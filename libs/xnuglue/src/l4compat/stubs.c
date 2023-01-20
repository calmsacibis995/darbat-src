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
 * stubs.c
 *
 */

#include <assert.h>
#include <stdio.h>	/* printf */

#if 0
//#if __PEDANTIC_MUST_IMPLEMENT__
#define XNUSTUB(sym)	\
	void (sym)(void); \
	void (sym)(void) { printf("%s: called.  Caller %p\n", \
		__FUNCTION__, __builtin_return_address(0)); \
	assert(!"shit"); }
#else
#define XNUSTUB(sym)	\
	int (sym)(void); \
	int (sym)(void) { printf("%s: called.  Caller %p\n", \
		__FUNCTION__, __builtin_return_address(0)); \
	return (0); }
#endif

XNUSTUB(assert_wait_deadline);
XNUSTUB(bpfattach);
XNUSTUB(b_to_q);
XNUSTUB(buf_biodone);
XNUSTUB(buf_blkno);
XNUSTUB(buf_count);
XNUSTUB(buf_dataptr);
XNUSTUB(buf_device);
XNUSTUB(buf_drvdata);
XNUSTUB(buf_flags);
XNUSTUB(buf_setdrvdata);
XNUSTUB(buf_seterror);
XNUSTUB(buf_setresid);
XNUSTUB(buf_upl);
XNUSTUB(buf_uploffset);
XNUSTUB(clalloc);
XNUSTUB(clfree);
XNUSTUB(clock_get_system_microtime);
XNUSTUB(clock_wakeup_calendar);
XNUSTUB(conslog_putc);
XNUSTUB(copyout);
XNUSTUB(cpuid_info);
XNUSTUB(dbugprintf);
XNUSTUB(dcache_incoherent_io_flush64);
XNUSTUB(dcache_incoherent_io_store64);
XNUSTUB(Debugger);
XNUSTUB(debug_mode);	/* DATA */
XNUSTUB(devfs_remove);
XNUSTUB(device_pager_deallocate);
XNUSTUB(device_pager_populate_object);
XNUSTUB(ether_add_proto);
XNUSTUB(ether_check_multi);
XNUSTUB(ether_del_proto);
XNUSTUB(ether_demux);
XNUSTUB(ether_frameout);
XNUSTUB(ev_try_lock);
XNUSTUB(ev_unlock);
XNUSTUB(first_avail);	/* DATA */
XNUSTUB(get_aiotask);
XNUSTUB(gPEClockFrequencyInfo);
XNUSTUB(gPESerialBaud);
XNUSTUB(host_priv_self);
XNUSTUB(ifmaddr_address);
XNUSTUB(ifnet_addrlen);
XNUSTUB(ifnet_allocate);
XNUSTUB(ifnet_attach);
XNUSTUB(ifnet_detach);
XNUSTUB(ifnet_eflags);
XNUSTUB(ifnet_event);
XNUSTUB(ifnet_family);
XNUSTUB(ifnet_flags);
XNUSTUB(ifnet_free_multicast_list);
XNUSTUB(ifnet_get_multicast_list);
XNUSTUB(ifnet_hdrlen);
XNUSTUB(ifnet_ioctl);
XNUSTUB(ifnet_mtu);
XNUSTUB(ifnet_name);
XNUSTUB(ifnet_release);
XNUSTUB(ifnet_set_addrlen);
XNUSTUB(ifnet_set_baudrate);
XNUSTUB(ifnet_set_flags);
XNUSTUB(ifnet_set_hdrlen);
XNUSTUB(ifnet_set_lladdr);
XNUSTUB(ifnet_set_mtu);
XNUSTUB(ifnet_set_offload);
XNUSTUB(ifnet_softc);
XNUSTUB(ifnet_stat_increment_out);
XNUSTUB(ifnet_unit);
XNUSTUB(in_cksum_offset);
XNUSTUB(in_delayed_cksum_offset);
XNUSTUB(iokit_alloc_object_port);
XNUSTUB(iokit_destroy_object_port);
XNUSTUB(iokit_lookup_connect_ref_current_task);
XNUSTUB(iokit_make_send_right);
XNUSTUB(iokit_mod_send_right);
XNUSTUB(iokit_release_port);
XNUSTUB(iokit_retain_port);
XNUSTUB(iokit_switch_object_port);
XNUSTUB(IOUnmapPages);
XNUSTUB(ipc_port_release_send);
XNUSTUB(kauth_cred_get);
XNUSTUB(kdebug_enable);
XNUSTUB(kdp_register_send_receive);
XNUSTUB(kdp_set_interface);
XNUSTUB(kdp_unregister_send_receive);
XNUSTUB(kdreboot);
XNUSTUB(kernel_map);	/* DATA */
XNUSTUB(kernel_pmap);	/* DATA */
XNUSTUB(kernel_task);	/* DATA */
XNUSTUB(kmem_alloc_contig);
XNUSTUB(kmem_free);
XNUSTUB(kmem_realloc);
XNUSTUB(kmem_suballoc);
XNUSTUB(kmod_dump_log);
XNUSTUB(kmod_load_extension);
XNUSTUB(KUNCGetNotificationID);
XNUSTUB(KUNCUserNotificationDisplayFromBundle);
XNUSTUB(KUNCUserNotificationDisplayNotice);
XNUSTUB(lck_attr_alloc_init);
XNUSTUB(lck_attr_free);
XNUSTUB(lck_attr_setdebug);
XNUSTUB(lck_attr_setdefault);
XNUSTUB(lck_grp_alloc_init);
XNUSTUB(lck_grp_attr_alloc_init);
XNUSTUB(lck_grp_attr_free);
XNUSTUB(lck_grp_attr_setdefault);
XNUSTUB(lck_grp_free);
XNUSTUB(lck_mtx_sleep_deadline);
XNUSTUB(lck_rw_alloc_init);
XNUSTUB(lck_rw_free);
XNUSTUB(mach_make_memory_entry);
XNUSTUB(mach_make_memory_entry_64);
XNUSTUB(mach_memory_entry_purgable_control);
XNUSTUB(mach_memory_object_memory_entry_64);
XNUSTUB(mach_msg_send_from_kernel);
XNUSTUB(master_device_port);
XNUSTUB(max_valid_stack_address);
XNUSTUB(memory_object_iopl_request);
XNUSTUB(microtime);	/* AppleYukon */
XNUSTUB(microuptime);
XNUSTUB(min_valid_stack_address);
XNUSTUB(ml_cause_interrupt);
XNUSTUB(ml_init_max_cpus);
XNUSTUB(ml_phys_read_byte);
XNUSTUB(ml_phys_read_byte_64);
XNUSTUB(ml_phys_read_double);
XNUSTUB(ml_phys_read_double_64);
XNUSTUB(ml_phys_read_half);
XNUSTUB(ml_phys_read_half_64);
XNUSTUB(ml_phys_read_word);
XNUSTUB(ml_phys_read_word_64);
XNUSTUB(ml_phys_write_byte);
XNUSTUB(ml_phys_write_byte_64);
XNUSTUB(ml_phys_write_double);
XNUSTUB(ml_phys_write_double_64);
XNUSTUB(ml_phys_write_half);
XNUSTUB(ml_phys_write_half_64);
XNUSTUB(ml_phys_write_word);
XNUSTUB(ml_phys_write_word_64);
XNUSTUB(ml_static_mfree);
#if 0
XNUSTUB(ml_static_ptovirt);
#endif
XNUSTUB(ml_thread_policy);
XNUSTUB(msleep);
XNUSTUB(ollo);
XNUSTUB(PE_current_console);
XNUSTUB(PE_display_icon);
XNUSTUB(PE_enter_debugger);
XNUSTUB(PE_initialize_console);
XNUSTUB(pmap_enter);
XNUSTUB(q_to_b);
XNUSTUB(suser);
XNUSTUB(sync_internal);
XNUSTUB(task_deallocate);
XNUSTUB(task_info);
XNUSTUB(task_reference);
XNUSTUB(termioschars);
XNUSTUB(tk_nin);
XNUSTUB(tk_rawcc);
XNUSTUB(ttioctl);
XNUSTUB(ttread);
XNUSTUB(ttyclose);
XNUSTUB(ttyflush);
XNUSTUB(ttylclose);
XNUSTUB(ttyselect);
XNUSTUB(upl_abort);
XNUSTUB(upl_commit);
XNUSTUB(upl_deallocate);
XNUSTUB(upl_get_internal_pagelist_offset);
XNUSTUB(upl_offset_to_pagelist);
XNUSTUB(upl_transpose);
XNUSTUB(vm_deallocate);
XNUSTUB(vm_inherit);
XNUSTUB(vm_map_copyin_common);
XNUSTUB(vm_map_copyout);
XNUSTUB(vm_map_create_upl);
XNUSTUB(vm_map_deallocate);
XNUSTUB(vm_map_get_upl);
XNUSTUB(vm_map_reference);
XNUSTUB(vm_map_unwire);
XNUSTUB(vm_map_wire);

/*
 * Libsa stuff.  These must be implemented.  Or probably should be for
 * most of them.
 */
XNUSTUB(getsectbyname);
XNUSTUB(host_info);
XNUSTUB(kld_set_link_options);
XNUSTUB(kld_unload_all);
XNUSTUB(flush_dcache);
XNUSTUB(invalidate_icache);

/*
 * Special provisions.
 */
#undef XNUSTUB
#define XNUSTUB(sym) \
int (sym)(void); \
	int (sym)(void) { printf("%s: called.  Caller %p\n", \
		__FUNCTION__, __builtin_return_address(0)); \
	return (1); }
XNUSTUB(kld_load_basefile_from_memory);
