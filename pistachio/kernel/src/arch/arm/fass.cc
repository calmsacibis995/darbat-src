/********************************************************************
 *
 * Copyright (C) 2003-2005,  National ICT Australia (NICTA)
 *
 * File path:     arch/arm/fass.c
 * Description:   FASS functionality
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
 * $Id: fass.cc,v 1.13 2004/09/08 08:35:25 cvansch Exp $
 *
 ********************************************************************/

#ifdef CONFIG_ENABLE_FASS

#include <macros.h>
#include <types.h>
#include <config.h>
#include INC_API(space.h)
#include INC_ARCH(fass.h)
#include INC_ARCH(special.h)
#include INC_API(tcb.h)
#include <kdb/tracepoints.h>


FEATURESTRING ("PIDs");


DECLARE_TRACEPOINT(ARM_FASS_RECYCLE);

arm_fass_t arm_fass;

void arm_fass_t::init(void)
{
    domain_dirty = 0;
    arm_fass.domain_space[0] = get_kernel_space();
    get_kernel_space()->set_domain(0);
    next_rr = 1;
}

void arm_fass_t::clean_all(word_t flush)
{
    if (flush) {
	domain_dirty = 0;
	SET_BIT_WORD(domain_dirty, current_domain);
	arm_cache::cache_flush();
    }

    arm_cache::tlb_flush();
}

/* Choose a domain to replace - try select a clean domain, otherwise replace one.
 * Should consider using a more sophisticated selection if
 * it will buy anything (for example, consider the number of CPD slots used by
 * the domains). Also, should consider moving this to user-level.
 */ 
int arm_fass_t::replacement_domain(void)
{
    word_t i = next_rr;	    /* Round robin pointer */

    /* First search for a clean domain */
    do {
        if (!TEST_BIT_WORD(domain_dirty, i))
	{
	    next_rr = i;

	    ASSERT(NORMAL, i != current_domain);
            return i;
	}
	i = (i + 1) % ARM_DOMAINS;
	i = i ? i : 1;	    /* Don't select domain 0 */
    } while (i != next_rr);

    /* Pick the next available domain */
    do {
	i = next_rr;

	next_rr = (next_rr + 1) % ARM_DOMAINS;
	next_rr = next_rr ? next_rr : 1;	/* Can't use domain 0 */
    } while (i == current_domain);

    ASSERT(NORMAL, i != current_domain);
    return i;
}

arm_domain_t arm_fass_t::domain_recycle(space_t *space)
{
    arm_domain_t target;
    space_t *old_space;
    word_t flush = 0;

    target = replacement_domain();

    TRACEPOINT(ARM_FASS_RECYCLE,
        printf("Recycling domain %d for %p\n", target, space));

    old_space = domain_space[target];

    if (old_space)
    {
	word_t old_vspace = old_space->get_vspace();

        old_space->set_domain(INVALID_DOMAIN);

	if ((!old_vspace) || (space->get_vspace() != old_vspace))
	    flush = 1;
    }

    space->set_domain(target);

    domain_space[target] = space;

    /* Remove the elements in the CPD belonging to the domain to be
     * recycled.
     */
    for (word_t i = 0, j; i < CPD_BITFIELD_ARRAY_SIZE; ++i) {
	j = cpd_set[target][i];

	if (j) {
	    do {
		word_t k = msb(j);

		word_t section = i * CPD_BITFIELD_WORD_SIZE + k;
		get_cpd()->pt.pdir[section].raw = 0;

		j &= ~(1 << k);
	    } while (j);

	    cpd_set[target][i] = 0;
	}
    }

    if (old_space) {
	/* Remove mapping to UTCBs from old_space */
	word_t section = ( UTCB_AREA_START/ARM_SECTION_SIZE +
			(old_space->get_utcb_section()) );
	// TRACEF("save old_space %p utcb cpd section %d\n", old_space, section);
	pgent_t entry;
	entry.raw = (word_t)old_space;
	get_cpd()->pt.pdir[section] = entry;
    }

//    if (TEST_BIT_WORD(domain_dirty, target))
//        clean_all(flush);
    clean_all(true);

    return target;
}

space_t *arm_fass_t::get_space(arm_domain_t domain)
{
    if (domain == INVALID_DOMAIN)
        return NULL;

    return domain_space[domain];
}

void arm_fass_t::set_space(arm_domain_t domain, space_t *space)
{
    if (domain != INVALID_DOMAIN)
        domain_space[domain] = space;
}



#endif /* CONFIG_ENABLE_FASS */
