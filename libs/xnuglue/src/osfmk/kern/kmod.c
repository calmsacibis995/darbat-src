/*
 * @NICTA_MODIFICATIONS_START@
 * 
 * This source code is licensed under Apple Public Source License Version 2.0.
 * Portions copyright Apple Computer, Inc.
 * Portions copyright National ICT Australia.
 *
 * All rights reserved.
 *
 * This code was modified 2006-06-20.
 *
 * @NICTA_MODIFICATIONS_END@
 */
/*
 * Copyright (c) 2001-2005 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 2.0 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * kmod.c
 *
 * XXX: TODO: this file has been clagged so much from the xnu tree that
 * XXX: we may as well use the real thing.
 */


/*
 * nothing fancy for now
 */
#define WRITE_PROTECT_MODULE_TEXT	0

#include <xnu_glue.h>
#include <xnucompat.h>

#include <l4/kdebug.h>
#include <kern/kalloc.h>

#include <mach/kern_return.h>
#include <mach/vm_types.h>
#include <mach/kmod.h>

#include <vm/vm_map.h>

#include <stdio.h>	/* printf */
/* XXX: bad */
extern void *kernel_map;

/*
 * Not all of these are implemented yet but we put them here anyway,
 * might as well.
 *
 * -gl
 */
kern_return_t   kmod_create_internal(kmod_info_t *info, kmod_t *id);
kern_return_t   kmod_destroy_internal(kmod_t id);
kern_return_t   kmod_start_or_stop(kmod_t id, int start, kmod_args_t *data,
                        mach_msg_type_number_t *dataCount);
kern_return_t   kmod_retain(kmod_t id);
kern_return_t   kmod_release(kmod_t id);
kern_return_t   kmod_queue_cmd(vm_address_t data, vm_size_t size);
kern_return_t   kmod_get_info(host_t host, kmod_info_array_t *kmods,
                        mach_msg_type_number_t *kmodCount);

kmod_info_t *kmod = 0;
static int kmod_index = 1;

decl_simple_lock_data(,kmod_lock)
decl_simple_lock_data(,kmod_queue_lock)

#include <l4/thread.h>

void kmod_dump1(char *s)
{
	kmod_info_t	*k;

    simple_lock(&kmod_lock);
	for (k = kmod; k ; k = k->next)
		printf("%s: (tid 0x%lx) dumping name %s id %d\n",
			s, L4_Myself().raw, k->name, k->id);
    simple_unlock(&kmod_lock);
}

static kern_return_t
_kmod_destroy_internal(kmod_t id, boolean_t fake)
{
    kern_return_t rc;
    kmod_info_t *k;    kmod_info_t *p;

    simple_lock(&kmod_lock);

    k = p = kmod;    while (k) {
        if (k->id == id) {
            kmod_reference_t *r, *t;

            if (!fake && (k->reference_count != 0)) {
                simple_unlock(&kmod_lock);                
	        return KERN_INVALID_ARGUMENT; 
	    }
    
            if (k == p) {    // first element
                kmod = k->next;
            } else {
                p->next = k->next;
            }
            simple_unlock(&kmod_lock);

            r = k->reference_list;
            while (r) {
                r->info->reference_count--;
                t = r;
                r = r->next;
                kfree(t, sizeof(struct kmod_reference));
            }

            if (!fake)
            {
#if DEBUG
                printf("kmod_destroy: %s (id %d), deallocating %d pages starting at 0x%x\n", k->name, k->id, k->size / PAGE_SIZE, k->address);
#endif /* DEBUG */

#ifndef L4IOKIT	/* no prelink for us yet. */
                if( (k->address >= sectPRELINKB) && (k->address < (sectPRELINKB + sectSizePRELINK)))
                {
                    vm_offset_t
                    virt = ml_static_ptovirt(k->address);
                    if( virt) {
                        ml_static_mfree( virt, k->size);
                    }
                }
                else
#endif
                {
                    rc = vm_map_unwire(kernel_map, k->address + k->hdr_size,
                            k->address + k->size, FALSE);
                    assert(rc == KERN_SUCCESS);

                    rc = vm_deallocate(kernel_map, k->address, k->size);
                    assert(rc == KERN_SUCCESS);
                }
            }
            return KERN_SUCCESS;
        }
        p = k;
        k = k->next;
    }

    simple_unlock(&kmod_lock);

    return KERN_INVALID_ARGUMENT;
}
kern_return_t
kmod_destroy_internal(kmod_t id)
{
    return _kmod_destroy_internal(id, FALSE);
}

kern_return_t
kmod_destroy(host_priv_t host_priv,
         kmod_t id)
{
#ifndef L4IOKIT	/* XXX: FIX later */
    if (host_priv == HOST_PRIV_NULL) return KERN_INVALID_HOST;
#endif
    return _kmod_destroy_internal(id, FALSE);
}

kern_return_t
kmod_retain(kmod_t id)
{
    kern_return_t rc = KERN_SUCCESS;

    kmod_info_t *t;    // reference to
    kmod_info_t *f;    // reference from
    kmod_reference_t *r = 0;

    r = (kmod_reference_t *)kalloc(sizeof(struct kmod_reference));
    if (!r) {
        rc = KERN_RESOURCE_SHORTAGE;
        goto finish;
    }

    simple_lock(&kmod_lock);

    t = kmod_lookupbyid(KMOD_UNPACK_TO_ID(id));
    f = kmod_lookupbyid(KMOD_UNPACK_FROM_ID(id));
    if (!t || !f) {
        simple_unlock(&kmod_lock);
        if (r) kfree(r, sizeof(struct kmod_reference));
        rc = KERN_INVALID_ARGUMENT;

        goto finish;
    }

    r->next = f->reference_list;
    r->info = t;
    f->reference_list = r;
    t->reference_count++;

    simple_unlock(&kmod_lock);

finish:

    return rc;
}

kern_return_t
kmod_default_start(struct kmod_info *ki, void *data)
{

    return KMOD_RETURN_SUCCESS;
}

kmod_info_t *
kmod_lookupbyid(kmod_t id)
{
    kmod_info_t *k = 0;
 
    k = kmod;
    while (k) {
        if (k->id == id) break;
        k = k->next;
    }
 
    return k;
}
 
kern_return_t
kmod_default_stop(struct kmod_info *ki, void *data)
{

    return KMOD_RETURN_SUCCESS;
}

kern_return_t
kmod_create_fake(const char *name, const char *version)
{
    kmod_info_t *info;

    if (!name || ! version ||
        (1 + strlen(name) > KMOD_MAX_NAME) ||
        (1 + strlen(version) > KMOD_MAX_NAME)) {

        return KERN_INVALID_ARGUMENT;
    }

    info = (kmod_info_t *)kalloc(sizeof(kmod_info_t));
    if (!info) {
        return KERN_RESOURCE_SHORTAGE;
    }

    // make de fake
    info->info_version = KMOD_INFO_VERSION;
    bcopy(name, info->name, 1 + strlen(name));
    bcopy(version, info->version, 1 + strlen(version));  //NIK fixed this part
    info->reference_count = 1;    // keep it from unloading, starting, stopping
    info->reference_list = 0;
    info->address = info->size = info->hdr_size = 0;
    info->start = info->stop = 0;

    simple_lock(&kmod_lock);

    // check to see if already "loaded"
    if (kmod_lookupbyname(info->name)) {
        simple_unlock(&kmod_lock);
        return KERN_INVALID_ARGUMENT;
    }

    info->id = kmod_index++;

    info->next = kmod;
    kmod = info;

    simple_unlock(&kmod_lock);

    return KERN_SUCCESS;
}

kmod_info_t *
kmod_lookupbyname(const char * name)
{
    kmod_info_t *k = 0;

    k = kmod;

    while (k) {
        if (!strcmp(k->name, name)) break;
        k = k->next;
    }

    return k;
}


kmod_info_t *
kmod_lookupbyname_locked(const char * name)
{
    kmod_info_t *k = 0;
    kmod_info_t *kc = 0;

    kc = (kmod_info_t *)kalloc(sizeof(kmod_info_t));
    if (!kc) return kc;

    simple_lock(&kmod_queue_lock);
    k = kmod_lookupbyname(name);
    if (k) {
        bcopy((char *)k, (char *)kc, sizeof(kmod_info_t));
    }

    simple_unlock(&kmod_queue_lock);

    if (k == 0) {
        kfree(kc, sizeof(kmod_info_t));
        kc = 0;
    }
    return kc;
}

/*
 * Operates only on 32 bit mach keaders on behalf of kernel module loader
 * if WRITE_PROTECT_MODULE_TEXT is defined.
 */
kern_return_t
kmod_create_internal(kmod_info_t *info, kmod_t *id)
{    kern_return_t rc;
    boolean_t     isPrelink;

    if (!info) return KERN_INVALID_ADDRESS;
    // double check for page alignment
    if ((info->address | info->hdr_size) & (PAGE_SIZE - 1)) {
        return KERN_INVALID_ADDRESS;
    }

#ifndef L4IOKIT
    isPrelink = ((info->address >= sectPRELINKB) && (info->address < (sectPRELINKB + sectSizePRELINK)));
    if (!isPrelink) {
        rc = vm_map_wire(kernel_map, info->address + info->hdr_size,
                info->address + info->size, VM_PROT_DEFAULT, FALSE);        if (rc != KERN_SUCCESS) {
            return rc;
        }
    }
#else
    isPrelink = 0;
#endif

#if WRITE_PROTECT_MODULE_TEXT
     {
        struct section * sect = getsectbynamefromheader(
            (struct mach_header*) info->address, "__TEXT", "__text");

        if(sect) {
            (void) vm_map_protect(kernel_map, round_page(sect->addr), trunc_page(sect->addr + sect->size),
                                    VM_PROT_READ|VM_PROT_EXECUTE, TRUE);
        }
    }
#endif /* WRITE_PROTECT_MODULE_TEXT */

    simple_lock(&kmod_lock);
    // check to see if already loaded
    if (kmod_lookupbyname(info->name)) {
        simple_unlock(&kmod_lock);
        if (!isPrelink) {
            rc = vm_map_unwire(kernel_map, info->address + info->hdr_size,
                info->address + info->size, FALSE);
            assert(rc == KERN_SUCCESS);
        }
        return KERN_INVALID_ARGUMENT;
    }

    info->id = kmod_index++;
    info->reference_count = 0;

    info->next = kmod;
    kmod = info;

    *id = info->id;
    simple_unlock(&kmod_lock);

#if DEBUG
    printf("kmod_create: %s (id %d), %d pages loaded at 0x%x, header size 0x%x\n",
        info->name, info->id, info->size / PAGE_SIZE, info->address, info->hdr_size);
#endif /* DEBUG */

    return KERN_SUCCESS;
}

kern_return_t
kmod_start_or_stop(
    kmod_t id,
    int start,
    kmod_args_t *data,
    mach_msg_type_number_t *dataCount)
{
    kern_return_t rc = KERN_SUCCESS;
    void * user_data = 0;
    kern_return_t (*func)(kmod_info_t *, void *);
    kmod_info_t *k;

    simple_lock(&kmod_lock);
    k = kmod_lookupbyid(id);
    if (!k || k->reference_count) {
        simple_unlock(&kmod_lock);
        rc = KERN_INVALID_ARGUMENT;
        goto finish;
    }

    if (start) {
        func = (void *)k->start;
    } else {
        func = (void *)k->stop;
    }

    simple_unlock(&kmod_lock);

    //
    // call kmod entry point
    //
    if (data && dataCount && *data && *dataCount) {
        vm_map_offset_t map_addr;
        vm_map_copyout(kernel_map, &map_addr, (vm_map_copy_t)*data);
        user_data = CAST_DOWN(void *, map_addr);
    }

    rc = (*func)(k, user_data);

finish:

    if (user_data) {
        (void) vm_deallocate(kernel_map, (vm_offset_t)user_data, *dataCount);
    }
    if (data) *data = 0;
    if (dataCount) *dataCount = 0;

    return rc;
}

