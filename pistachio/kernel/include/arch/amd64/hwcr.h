/*********************************************************************
 *                
 * Copyright (C) 2004,  Karlsruhe University
 *                
 * File path:     arch/amd64/hwcr.h
 * Description:   
 *                
 * @LICENSE@
 *                
 * $Id: hwcr.h,v 1.2 2004/06/02 18:05:04 stoess Exp $
 *                
 ********************************************************************/
#ifndef __ARCH__AMD64__HWCR_H__
#define __ARCH__AMD64__HWCR_H__

/* HWCR Bits features 26049 p289 */
#define AMD64_HWCR_SMMLOCK	( 1 <<  0)        /* SMM lock */			 
#define AMD64_HWCR_SLOWFENCE	( 1 <<  1)        /* Slow SFENCE enable */		 
#define AMD64_HWCR_TLBCACHEDIS	( 1 <<  3)        /* Cacheable memory disable*/		 
#define AMD64_HWCR_INVD_WBINVD	( 1 <<  4)        /* INVD to WBINVD conversion */	 
#define AMD64_HWCR_FFDIS	( 1 <<  6)        /* Flush filter disable*/		 
#define AMD64_HWCR_DISLOCK	( 1 <<  7)        /* x86 LOCK prefix disable  */	 
#define AMD64_HWCR_IGNNE_EM	( 1 <<  8)        /* IGNNE port emulation enable*/	 
#define AMD64_HWCR_HLTXSPCYCEN	( 1 << 12)        /* HLT special bus cyle enable  */	 
#define AMD64_HWCR_SMISPCYCDIS	( 1 << 13)        /* SMI special bus cyle disable */	 
#define AMD64_HWCR_RSMSPCYCDIS	( 1 << 14)        /* RSM special bus cyle disable */	 
#define AMD64_HWCR_SSEDIS	( 1 << 15)        /* SSE disable */			 
#define AMD64_HWCR_WRAP32DIS	( 1 << 17)        /* 32-bit address wrap disable  */	 
#define AMD64_HWCR_MCIS_WREN	( 1 << 18)        /* McI status write enable  */	 
#define AMD64_HWCR_START_FID	(63 << 19)        /* startup FID status */               


class amd64_hwcr_t{

public:
    static void dump_hwcr(){
	
	printf("HWCR register:\n");
	
	printf("\tsmmlock: %s\n"
	       "\tslowfence: %s\n"
	       "\ttlbcache: %s\n"
	       "\tinvd_wbinvd: %s\n"
	       "\tflush filter: %s\n"
	       "\tlock prefix: %s\n"
	       "\tignne emulation: %s\n"
	       "\texit from hlt special bus cycle: %s\n" 
	       "\tsmi special bus cycle: %s\n"
	       "\trsm special bus cycle: %s\n"
	       "\tsse: %s\n"
	       "\t32-bit address wrap: %s\n"
	       "\tmci status write: %s\n"
	       "\tstartup fid status: %x\n",
	       (is_smm_locked() ? "enabled" : "disabled" ),
	       (is_slowfence_enabled() ? "enabled" : "disabled" ),
	       (is_ptemem_cached() ? "enabled" : "disabled" ),
	       (is_invd_wbinvd() ? "enabled" : "disabled" ),
	       (is_flushfilter_enabled() ? "enabled" : "disabled" ),
	       (is_lockprefix_enabled() ? "enabled" : "disabled" ),
	       (is_ignne_emulation_enabled() ? "enabled" : "disabled" ),
	       (is_hltx_spc_enabled() ? "enabled" : "disabled" ), 
	       (is_smi_spc_enabled() ? "enabled" : "disabled" ),
	       (is_rsm_spc_enabled() ? "enabled" : "disabled" ),
	       (is_sse_enabled() ? "enabled" : "disabled" ),
	       (is_wrap32_enabled() ? "enabled" : "disabled" ),
	       (is_mci_status_write_enabled() ? "enabled" : "disabled" ),
	       get_startup_fid_status());
    }
    
    static bool is_smm_locked() 
    { 
	return (amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_SMMLOCK); 
    }
    static void enable_smmlock() 
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_SMMLOCK);
    }
    static void disable_smmlock()
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_SMMLOCK);
    }

    
    static bool is_slowfence_enabled() 
    { 
	return (amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_SLOWFENCE); 
    }	
    static void enable_slowfence()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_SLOWFENCE);
    }

    static void disable_slowfence()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_SMMLOCK);
    }
	
    
    static bool is_ptemem_cached() 
    { 
	return !(amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_TLBCACHEDIS); 
    }	
    static void enable_ptemem_cached()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_TLBCACHEDIS);
    }
    static void disable_ptemem_cached()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_TLBCACHEDIS);
    }
	

    static bool is_invd_wbinvd() { 
	return (amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_INVD_WBINVD); 
    }	
    static void enable_invd_wbinvd()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_INVD_WBINVD);
    }
    static void disable_invd_wbinvd()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_INVD_WBINVD);
    }


    static bool is_flushfilter_enabled() 
    { 
	return !(amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_FFDIS); 
    }

    static void enable_flushfilter()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_FFDIS);
    }
    static void disable_flushfilter()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_FFDIS);
    }


    static bool is_lockprefix_enabled() 
    {
	return !(amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_DISLOCK); 
    }	
    static void enable_lockprefix()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_DISLOCK);
    }
    static void disable_lockprefix()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_DISLOCK);
    }
	

    static bool is_ignne_emulation_enabled() 
    {
	return (amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_IGNNE_EM); 
    }	
    static void enable_ignne_emulation()
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_IGNNE_EM);
    }
    static void disable_ignne_emulation()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_IGNNE_EM);
    }

    
    static bool is_hltx_spc_enabled() 
    {
	return (amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_HLTXSPCYCEN);
    }	
    static void enable_hltx_spc()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_HLTXSPCYCEN);
    }
    static void disable_hltx_spc()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_HLTXSPCYCEN);
    }


    static bool is_smi_spc_enabled()
    { 
	return !(amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_SMISPCYCDIS); 
    }	
    static void enable_smi_spc()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_SMISPCYCDIS);
    }
    static void disable_smi_spc()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_SMISPCYCDIS);
    }


    static bool is_rsm_spc_enabled() 
    { 
	return !(amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_RSMSPCYCDIS); 
    }	
    static void enable_rsm_spc()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_RSMSPCYCDIS);
    }
    static void disable_rsm_spc()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_RSMSPCYCDIS);
    }


    static bool is_sse_enabled()
    { 
	return !(amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_SSEDIS); 
    }
    static void enable_sse()   
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_SSEDIS);
    }
    static void disable_sse()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_SSEDIS);
    }

    
	
    static bool is_wrap32_enabled() 
    { 
	return !(amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_WRAP32DIS); 
    }	
    static void enable_wrap32()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_WRAP32DIS);
    }

    static void disable_wrap32()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_WRAP32DIS);
    }

    

    static bool is_mci_status_write_enabled() 
    { 
	return (amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_MCIS_WREN); 
    }
    static void enable_mci_status_write()   
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr | AMD64_HWCR_MCIS_WREN);
    }
	
    static void disable_mci_status_write()    
    {
	u64_t hwcr = amd64_rdmsr(AMD64_HWCR_MSR);
	amd64_wrmsr(AMD64_HWCR_MSR, hwcr & ~AMD64_HWCR_MCIS_WREN);
    }

    static u8_t get_startup_fid_status()    {
	return (u8_t) ((amd64_rdmsr(AMD64_HWCR_MSR) & AMD64_HWCR_START_FID) >> 19);
    }
	
};



#endif /* !__ARCH__AMD64__HWCR_H__ */
