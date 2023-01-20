/*********************************************************************
 *
 * Copyright (C) 2002,  Karlsruhe University
 * Copyright (C) 2005,  National ICT Australia (NICTA)
 *
 * File path:    api/v4/interrupt.cc 
 * Description:  Interrupt handling
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
 * $Id: interrupt.cc,v 1.22 2004/12/09 01:20:32 cvansch Exp $
 *
 *********************************************************************/

#include <macros.h>
#include <types.h>
#include <config.h>
#include <debug.h>
#include <kdb/tracepoints.h>

#include INC_API(tcb.h)
#include INC_API(space.h)
#include INC_API(interrupt.h)
#include INC_API(schedule.h)
#include INC_API(kernelinterface.h)
#include INC_API(smp.h)
#ifdef CONFIG_PHYSICAL_KERNEL
#include <generic/tidtable.h>
#endif

void handle_interrupt(word_t irq);

#if defined(CONFIG_TRACEBUFFER)
extern long tb_irq;
bool tb_reply_irq();
void tb_irq_control(bool enable);
# define nTBUF_IRQ(irq)  (irq != tb_irq)
#else
# define nTBUF_IRQ(irq)  (1)
#endif

//#define TRACE_IRQ TRACEF
#define TRACE_IRQ(x...)
//#define TRACE_IRQ(x...) printf(x)

DECLARE_TRACEPOINT(INTERRUPT);
DECLARE_TRACEPOINT(SYSCALL_THREAD_CONTROL_IRQ);
EXTERN_TRACEPOINT(PREEMPTION_SIGNALED);

static utcb_t irq_utcb;

// handler for dedicated irq threads
static void irq_thread()
{
    tcb_t * current = get_current_tcb();
    int irq = current->get_global_id().get_irqno();

    while(1)
    {
	tcb_t * handler_tcb =
		get_current_space()->get_tcb(current->get_irq_handler());

	/* VU: when we are in the send queue the IRQ thread was busy
	 * and the IRQ could not be delivered. Hence, we actually
	 * have to send the IPC. Otherwise, the message was delivered
	 * on the fast path and we got activated by an ack IPC */
	if (current->queue_state.is_set(queue_state_t::send))
	{
	    // got activated -- do send operation
	    ASSERT(DEBUG, handler_tcb->is_local_cpu());
	    ASSERT(DEBUG, current->is_local_cpu());
	    TRACE_IRQ("deliver IRQ message\n");

	    handler_tcb->lock();
	    current->dequeue_send(handler_tcb);
	    handler_tcb->unlock();

	    handler_tcb->set_tag(msg_tag_t::irq_tag());
	    handler_tcb->set_partner(current->get_global_id());
	    current->set_partner(current->get_irq_handler());
	    current->set_state(thread_state_t::waiting_forever);
	    current->switch_to(handler_tcb);
	}

	// got re-activated due to send operation to IRQ thread...
	if (!current->queue_state.is_set(queue_state_t::send))
	{
	    TRACE_IRQ("got activated irq = %d\n", irq);

	    current->set_state(thread_state_t::halted);
	 
	    // if an interrupt was already pending deliver it
#if defined(CONFIG_TRACEBUFFER)
	    if (irq == tb_irq)
	    {
		if (tb_reply_irq())
		    handle_interrupt(irq);
	    }
	    else
#endif
	    {
		if (get_interrupt_ctrl()->unmask(irq)) 
		    handle_interrupt(irq);
	    }

	    get_current_scheduler()->yield(current);
	}
    }
}

#ifdef CONFIG_SMP
static void do_xcpu_send_irq(cpu_mb_entry_t * entry)
{
    tcb_t * handler_tcb = entry->tcb;
    word_t irq = entry->param[0];

    if (!handler_tcb->is_local_cpu())
	UNIMPLEMENTED();

    if (handler_tcb->get_state().is_waiting() &&
	( handler_tcb->get_partner().is_anythread() ||
	  handler_tcb->get_partner() == threadid_t::irqthread(irq) ))
    {
	// ok, thread is waiting -- deliver IRQ
	printf("xcpu-IRQ delivery (%d->%t)\n", irq, handler_tcb);
	handler_tcb->set_tag(msg_tag_t::irq_tag());
	handler_tcb->set_partner(threadid_t::irqthread(irq));
	handler_tcb->set_state(thread_state_t::running);
	get_current_scheduler()->enqueue_ready(handler_tcb);
    }
    else
	UNIMPLEMENTED();
}

/* for IRQ forwarding */
static void do_xcpu_interrupt(cpu_mb_entry_t * entry)
{
    word_t irq = entry->param[0];
    handle_interrupt(irq);
}
#endif

/**
 * interrupt handler, delivers interrupt IPC if thread is waiting
 * @param irq interrupt number
 */
void handle_interrupt(word_t irq)
{
    TRACEPOINT (INTERRUPT, printf("IRQ %d\n", irq));

    spin(76, get_current_cpu());

    tcb_t * current = get_current_tcb();
    TRACE_IRQ("IRQ%d (curr=%t)\n", irq, current);

    threadid_t irq_tid = threadid_t::irqthread(irq);
    tcb_t * irq_tcb = get_kernel_space()->get_tcb(irq_tid);
    
    // some sanity checks
    ASSERT(DEBUG, irq_tid.get_irqno() < get_kip()->thread_info.get_system_base());

    /* VU: we can get a spurious interrupt if we de-attached the IRQ
     * meanwhile in this case we simply ignore the IRQ */
    if ( irq_tcb->get_state() == thread_state_t::aborted )
    {
	TRACE("CPU%d spurious IRQ%d?\n", get_current_cpu(), irq);
	return;
    }

#ifdef CONFIG_SMP
    /* while migrating it may happen that we get an IRQ -> forward to
     * other CPU */
    if ( !irq_tcb->is_local_cpu() )
    {
	xcpu_request( irq_tcb->get_cpu(), do_xcpu_interrupt, NULL, irq );
	return;
    }
#endif

    // we should only receive irqs if the thread is halted
    ASSERT(NORMAL, irq_tcb->get_state().is_halted());

    // get the handler thread id
    threadid_t handler_tid = irq_tcb->get_irq_handler();
    tcb_t * handler_tcb = get_kernel_space()->get_tcb(handler_tid);

    // if the handler TID is not valid -- abort the IRQ thread
    if (EXPECT_FALSE( handler_tcb->get_global_id() != handler_tid ))
    {
	TRACE("IRQ handler TID is invalid -- halting IRQ%d\n", irq);
	irq_tcb->set_state(thread_state_t::aborted);
	return;
    }

    //TRACE_IRQ("handler_tcb: %t, state=%x\n", handler_tcb, (word_t)handler_tcb->get_state());
    //enter_kdebug("irq");

    if (EXPECT_TRUE( handler_tcb->get_state().is_waiting() ))
    {
	// thread is waiting for IPC -- we use a shortcut
	threadid_t partner = handler_tcb->get_partner();

	if (EXPECT_TRUE( partner == irq_tid || partner.is_anythread() ))
	{
	    // set IRQ thread to be waiting for the ack IPC
	    irq_tcb->set_partner(handler_tid);
	    irq_tcb->set_state(thread_state_t::waiting_forever);

#ifdef CONFIG_SMP
	    if (!handler_tcb->is_local_cpu())
	    {
		xcpu_request( handler_tcb->get_cpu(), do_xcpu_send_irq, 
			      handler_tcb, irq);
		return;
	    }
#endif

	    // deliver IPC
	    handler_tcb->set_tag(msg_tag_t::irq_tag());
	    handler_tcb->set_partner(irq_tid);

	    /* we enter this path only if the handler is waiting -- so
	     * we are not currently executing on its TCB */
#if 0
	    if (current == irq_tcb || current == get_idle_tcb()) 
		current->switch_to(handler_tcb);
#else
	// it appears that we cannot call switch_to() in the kernel hardware
	// interrupt thread context.  So, we will short-circuit to the
	// enqueue path.  This could, of course, cause latency problems
	// if your system is loaded.
	// XXX: fixme -gl 
	    if (current == irq_tcb)
		goto enqueue;
	    if (current == get_idle_tcb()) 
		current->switch_to(handler_tcb);
#endif

	    else if (get_current_scheduler()->check_dispatch_thread(current, handler_tcb))
	    {
		TRACE_IRQ("deliver IRQ to %t\n", handler_tcb);

		if ( EXPECT_FALSE(current->get_preempt_flags().is_signaled()) )
		{
		    TRACEPOINT(PREEMPTION_SIGNALED, 
			    printf("preemption signalled (irq) for %t\n", current));

		    current->set_preempted_ip( current->get_user_ip() );
		    current->set_user_ip( current->get_preempt_callback_ip() );
		}

		// make sure we are in the ready queue
		get_current_scheduler()->preempt_thread (current, handler_tcb);
		current->switch_to (handler_tcb);
	    }
	    else
	    {
		/* according to the scheduler should the current
		 * thread remain active so simply activate the other
		 * guy and return */
enqueue:
		TRACE_IRQ("enqueue IRQ handler %t (curr=%t)\n", handler_tcb, current);
		handler_tcb->set_state(thread_state_t::running);
		get_current_scheduler()->enqueue_ready(handler_tcb);
	    }
	    return;
	}
    }

    TRACE_IRQ("IRQ%d not delivered -- enqueue\n", irq);

    /* the thread is not waiting for IPC -- so generate nice msg and
     * enqueue into send queue */
    irq_tcb->set_tag(msg_tag_t::irq_tag());
    irq_tcb->set_partner(handler_tid);
    irq_tcb->set_state(thread_state_t::polling);
    handler_tcb->lock();
    irq_tcb->enqueue_send(handler_tcb);
    handler_tcb->unlock();
}

#ifdef CONFIG_SMP
static void do_xcpu_thread_control_interrupt(cpu_mb_entry_t * entry)
{
    threadid_t handler_tid;
    handler_tid.set_raw(entry->param[0]);
    thread_control_interrupt(entry->tcb->get_global_id(), handler_tid);
}
#endif

/**
 * implements the sys_thread_control-handling for interrupt threads
 * @param irq_tid interrupt thread id
 * @param handler_tid thread id of the handler thread
 * @return true if operation was successful
 */
bool thread_control_interrupt(threadid_t irq_tid, threadid_t handler_tid)
{
    // interrupt thread
    tcb_t * irq_tcb = get_current_space()->get_tcb(irq_tid);
    word_t irq = irq_tid.get_irqno();
    tcb_t * handler_tcb = get_current_space()->get_tcb(handler_tid);

    TRACEPOINT (SYSCALL_THREAD_CONTROL_IRQ, 
		printf("SYS_THREAD_CONTROL for IRQ%d (IRQ=%t, handler=%t)\n",
		       irq, TID(irq_tid), TID(handler_tid)) );

    // check whether this is a valid/available IRQ
    if (!irq_tid.is_interrupt() ||
	    (nTBUF_IRQ(irq) && !get_interrupt_ctrl()->is_irq_available(irq)))
	return false;

#ifndef CONFIG_PHYSICAL_KERNEL
    // allocate before usage
    if (!irq_tcb->allocate())
	return false;
#endif

    if (( handler_tcb->get_global_id() != handler_tid ))
	return false;

    /* VU: IRQ TCBs always "exist" -- so we check whether they 
     * already have a UTCB */
    if (irq_tcb->is_activated())
    {
	// check whether we really change something
	if (irq_tcb->get_irq_handler() == handler_tid)
	    return true;

#ifdef CONFIG_SMP
	if (!irq_tcb->is_local_cpu())
	{
	    xcpu_request(irq_tcb->get_cpu(), do_xcpu_thread_control_interrupt,
			 irq_tcb, handler_tid.get_raw());
	    return true;
	}
#endif
	// dequeue from handler's send queue if necessary
	if (irq_tcb->get_state().is_polling())
	{
	    tcb_t * handler_tcb = irq_tcb->get_partner_tcb();
	    handler_tcb->lock();
	    irq_tcb->dequeue_send(handler_tcb);
	    handler_tcb->unlock();
	}
    }
    else
    {
#ifdef CONFIG_PHYSICAL_KERNEL
    if (irq_tcb == dummy_tcb)
        irq_tcb = tidtable->new_tcb(irq_tid);
#endif
	irq_tcb->create_kernel_thread(irq_tid, &irq_utcb);
#ifdef CONFIG_DEBUG
#if defined(CONFIG_TRACEBUFFER)
	if (irq == tb_irq)
	{
	    char *c = irq_tcb->debug_name;
	    *c++ = 'T';
	    *c++ = 'B';
	    *c++ = ' ';
	    *c++ = 'I';
	    *c++ = 'R';
	    *c++ = 'Q';
	    *c++ = '\0';
	}
	else
#endif
	{
	    char *c = irq_tcb->debug_name;
	    *c++ = 'I';
	    *c++ = 'R';
	    *c++ = 'Q';
	    *c++ = ' ';
	    *c++ = '0' + (irq / 10) % 10;
	    *c++ = '0' + irq % 10;
	    *c++ = '\0';
	}
#endif
	/*
	 * Set the priority of the kernel interrupt thread to the
	 * maximum priority.  Note that this is not related to the
	 * priority of the actual interrupt the API is concerned with.
	 * Instead it only makes sure that, given the current
	 * implementation of the interrupt protocol, acknowledge
	 * messages are immediately acted upon.  This is necessary to
	 * match more closely the API idea of interrupts being
	 * represented as threads but having no execution time.
	 */
	get_current_scheduler()->set_priority(irq_tcb, MAX_PRIO);
	irq_tcb->notify(irq_thread);
    }

#ifdef CONFIG_SMP
    /* at this point we must be on the local CPU */
    ASSERT(DEBUG, irq_tcb->is_local_cpu());
#endif

    irq_tcb->set_irq_handler(handler_tid);

    if (irq_tid == handler_tid)
    {
	// printf("disable IRQ %d\n", irq);
	// de-activate irq thread
#if defined(CONFIG_TRACEBUFFER)
	if (irq == tb_irq)
	    tb_irq_control(false);
	else
#endif
	{
	    get_interrupt_ctrl()->disable(irq);
	}
	irq_tcb->set_state(thread_state_t::aborted);
    }
    else
    {
	// printf("enable IRQ %d\n", irq);
	irq_tcb->set_state(thread_state_t::halted);
#if defined(CONFIG_TRACEBUFFER)
	if (irq == tb_irq)
	    tb_irq_control(true);
	else
#endif
	{
	    get_interrupt_ctrl()->set_cpu(irq, irq_tcb->get_cpu());
	    get_interrupt_ctrl()->enable(irq);
	}
    }
    return true;
}

#ifdef CONFIG_SMP
void migrate_interrupt_start (tcb_t * tcb)
{
    ASSERT(NORMAL, tcb->is_interrupt_thread());
    word_t irq = tcb->get_global_id().get_irqno();

    if (tcb->get_state().is_halted())
	get_interrupt_ctrl()->mask(irq);
}

void migrate_interrupt_end (tcb_t * tcb)
{
    ASSERT(NORMAL, tcb->is_interrupt_thread());
    word_t irq = tcb->get_global_id().get_irqno();
    
    get_interrupt_ctrl()->set_cpu(get_current_cpu(), irq);
    
    if (tcb->get_state().is_halted())
	get_interrupt_ctrl()->unmask(irq);
}
#endif

#ifdef __ELF__
void SECTION(".init") init_interrupt_threads()
#elif defined(__APPLE_CC__)
void SECTION("__INIT", "__init") init_interrupt_threads()
#else
#error "unknown compiler"
#endif
{
    /* initialize KIP */
    word_t num_irqs = get_interrupt_ctrl()->get_number_irqs();
#if defined(CONFIG_TRACEBUFFER)
    tb_irq = num_irqs;
    num_irqs ++;
#endif
    get_kip()->thread_info.set_system_base(num_irqs);
    TRACE_INIT("system has %d interrupts\n", num_irqs);
}
