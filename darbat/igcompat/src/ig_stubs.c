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
#include <stdio.h>
#include <assert.h>


#define HACK_SYM(sym)                  \
    void sym(void);    \
	void sym(void) { printf( "%s (caller %p)\n", __func__, (void*) __builtin_return_address(0) ); assert(0); }


/* ceg hack */
HACK_SYM(_thread_setcurrent)

/*** some hand hacks ***/
HACK_SYM(kvtophys) // TEXT
HACK_SYM(cngetc) // TEXT
//HACK_SYM(mach_absolute_time)

/*** domains ***/
#if 0
HACK_SYM(inetdomain)
#endif
#if 0
HACK_SYM(inet6domain)
#endif

/*** video ***/
HACK_SYM(switch_to_serial_console)
HACK_SYM(io_map_spec)

/***  other stuff ***/

HACK_SYM(Debugger)
HACK_SYM(IOBSDRegistryEntryForDeviceTree)
HACK_SYM(IOBSDRegistryEntryGetData)
HACK_SYM(IOBSDRegistryEntryRelease)
HACK_SYM(IODTFreeLoaderInfo)
HACK_SYM(IODTGetLoaderInfo)
HACK_SYM(IOMapperInsertPage)
HACK_SYM(IOSleep)
//HACK_SYM(PEGetMachineName)
//HACK_SYM(PEGetModelName)
HACK_SYM(PEGetPlatformEpoch)
#ifndef __APPLE_CC__
HACK_SYM(_mh_execute_header)
#endif
HACK_SYM(act_thread_catt)
HACK_SYM(act_thread_csave)
//HACK_SYM(bootp)
HACK_SYM(bsd_exception) // TEXT
HACK_SYM(bsd_log_lock) // TEXT
HACK_SYM(bsd_log_unlock) // TEXT
//HACK_SYM(clock_absolutetime_interval_to_deadline)
//HACK_SYM(clock_get_calendar_nanotime)
//HACK_SYM(clock_get_uptime)
//HACK_SYM(clock_interval_to_absolutetime_interval)
//HACK_SYM(clock_set_calendar_microtime)
HACK_SYM(clr_be_bit) // TEXT
HACK_SYM(cnputc) // TEXT
HACK_SYM(coredumpok) // TEXT
// void count_busy_buffers(void) { printf( "%s\n", __func__ ); assert(0); }
HACK_SYM(current_act) // TEXT
//HACK_SYM(dhcpol_find)
//HACK_SYM(dhcpol_parse_packet)
HACK_SYM(di_root_image) // TEXT
HACK_SYM(get_user_regs) // TEXT
HACK_SYM(get_useraddr) // TEXT
//HACK_SYM(in_cksum_offset)
//HACK_SYM(in_delayed_cksum_offset)
// HACK_SYM(inet_ntop) // TEXT
//HACK_SYM(kprintf)
HACK_SYM(m_mbigget) // TEXT
//HACK_SYM(ml_cpu_get_info)
// void mountlist(void) { printf( "%s\n", __func__ ); assert(0); }

//HACK_SYM(nanoseconds_to_absolutetime)
//HACK_SYM(nfs_mountroot)
HACK_SYM(nosys) // TEXT
HACK_SYM(panic_dialog_get_image)
HACK_SYM(panic_dialog_set_image)
HACK_SYM(panic_dialog_test)
// void rootvnode(void) { printf( "%s\n", __func__ ); assert(0); }
HACK_SYM(sys_perf_notify)
/*
HACK_SYM(sysctl__net_inet)
HACK_SYM(sysctl__net_inet_icmp)
HACK_SYM(sysctl__net_inet_icmp_bmcastecho)
HACK_SYM(sysctl__net_inet_icmp_drop_redirect)
HACK_SYM(sysctl__net_inet_icmp_icmplim)
HACK_SYM(sysctl__net_inet_icmp_log_redirect)
HACK_SYM(sysctl__net_inet_icmp_maskrepl)
HACK_SYM(sysctl__net_inet_icmp_stats)
HACK_SYM(sysctl__net_inet_icmp_timestamp)
HACK_SYM(sysctl__net_inet_igmp)
HACK_SYM(sysctl__net_inet_igmp_stats)
HACK_SYM(sysctl__net_inet_ip)
HACK_SYM(sysctl__net_inet_ip_accept_sourceroute)
HACK_SYM(sysctl__net_inet_ip_check_interface)
HACK_SYM(sysctl__net_inet_ip_check_route_selfref)
HACK_SYM(sysctl__net_inet_ip_fastforwarding)
HACK_SYM(sysctl__net_inet_ip_forwarding)
HACK_SYM(sysctl__net_inet_ip_intr_queue_drops)
HACK_SYM(sysctl__net_inet_ip_intr_queue_maxlen)
HACK_SYM(sysctl__net_inet_ip_keepfaith)
HACK_SYM(sysctl__net_inet_ip_linklocal)
HACK_SYM(sysctl__net_inet_ip_linklocal_in)
HACK_SYM(sysctl__net_inet_ip_linklocal_in_allowbadttl)
HACK_SYM(sysctl__net_inet_ip_linklocal_stat)
HACK_SYM(sysctl__net_inet_ip_maxchainsent)
HACK_SYM(sysctl__net_inet_ip_maxfragpackets)
HACK_SYM(sysctl__net_inet_ip_maxfrags)
HACK_SYM(sysctl__net_inet_ip_maxfragsperpacket)
HACK_SYM(sysctl__net_inet_ip_mtu)
HACK_SYM(sysctl__net_inet_ip_portrange)
HACK_SYM(sysctl__net_inet_ip_portrange_first)
HACK_SYM(sysctl__net_inet_ip_portrange_hifirst)
HACK_SYM(sysctl__net_inet_ip_portrange_hilast)
HACK_SYM(sysctl__net_inet_ip_portrange_last)
HACK_SYM(sysctl__net_inet_ip_portrange_lowfirst)
HACK_SYM(sysctl__net_inet_ip_portrange_lowlast)
HACK_SYM(sysctl__net_inet_ip_redirect)
HACK_SYM(sysctl__net_inet_ip_rtexpire)
HACK_SYM(sysctl__net_inet_ip_rtmaxcache)
HACK_SYM(sysctl__net_inet_ip_rtminexpire)
HACK_SYM(sysctl__net_inet_ip_sourceroute)
HACK_SYM(sysctl__net_inet_ip_stats)
HACK_SYM(sysctl__net_inet_ip_subnets_are_local)
HACK_SYM(sysctl__net_inet_ip_ttl)
HACK_SYM(sysctl__net_inet_ip_use_route_genid)
HACK_SYM(sysctl__net_inet_raw)
HACK_SYM(sysctl__net_inet_raw_maxdgram)
HACK_SYM(sysctl__net_inet_raw_pcblist)
HACK_SYM(sysctl__net_inet_raw_recvspace)
HACK_SYM(sysctl__net_inet_tcp)
HACK_SYM(sysctl__net_inet_tcp_always_keepalive)
HACK_SYM(sysctl__net_inet_tcp_blackhole)
HACK_SYM(sysctl__net_inet_tcp_delacktime)
HACK_SYM(sysctl__net_inet_tcp_delayed_ack)
HACK_SYM(sysctl__net_inet_tcp_do_tcpdrain)
HACK_SYM(sysctl__net_inet_tcp_icmp_may_rst)
HACK_SYM(sysctl__net_inet_tcp_isn_reseed_interval)
HACK_SYM(sysctl__net_inet_tcp_keepidle)
HACK_SYM(sysctl__net_inet_tcp_keepinit)
HACK_SYM(sysctl__net_inet_tcp_keepintvl)
HACK_SYM(sysctl__net_inet_tcp_local_slowstart_flightsize)
HACK_SYM(sysctl__net_inet_tcp_log_in_vain)
HACK_SYM(sysctl__net_inet_tcp_minmss)
HACK_SYM(sysctl__net_inet_tcp_minmssoverload)
HACK_SYM(sysctl__net_inet_tcp_msl)
HACK_SYM(sysctl__net_inet_tcp_mssdflt)
HACK_SYM(sysctl__net_inet_tcp_newreno)
HACK_SYM(sysctl__net_inet_tcp_packetchain)
HACK_SYM(sysctl__net_inet_tcp_path_mtu_discovery)
HACK_SYM(sysctl__net_inet_tcp_pcbcount)
HACK_SYM(sysctl__net_inet_tcp_pcblist)
HACK_SYM(sysctl__net_inet_tcp_reass)
HACK_SYM(sysctl__net_inet_tcp_reass_cursegments)
HACK_SYM(sysctl__net_inet_tcp_reass_maxsegments)
HACK_SYM(sysctl__net_inet_tcp_reass_overflows)
HACK_SYM(sysctl__net_inet_tcp_recvspace)
HACK_SYM(sysctl__net_inet_tcp_rfc1323)
HACK_SYM(sysctl__net_inet_tcp_rfc1644)
HACK_SYM(sysctl__net_inet_tcp_sendspace)
HACK_SYM(sysctl__net_inet_tcp_slowlink_wsize)
HACK_SYM(sysctl__net_inet_tcp_slowstart_flightsize)
HACK_SYM(sysctl__net_inet_tcp_sockthreshold)
HACK_SYM(sysctl__net_inet_tcp_stats)
HACK_SYM(sysctl__net_inet_tcp_strict_rfc1948)
HACK_SYM(sysctl__net_inet_tcp_tcbhashsize)
HACK_SYM(sysctl__net_inet_tcp_tcp_lq_overflow)
HACK_SYM(sysctl__net_inet_udp)
HACK_SYM(sysctl__net_inet_udp_blackhole)
HACK_SYM(sysctl__net_inet_udp_checksum)
HACK_SYM(sysctl__net_inet_udp_log_in_vain)
HACK_SYM(sysctl__net_inet_udp_maxdgram)
HACK_SYM(sysctl__net_inet_udp_pcbcount)
HACK_SYM(sysctl__net_inet_udp_pcblist)
HACK_SYM(sysctl__net_inet_udp_recvspace)
HACK_SYM(sysctl__net_inet_udp_stats)
HACK_SYM(sysctl__net_link_ether_inet)
HACK_SYM(sysctl__net_link_ether_inet_apple_hwcksum_rx)
HACK_SYM(sysctl__net_link_ether_inet_apple_hwcksum_tx)
HACK_SYM(sysctl__net_link_ether_inet_host_down_time)
HACK_SYM(sysctl__net_link_ether_inet_log_arp_warnings)
HACK_SYM(sysctl__net_link_ether_inet_max_age)
HACK_SYM(sysctl__net_link_ether_inet_maxtries)
HACK_SYM(sysctl__net_link_ether_inet_proxyall)
HACK_SYM(sysctl__net_link_ether_inet_prune_intvl)
HACK_SYM(sysctl__net_link_ether_inet_useloopback)
*/
//HACK_SYM(task_importance)
//HACK_SYM(thread_adjuserstack)
//HACK_SYM(thread_entrypoint)
HACK_SYM(thread_set_parent)
//HACK_SYM(thread_userstack)
//HACK_SYM(unix_syscall_return)
HACK_SYM(ux_handler_init)
const char version[] = "1337";
const char osrelease[] = "Prerelease";
const char ostype[] = "Darwin/L4/x86";
//HACK_SYM(version)
HACK_SYM(vndevice_root_image)


/**** undefined refernce in vfs ****/

//HACK_SYM(fifo_vnodeop_opv_desc)
HACK_SYM(strncasecmp)
//HACK_SYM(tcp_recvspace)
//HACK_SYM(tcp_sendspace)



/**** undefined refernce in net ****/
//HACK_SYM(arp_ifinit)
//HACK_SYM(arp_ip_handle_input)
//HACK_SYM(arp_lookup_ip)
HACK_SYM(bond_family_init)
//HACK_SYM(check_routeselfref)
//HACK_SYM(ipv4_ll_arp_aware)
HACK_SYM(kdp_get_interface)
HACK_SYM(kdp_set_gateway_mac)
HACK_SYM(kdp_set_ip_and_mac_addresses)
//HACK_SYM(mrt_ioctl)
//HACK_SYM(nd6_lookup_ipv6)
//HACK_SYM(nd6_setmtu)
/*
HACK_SYM(sysctl__net_inet6)
HACK_SYM(sysctl__net_inet6_icmp6)
HACK_SYM(sysctl__net_inet6_icmp6_errppslimit)
HACK_SYM(sysctl__net_inet6_icmp6_nd6_debug)
HACK_SYM(sysctl__net_inet6_icmp6_nd6_delay)
HACK_SYM(sysctl__net_inet6_icmp6_nd6_maxnudhint)
HACK_SYM(sysctl__net_inet6_icmp6_nd6_mmaxtries)
HACK_SYM(sysctl__net_inet6_icmp6_nd6_prune)
HACK_SYM(sysctl__net_inet6_icmp6_nd6_umaxtries)
HACK_SYM(sysctl__net_inet6_icmp6_nd6_useloopback)
HACK_SYM(sysctl__net_inet6_icmp6_nodeinfo)
HACK_SYM(sysctl__net_inet6_icmp6_rediraccept)
HACK_SYM(sysctl__net_inet6_icmp6_redirtimeout)
HACK_SYM(sysctl__net_inet6_icmp6_stats)
HACK_SYM(sysctl__net_inet6_ip6)
HACK_SYM(sysctl__net_inet6_ip6_accept_rtadv)
HACK_SYM(sysctl__net_inet6_ip6_auto_flowlabel)
HACK_SYM(sysctl__net_inet6_ip6_auto_linklocal)
HACK_SYM(sysctl__net_inet6_ip6_dad_count)
HACK_SYM(sysctl__net_inet6_ip6_defmcasthlim)
HACK_SYM(sysctl__net_inet6_ip6_forwarding)
HACK_SYM(sysctl__net_inet6_ip6_gifhlim)
HACK_SYM(sysctl__net_inet6_ip6_hdrnestlimit)
HACK_SYM(sysctl__net_inet6_ip6_hlim)
HACK_SYM(sysctl__net_inet6_ip6_kame_version)
HACK_SYM(sysctl__net_inet6_ip6_keepfaith)
HACK_SYM(sysctl__net_inet6_ip6_log_interval)
HACK_SYM(sysctl__net_inet6_ip6_maxfragpackets)
HACK_SYM(sysctl__net_inet6_ip6_maxfrags)
HACK_SYM(sysctl__net_inet6_ip6_mrt6stat)
HACK_SYM(sysctl__net_inet6_ip6_redirect)
HACK_SYM(sysctl__net_inet6_ip6_rip6stats)
HACK_SYM(sysctl__net_inet6_ip6_rr_prune)
HACK_SYM(sysctl__net_inet6_ip6_rtexpire)
HACK_SYM(sysctl__net_inet6_ip6_rtmaxcache)
HACK_SYM(sysctl__net_inet6_ip6_rtminexpire)
HACK_SYM(sysctl__net_inet6_ip6_stats)
HACK_SYM(sysctl__net_inet6_ip6_temppltime)
HACK_SYM(sysctl__net_inet6_ip6_tempvltime)
HACK_SYM(sysctl__net_inet6_ip6_use_deprecated)
HACK_SYM(sysctl__net_inet6_ip6_use_tempaddr)
HACK_SYM(sysctl__net_inet6_ip6_v6only)
*/
//HACK_SYM(sysctl__net_inet_tcp_v6mssdflt)
//HACK_SYM(use_routegenid)
HACK_SYM(vlan_family_init)



/**** undefined references in Mach VM ****/


HACK_SYM(default_pager_triggers)
//HACK_SYM(ipc_object_translate)

HACK_SYM(_vm_external_state_get)
//HACK_SYM(pmap_is_modified)
HACK_SYM(vm_external_create)
HACK_SYM(vm_external_state_clr)


HACK_SYM(ps_vstruct_allocated_pages)
HACK_SYM(ps_vstruct_allocated_size)
HACK_SYM(ps_vstruct_create)
HACK_SYM(ps_vstruct_dealloc)
HACK_SYM(pvs_cluster_read)
HACK_SYM(vs_cluster_write)

HACK_SYM(device_data_action)
HACK_SYM(device_close)

HACK_SYM(fillPage)
//HACK_SYM(pmap_copy_page)
HACK_SYM(pmap_copy_part_page)


HACK_SYM(aes_decrypt_cbc)
HACK_SYM(aes_decrypt_key)
HACK_SYM(aes_encrypt_cbc)
HACK_SYM(aes_encrypt_key)
HACK_SYM(consider_machine_adjust)
HACK_SYM(consider_machine_collect)
//HACK_SYM(pmap_is_referenced)
//HACK_SYM(sysclk_gettime)


HACK_SYM(pmap_sync_page_attributes_phys)


HACK_SYM(_kernel_preempt_check)

    // TGB UP TO HERE CHECKING STUFF

// in kalloc.c
//HACK_SYM(kalloc_map)


/* BSD vm -- how did I miss this? */

HACK_SYM(default_pager_add_file)
HACK_SYM(default_pager_backing_store_create)
HACK_SYM(default_pager_backing_store_delete)
HACK_SYM(default_pager_info_64)
HACK_SYM(start_def_pager)


/* pulling in more of mach */

/* mach/task.c */

//HACK_SYM(KERNEL_AUDIT_TOKEN)
//HACK_SYM(KERNEL_SECURITY_TOKEN)
//HACK_SYM(absolutetime_to_microtime)
//HACK_SYM(ipc_object_release)
// src/hacks.c please
//HACK_SYM(timer_grab)


/* mach/thread.c */

HACK_SYM(machine_thread_set_state)
//HACK_SYM(thread_depress_expire)


/* a couple more */

//HACK_SYM(commpage_populate)
HACK_SYM(cpu_exit_wait)
HACK_SYM(cpu_sleep)
HACK_SYM(halt_all_cpus)
HACK_SYM(machine_boot_info)
HACK_SYM(machine_processor_shutdown)
HACK_SYM(ml_cpu_down)
//HACK_SYM(slave_machine_init)
// not right but should be ok (version major and minor)


//HACK_SYM(cause_ast_check)
HACK_SYM(machine_signal_idle)
HACK_SYM(ml_get_interrupts_enabled)

/* processor.c */

HACK_SYM(cpu_control)
HACK_SYM(cpu_start)
//HACK_SYM(slot_type)


/* kalloc.c */

HACK_SYM(hw_compare_and_store)


/* ipc_space.c */

//HACK_SYM(ipc_right_clean)
//HACK_SYM(ipc_right_destroy)

/* ipc_port.c */

//HACK_SYM(io_free)
//HACK_SYM(ipc_entry_lookup)
//HACK_SYM(ipc_kmsg_free)
HACK_SYM(ipc_notify_dead_name)
//HACK_SYM(ipc_notify_no_senders)
HACK_SYM(ipc_notify_port_destroyed)
HACK_SYM(ipc_notify_send_once)
//HACK_SYM(ipc_object_alloc)
//HACK_SYM(ipc_object_alloc_name)
//HACK_SYM(ipc_object_copyout)
//HACK_SYM(ipc_pset_remove_from_all)


/* ipc_kobject.c */

//HACK_SYM(ipc_kmsg_alloc)
//HACK_SYM(ipc_kmsg_destroy)


/* sync_sema.c */

//HACK_SYM(port_name_to_semaphore)
//HACK_SYM(thread_syscall_return)

/* mk_timer.c */

//HACK_SYM(mach_port_allocate_qos)
HACK_SYM(mach_msg_send_from_kernel)
//HACK_SYM(mach_port_destroy)

/* ipc_mqueue.c */

//HACK_SYM(ipc_kmsg_copyout_size)
//HACK_SYM(ipc_kmsg_dequeue)
//HACK_SYM(ipc_kmsg_destroy_dest)
//HACK_SYM(ipc_kmsg_queue_next)
//HACK_SYM(ipc_kmsg_rmqueue)
//HACK_SYM(mach_msg_receive_continue)


/* timer_call.c */

//HACK_SYM(clock_set_timer_func)

/* kmod.c */

HACK_SYM(kdb_printf)
HACK_SYM(ml_static_mfree)
HACK_SYM(ml_static_ptovirt)

/* clock.c */

    /*
HACK_SYM(clock_adjust_calendar)
HACK_SYM(clock_alarm_reply)
HACK_SYM(clock_count)
HACK_SYM(clock_list)
HACK_SYM(clock_set_calendar_adjtime)
HACK_SYM(clock_timebase_info)
HACK_SYM(ipc_clock_enable)
HACK_SYM(ipc_clock_init)
HACK_SYM(machine_delay_until)
HACK_SYM(port_name_to_clock)
*/


/* task_working_set.c */

HACK_SYM(pmap_remove_some_phys)

/* ipc_tt.c */

//HACK_SYM(ipc_object_copyin)

/* stack.c */


/* ufs_vnops.c */

HACK_SYM(chkdq)
HACK_SYM(chkiq)
HACK_SYM(getinoquota)
HACK_SYM(getquota)
HACK_SYM(qsync)
HACK_SYM(quotaoff)
HACK_SYM(quotaon)
HACK_SYM(quotastat)
HACK_SYM(setquota)
HACK_SYM(setuse)


/* thread_act.c */

//HACK_SYM(machine_thread_dup)
HACK_SYM(machine_thread_get_state)
//HACK_SYM(machine_thread_state_initialize)
//HACK_SYM(thread_depress_abort_internal)
//HACK_SYM(thread_set_child)
//HACK_SYM(thread_state)

/* syscalls! */
HACK_SYM(iokit_user_client_trap)
//HACK_SYM(ipc_object_destroy)
//HACK_SYM(ipc_object_copyout_dest)
//HACK_SYM(ipc_object_copyout_to_kernel)
//HACK_SYM(copyinmsg)
//HACK_SYM(copyoutmsg)
//HACK_SYM(ipc_entry_dealloc)
//HACK_SYM(ipc_entry_get)
//HACK_SYM(ipc_entry_grow_table)
HACK_SYM(ipc_notify_port_deleted)
//HACK_SYM(ipc_object_copyin_from_kernel)
//HACK_SYM(ipc_object_copyin_type)
//HACK_SYM(ipc_right_copyin)
//HACK_SYM(ipc_right_copyin_check)
//HACK_SYM(ipc_right_copyin_two)
//HACK_SYM(ipc_right_copyout)
//HACK_SYM(ipc_right_reverse)
//

//HACK_SYM(convert_clock_ctrl_to_port)
//HACK_SYM(convert_clock_to_port)
//HACK_SYM(convert_lock_set_to_port)
//HACK_SYM(convert_port_to_clock)
//HACK_SYM(convert_port_to_clock_ctrl)
//HACK_SYM(convert_port_to_lock_set)
//HACK_SYM(convert_port_to_semaphore)
//HACK_SYM(convert_semaphore_to_port)
HACK_SYM(disable_bluebox)
HACK_SYM(enable_bluebox)
HACK_SYM(host_get_UNDServer)
HACK_SYM(host_load_symbol_table)
HACK_SYM(host_set_UNDServer)
HACK_SYM(host_virtual_physical_table_info)
HACK_SYM(mach_vm_region_info)
HACK_SYM(mach_vm_region_info_64)
HACK_SYM(task_get_emulation_vector)
HACK_SYM(task_policy_get)
HACK_SYM(task_policy_set)
HACK_SYM(task_sample)
HACK_SYM(task_set_emulation)
HACK_SYM(task_set_emulation_vector)
//HACK_SYM(thread_policy)
HACK_SYM(thread_sample)
HACK_SYM(thread_set_policy)
HACK_SYM(vm_mapped_pages_info)

// Clock stuff
//HACK_SYM(thread_syscall_return)
#if 0	/* netkey is in kernel now */
HACK_SYM(sysctl__net_key)
HACK_SYM(sysctl__net_key_debug)
HACK_SYM(sysctl__net_key_prefered_oldsa)
HACK_SYM(sysctl__net_key_spi_trycnt)
HACK_SYM(sysctl__net_key_spi_minval)
HACK_SYM(sysctl__net_key_spi_maxval)
HACK_SYM(sysctl__net_key_int_random)
HACK_SYM(sysctl__net_key_larval_lifetime)
HACK_SYM(sysctl__net_key_blockacq_count)
HACK_SYM(sysctl__net_key_blockacq_lifetime)
HACK_SYM(sysctl__net_key_esp_keymin)
HACK_SYM(sysctl__net_key_esp_auth)
HACK_SYM(sysctl__net_key_ah_keymin)
HACK_SYM(sysctl__net_key_natt_keepalive_interval)
HACK_SYM(sysctl__net_key_pfkeystat)
#endif

HACK_SYM(BF_decrypt)
HACK_SYM(BF_encrypt)
HACK_SYM(BF_set_key)
HACK_SYM(cast128_decrypt_round12)
HACK_SYM(cast128_decrypt_round16)
HACK_SYM(cast128_encrypt_round12)
HACK_SYM(cast128_encrypt_round16)
HACK_SYM(deflate)
HACK_SYM(deflateInit2_)
HACK_SYM(deflateReset)
HACK_SYM(des_ecb3_encrypt)
HACK_SYM(des_ecb_encrypt)
HACK_SYM(des_is_weak_key)
HACK_SYM(des_key_sched)
HACK_SYM(gen_tabs)
HACK_SYM(inflate)
HACK_SYM(inflateInit2_)
HACK_SYM(inflateReset)
#if 0	/*NETKEY in kernel now */
HACK_SYM(key_allocsa)
HACK_SYM(key_allocsp)
HACK_SYM(key_checkrequest)
HACK_SYM(key_checktunnelsanity)
HACK_SYM(key_freesav)
HACK_SYM(key_freesp)
HACK_SYM(key_gettunnel)
HACK_SYM(key_msg2sp)
HACK_SYM(key_newsp)
HACK_SYM(key_randomfill)
HACK_SYM(key_sa_recordxfer)
HACK_SYM(key_sa_routechange)
HACK_SYM(key_sa_stir_iv)
HACK_SYM(key_sp2msg)
HACK_SYM(key_spdacquire)
#endif
#if 0
HACK_SYM(natt_now)
#endif
HACK_SYM(ovbcopy)
// already here
//HACK_SYM(read_random)
#if 0
HACK_SYM(sadb_mutex)
#endif
HACK_SYM(set_cast128_subkey)
HACK_SYM(sha1_init)
HACK_SYM(sha1_loop)
HACK_SYM(sha1_result)
HACK_SYM(SHA256_Final)
HACK_SYM(SHA256_Init)
HACK_SYM(SHA256_Update)
HACK_SYM(SHA384_Final)
HACK_SYM(SHA384_Init)
HACK_SYM(SHA384_Update)
HACK_SYM(SHA512_Final)
HACK_SYM(SHA512_Init)
HACK_SYM(SHA512_Update)

// Notify stuff
HACK_SYM(catch_exception_raise)
HACK_SYM(catch_exception_raise_state)
HACK_SYM(catch_exception_raise_state_identity)
HACK_SYM(do_mach_notify_port_destroyed)
HACK_SYM(do_mach_notify_send_once)
HACK_SYM(do_mach_notify_dead_name)
HACK_SYM(do_mach_notify_port_deleted)
HACK_SYM(do_mach_notify_no_senders)

/* TGB's DATA symbols */
HACK_SYM(LockTimeOut)
HACK_SYM(backing_store_release_trigger_disable)
HACK_SYM(c_thread_invoke_csw)
HACK_SYM(c_thread_invoke_hits)
HACK_SYM(c_thread_invoke_misses)
HACK_SYM(debug_mode)
//HACK_SYM(default_pager_object)
HACK_SYM(gPEClockFrequencyInfo)
//HACK_SYM(max_mem)
//HACK_SYM(mem_size)
HACK_SYM(my_name)
HACK_SYM(not_in_kdp)
HACK_SYM(panicstr)
HACK_SYM(pc_trace_buf)
HACK_SYM(pc_trace_cnt)
HACK_SYM(sysctl__debug_iokit)
HACK_SYM(systemLogDiags)
HACK_SYM(version_major)
HACK_SYM(version_minor)
//HACK_SYM(vm_page_mask)
