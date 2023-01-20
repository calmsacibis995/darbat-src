/*********************************************************************
 *                
 * Copyright (C) 2002-2004, Karlsruhe University
 *                
 * File path:     platform/generic/intctrl-apic.cc
 * Description:   Implementation of APIC+IOAPIC intctrl (with ACPI)
 *                
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *                
 * $Id: intctrl-apic.cc,v 1.8 2004/11/24 20:31:38 joshua Exp $
 *                
 ********************************************************************/

#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include <linear_ptab.h>

#include INC_GLUE(config.h)

#include INC_PLAT(acpi.h)

#include INC_ARCH(apic.h)
#include INC_ARCH(ioport.h)
#include INC_ARCH(trapgate.h)
#include INC_GLUE(idt.h)
#include INC_GLUE(space.h)
#include INC_GLUE(intctrl.h)
#include INC_GLUE(hwirq.h)

/* XXX: scons is broken */
#ifdef __ELF__
#define EXC_INTERRUPT(name)	IA32_EXC_NO_ERRORCODE(name, 0)
#elif defined(__APPLE_CC__)
#define EXC_INTERRUPT(name)	IA32_EXC_NO_ERRORCODE(name, 0)
#endif
void handle_interrupt(word_t irq);

intctrl_t intctrl;
EXC_INTERRUPT(spurious_interrupt)
{
    enter_kdebug("spurious interrupt - what now?");
}

HW_IRQ( 0);
HW_IRQ( 1);
HW_IRQ( 2);
HW_IRQ( 3);
HW_IRQ( 4);
HW_IRQ( 5);
HW_IRQ( 6);
HW_IRQ( 7);
HW_IRQ( 8);
HW_IRQ( 9);
HW_IRQ(10);
HW_IRQ(11);
HW_IRQ(12);
HW_IRQ(13);
HW_IRQ(14);
HW_IRQ(15);
HW_IRQ(16);
HW_IRQ(17);
HW_IRQ(18);
HW_IRQ(19);
HW_IRQ(20);
HW_IRQ(21);
HW_IRQ(22);
HW_IRQ(23);
HW_IRQ(24);
HW_IRQ(25);
HW_IRQ(26);
HW_IRQ(27);
HW_IRQ(28);
HW_IRQ(29);
HW_IRQ(30);
HW_IRQ(31);
HW_IRQ(32);
HW_IRQ(33);
HW_IRQ(34);
HW_IRQ(35);
HW_IRQ(36);
HW_IRQ(37);
HW_IRQ(38);
HW_IRQ(39);
HW_IRQ(40);
HW_IRQ(41);
HW_IRQ(42);
HW_IRQ(43);
HW_IRQ(44);
HW_IRQ(45);
HW_IRQ(46);
HW_IRQ(47);
HW_IRQ(48);
HW_IRQ(49);

/* have this asm _after_ the entry points to get forward jumps */
HW_IRQ_COMMON();


typedef void(*hwirqfunc_t)();
INLINE hwirqfunc_t get_interrupt_entry(word_t irq)
{
    return (hwirqfunc_t)((word_t)hwirq_0 + ((word_t)hwirq_1 - (word_t)hwirq_0) * irq);
}

INLINE word_t intctrl_t::setup_idt_entry(word_t irq, u8_t prio)
{
    word_t vector = IDT_IOAPIC_BASE + irq;
#if 1
    TRACEF("IRQ %d, vector=%d, prio=%d, entry=%p\n", 
	   irq, vector, prio, get_interrupt_entry(irq));
#endif
    idt.add_int_gate(vector, get_interrupt_entry(irq));
    return vector;
}

static spinlock_t global_ioapic_lock;

INLINE void intctrl_t::sync_redir_entry(ioapic_redir_table_t * entry, bool full_sync)
{
	ASSERT(ALWAYS, entry->is_valid());

    //ioapic_locks[entry->id].lock();
    global_ioapic_lock.lock();
    i82093_t * ioapic = get_ioapic(entry->id);
    if (full_sync)
	ioapic->set_redir_entry(entry->line, entry->entry);
    else
	ioapic->set_redir_entry_low(entry->line, entry->entry);
    global_ioapic_lock.unlock();
    //ioapic_locks[entry->id].unlock();
}

static bool mapit(addr_t addr)
{
    if (!get_kernel_space()->is_user_area(addr))
    {
	TRACE("ACPI: I won't map into kernel area\n");
	return false;
    }
    // map writable -- we may overmap existing mappings
    get_kernel_space()->add_mapping
	(addr_mask (addr, ~page_mask (ACPI_PGENTSZ)),
	 addr_mask (addr, ~page_mask (ACPI_PGENTSZ)),
	 ACPI_PGENTSZ, true, true, true);

    return true;
}

void intctrl_t::init_arch()
{
    /* first initialize object */
    for (word_t i = 0; i < NUM_REDIR_ENTRIES; i++)
	redir[i].init();

    for (word_t i = 0; i < CONFIG_MAX_IOAPICS; i++)
	ioapic_locks[i].init();

    max_intsource = 0;
    num_intsources = 0;

    /* mask all IRQs on PIC1 and PIC2 */
    out_u8(0x21, 0xff);
    out_u8(0xa1, 0xff);

    /* set APIC to symetric mode */
    out_u8(0x22, 0x70);
    out_u8(0x23, 0x01);

    /* setup spurious interrupt vector */
    idt.add_int_gate(IDT_LAPIC_SPURIOUS_INT, spurious_interrupt_wrapper);

#ifndef CONFIG_EFI
    /* now walk the ACPI structure */
    mapit((addr_t)ACPI20_PC99_RSDP_START);
#endif

    printf( "looking for RSDP\n" );
    acpi_rsdp_t* rsdp = acpi_rsdp_t::locate();
    TRACE_INIT("RSDP is at %p\n", rsdp);

#if CONFIG_EFI
    printf( "mapping RSDP\n" );
    /* we only know the location of the rsdp now... */
    mapit((addr_t)rsdp);
#endif
    
    if (rsdp == NULL)
    {
	TRACE_INIT("Assuming local APIC defaults");
	get_kernel_space()->add_mapping((addr_t)(APIC_MAPPINGS),
					(addr_t)(0xFEE00000),
					APIC_PGENTSZ, true, true, true);
	
	return;
    }
    
    acpi_rsdt_t* rsdt = rsdp->rsdt();
    acpi_xsdt_t* xsdt = rsdp->xsdt();

    if ((rsdt == NULL) && (xsdt == NULL))
	return;

    TRACE_INIT("RSDT is at %p\n", rsdt);
    TRACE_INIT("XSDT is at %p\n", xsdt);

    acpi_madt_t* madt = NULL;
    if (xsdt != NULL)
    {
	    printf( "finding APIC, xsdt style\n" );
	if (!mapit(xsdt)) return;
	madt = (acpi_madt_t*) xsdt->find("APIC");
    }
    if ((madt == NULL) && (rsdt != NULL))
    {
	    printf( "finding APIC, rsdt style\n" );
	if (!mapit(rsdt)) return;
	madt = (acpi_madt_t*) rsdt->find("APIC");
    }
    
    if (madt == NULL)
    {
	    printf( "no madt :(\n" );
	return;
    }

    if (!mapit(madt))
    {
	    printf( "coulnd't map madt :(\n" );
	    return;
    }

    TRACE_INIT("MADT is at %p, local APICs @ %p\n",
	       madt, madt->local_apic_addr);
    
    TRACE_INIT("Mapping local APICs at %p to %p\n",
	       madt->local_apic_addr, APIC_MAPPINGS);
    get_kernel_space()->add_mapping((addr_t)(APIC_MAPPINGS),
				    (addr_t)((word_t)madt->local_apic_addr),
				    APIC_PGENTSZ, true, true, true);
    printf( "Local APIC...\n" );
    /* local apic */
    {
	num_cpus = 0;
	lapic_map = 0;
	acpi_madt_lapic_t* p;
	for (word_t i = 0; ((p = madt->lapic(i)) != NULL); i++)
	{
	    TRACE_INIT("Found local APIC: apic_id=%d use=%s proc_id=%d\n",
		       p->id, p->flags.enabled ? "ok" : "disabled",
		       p->apic_processor_id);
	    if (p->flags.enabled)
		num_cpus++;
	    lapic_map |= (1 << p->id);
	}
	TRACE_INIT("Found %d active CPUs, boot CPU is %x\n",
		   num_cpus, local_apic.id());
		   
    }

    printf( "IO APIC...\n" );

    /* IO APIC */
    {
	acpi_madt_ioapic_t* p;
	ioapic_map = 0;

	for (word_t i = 0; ((p = madt->ioapic(i)) != NULL); i++)
	{
	    i82093_t* ioapic = get_ioapic(p->id);
	    TRACE_INIT("Found IOAPIC: id=%d irq_base=%d addr=%p, map address=%p\n",
		       p->id, p->irq_base, p->address, ioapic);
	    if ((p->address & page_mask(APIC_PGENTSZ)) != 0)
	    {
		TRACE_INIT("  APIC %d IS MISALIGNED (%p). Ignoring!\n",
			   i, p->address);
		continue;
	    }
	    get_kernel_space()->add_mapping((addr_t)ioapic,
					    (addr_t)((word_t)p->address),
					    APIC_PGENTSZ,
					    true, // writable
					    true, // kernel
					    true, // global
					    false); // uncacheable

	    init_io_apic(p->id, p->irq_base);
	    ioapic_map |= 1 << p->id;
	}
    }

    printf( "IRQ Overrides...\n" );

    /* IRQ source overrides */
    {
	acpi_madt_irq_t* p;
	for (word_t i = 0; ((p = madt->irq(i)) != NULL); i++)
	{
	    TRACE_INIT("Found IRQ source override: "
		       "srcbus=%d, srcirq=%d, dest=%d, "
		       "%s, trigger=%s \n",
		       p->src_bus, p->src_irq, p->dest,
		       p->get_polarity() == 0 ? "conform pol." :
		       p->get_polarity() == 1 ? "active high" :
		       p->get_polarity() == 3 ? "active low" : "reserved",
		       p->get_trigger_mode() == 0 ? "conform" :
		       p->get_trigger_mode() == 1 ? "edge" :
		       p->get_trigger_mode() == 3 ? "level" : "reserved");

	    /* source overrides only exist for ISA (see ACPI spec), 
	     * hence conform means high active, edge triggered
	     * An override means that the original src irq is 
	     * connected to dest. For example the timer is usually connected
	     * to IRQ 0, but in APIC mode it is redirected to IRQ 2.
	     * We do not eliminate the redirections but have to
	     * care about polarity.
	     */
	    ioapic_redir_t * entry = &redir[p->dest].entry;
/*
 * XXX glee
 *
 * in a redir entry, according to the 82093 spec if the polarity is active
 * high then this field is zero, otherwise 1.
 */

#if 0
	    entry->polarity = 
		(p->get_polarity() == acpi_madt_irq_t::active_low) ? 1 : 0;
#else
	    entry->polarity = 
		(p->get_polarity() == acpi_madt_irq_t::active_high) ? 1 : 0;
#endif
	    entry->trigger_mode = 
		(p->get_trigger_mode() == acpi_madt_irq_t::level) ? 1 : 0;
	}
	
    }

    /* Any other tables ? */
    {
	acpi_madt_hdr_t* p;
	for (u8_t t = 3; t <= 8; t++)
	    for (word_t i = 0; ((p = madt->find(t, i)) != NULL); i++)
		TRACE_INIT("MADT: found unknown type=%d, len=%d\n", p->type, p->len);
    }
    
    TRACE_INIT("Found %d IRQ input lines, max IRQ ID is %d\n",
	       num_intsources, max_intsource);

    for (word_t i = 0; i <= max_intsource; i++)
    {
	/// @todo: handle IRQ prios correctly
	word_t vector = setup_idt_entry(i, 0);

	if (redir[i].is_valid())
	{
	    TRACE_INIT(" IRQ %2d: APIC %d, line %2d, %s, %s active\n",
		       i, redir[i].id, redir[i].line, 
		       redir[i].entry.trigger_mode ? "level" : "edge",
#if 0
		       redir[i].entry.polarity ? "high" : "low");
#else
		       redir[i].entry.polarity ? "low" : "high");
#endif
	    redir[i].entry.vector = vector;
	    sync_redir_entry(&redir[i], true);
	}
    }
		   
    printf( "intctr::init_arch: I'm done!!\n" );
}


void intctrl_t::init_cpu()
{
    TRACE_INIT("APIC init CPU\n");
    init_local_apic();
}


void intctrl_t::init_io_apic(word_t ioapic_id, word_t irq_base)
{
    i82093_t * ioapic = get_ioapic(ioapic_id);
    word_t numirqs = ioapic->version().ver.max_lvt + 1;
    TRACE_INIT("              realid=%d maxint=%d, version=%d\n",
	       ioapic->id(), numirqs, ioapic->version().ver.version);

    /* VU: we initialize all IO-APIC interrupts. By default all 
     *     IRQs are steered to local apic 0. The kernel re-routes
     *     them later on via set_cpu(...)
     */
    for (word_t i = 0; i < numirqs; i++)
    {
	redir[irq_base + i].set(ioapic_id, i);
	ioapic_redir_t * entry = &redir[irq_base + i].entry;

	/* ISA IRQs are mapped 1:1 --> 0 to 15 */
	if (irq_base + i < 16)
	    entry->set_fixed_hwirq(IDT_IOAPIC_BASE + irq_base + i,
				   false,	// high active
				   false,	// edge triggered
				   true,	// masked
				   0);		// apic 0
	else
	    entry->set_fixed_hwirq(IDT_IOAPIC_BASE + irq_base + i,
				   true,	// low active
				   true,	// level triggered
				   true,	// masked
				   0);		// apic 0
    }

    /* update the interrupt sources */
    num_intsources += numirqs;
    if ((irq_base + numirqs - 1) > max_intsource)
	max_intsource = irq_base + numirqs - 1;
}

void intctrl_t::init_local_apic()
{
    TRACE_INIT("local apic id=%d, version=%d\n",
	       local_apic.id(), local_apic.version());

    if (!local_apic.enable(IDT_LAPIC_SPURIOUS_INT))
	WARNING ("failed initializing local APIC\n");

    /* VU: now deal with broken BIOS or crazy ID assignements 
     * for efficiency reasons we try to change local APIC ids to be 
     * contiguous
     */
    if (local_apic.id() >= num_cpus)
    {
	static spinlock_t apicid_init;
	apicid_init.lock();

	/* try to find an unused local APIC id */
	for (word_t i = 0; i < num_cpus; i++)
	    if ((lapic_map & (1 << i)) == 0)
	    {
		lapic_map |= (1 << i);
		TRACE_INIT("changing local APIC id to %d\n", i);
		local_apic.set_id(i);
		if (local_apic.id() != i)
		    panic("could not change local APIC id\n");
		break;
	    }

	apicid_init.unlock();
    }

    local_apic.set_task_prio(0);
    
    /* now disable all interrupts */
    local_apic.mask(local_apic_t<APIC_MAPPINGS>::lvt_timer);
    local_apic.mask(local_apic_t<APIC_MAPPINGS>::lvt_thermal_monitor);
    local_apic.mask(local_apic_t<APIC_MAPPINGS>::lvt_perfcount);
    local_apic.mask(local_apic_t<APIC_MAPPINGS>::lvt_lint0);
    local_apic.mask(local_apic_t<APIC_MAPPINGS>::lvt_lint1);
    local_apic.mask(local_apic_t<APIC_MAPPINGS>::lvt_error);
}

void intctrl_t::mask(word_t irq)
{
    ASSERT(ALWAYS, redir[irq].is_valid());

    if (redir[irq].entry.is_edge_triggered())
    {
	redir[irq].entry.mask_irq();
    }
    else
    {
	redir[irq].entry.mask_irq();
	sync_redir_entry(&redir[irq], false);
    }
}

bool intctrl_t::unmask(word_t irq)
{
    ASSERT(ALWAYS, redir[irq].is_valid());

    if (redir[irq].entry.is_edge_triggered())
    {
	if (redir[irq].pending)
	{
	    redir[irq].pending = false;
	    return true; // leave IRQ masked, since there was another pending
	}
	redir[irq].entry.unmask_irq();
    }
    else
    {
	redir[irq].entry.unmask_irq();
	sync_redir_entry(&redir[irq], false);
    }
    return false;
}

bool intctrl_t::is_masked(word_t irq)
{
    return redir[irq].entry.is_masked_irq();
}

void intctrl_t::enable(word_t irq)
{
    redir[irq].pending = false;
    redir[irq].entry.unmask_irq();
    sync_redir_entry(&redir[irq], false);
}

void intctrl_t::disable(word_t irq)
{
    redir[irq].pending = false;
    redir[irq].entry.mask_irq();
    sync_redir_entry(&redir[irq], false);
}

bool intctrl_t::is_enabled(word_t irq)
{
    return !is_masked(irq);
}

void intctrl_t::set_cpu(word_t irq, word_t cpu)
{
#if !defined(CONFIG_SMP)
    /* VU: on SMP systems we may have an APIC id != 0
     * hence we set the correct routing value here. Since thread migrations
     * are not possible on a UP this function is not time critical
     */
    cpu = local_apic.id();
#endif
    if (redir[irq].entry.get_phys_dest() != cpu)
    {
	redir[irq].entry.set_phys_dest(cpu);
	sync_redir_entry(&redir[irq], true);
    }
}

/* handler invoked on interrupt */
void intctrl_t::handle_irq(word_t irq)
{
    bool deliver = true;

    // edge triggered IRQs are marked as pending if masked
    if ( redir[irq].entry.is_edge_triggered() &&
	 redir[irq].entry.mask )
    {
	//printf("set pending and not delivering\n");
	redir[irq].pending = true;
	deliver = false;
    } else if (is_masked(irq)){
	local_apic.EOI();
	TRACE("Bogus IRQ %d raised\n", irq);
	return;
    }

    mask(irq);
    local_apic.EOI();

    if (deliver)
	::handle_interrupt(irq);
}

word_t intctrl_t::get_number_irqs()
{
    return max_intsource + 1;
}

bool intctrl_t::is_irq_available(word_t irq)
{
    ASSERT(ALWAYS, irq < get_number_irqs());
    if (irq == 9) return false;
    return redir[irq].is_valid();
}
