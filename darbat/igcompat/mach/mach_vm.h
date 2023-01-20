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
#ifndef __IG_COMPAT_MACH_VM_H__
#define __IG_COMPAT_MACH_VM_H__


kern_return_t mach_vm_protect( vm_map_t		map,
			       mach_vm_offset_t	start,
			       mach_vm_size_t	size,
			       boolean_t	set_maximum,
			       vm_prot_t	new_protection );


kern_return_t mach_vm_region_recurse( vm_map_t	                map,
				      mach_vm_address_t		*address,
				      mach_vm_size_t		*size,
				      uint32_t			*depth,
				      vm_region_recurse_info_t	info,
				      mach_msg_type_number_t 	*infoCnt );


kern_return_t mach_vm_allocate(	vm_map_t		map,
				mach_vm_offset_t	*addr,
				mach_vm_size_t	        size,
				int			flags);

kern_return_t vm_allocate( vm_map_t	map,
			   vm_offset_t	*addr,
			   vm_size_t	size,
			   int		flags );

kern_return_t mach_vm_map( vm_map_t		target_map,
			   mach_vm_offset_t	*address,
			   mach_vm_size_t	initial_size,
			   mach_vm_offset_t	mask,
			   int			flags,
			   ipc_port_t		port,
			   vm_object_offset_t	offset,
			   boolean_t		copy,
			   vm_prot_t		cur_protection,
			   vm_prot_t		max_protection,
			   vm_inherit_t		inheritance );

kern_return_t mach_vm_msync( vm_map_t		map,
			     mach_vm_address_t	address,
			     mach_vm_size_t	size,
			     vm_sync_t		sync_flags );

kern_return_t mach_vm_deallocate( vm_map_t		map,
				  mach_vm_offset_t	start,
				  mach_vm_size_t	size );

kern_return_t mach_vm_inherit( vm_map_t		map,
			       mach_vm_offset_t	start,
			       mach_vm_size_t	size,
			       vm_inherit_t		new_inheritance );

kern_return_t vm_inherit( register vm_map_t map,
			  vm_offset_t start,
			  vm_size_t size,
			  vm_inherit_t new_inheritance );

kern_return_t mach_vm_behavior_set( vm_map_t		map,
				    mach_vm_offset_t	start,
				    mach_vm_size_t	size,
				    vm_behavior_t		new_behavior );

kern_return_t vm_map_page_query( vm_map_t		map,
				 vm_offset_t		offset,
				 int			*disposition,
				 int			*ref_count );

/*
kern_return_t mach_vm_wire( host_priv_t		host_priv,
			    vm_map_t		map,
			    mach_vm_offset_t	start,
			    mach_vm_size_t	size,
			    vm_prot_t		access );
*/

kern_return_t vm_map_64( vm_map_t		target_map,
			 vm_offset_t		*address,
			 vm_size_t		size,
			 vm_offset_t		mask,
			 int			flags,
			 ipc_port_t		port,
			 vm_object_offset_t	offset,
			 boolean_t		copy,
			 vm_prot_t		cur_protection,
			 vm_prot_t		max_protection,
			 vm_inherit_t		inheritance );

kern_return_t vm_deallocate( register vm_map_t	map,
			     vm_offset_t	start,
			     vm_size_t		size );


kern_return_t vm_protect( vm_map_t		map,
			  vm_offset_t		start,
			  vm_size_t		size,
			  boolean_t		set_maximum,
			  vm_prot_t		new_protection );


kern_return_t mach_make_memory_entry( vm_map_t		target_map,
				      vm_size_t		*size,
				      vm_offset_t	offset,
				      vm_prot_t		permission,
				      ipc_port_t	*object_handle,
				      ipc_port_t	parent_entry );

kern_return_t mach_vm_machine_attribute( vm_map_t map,
					 mach_vm_address_t addr,
					 mach_vm_size_t size,
					 vm_machine_attribute_t	attribute,
					 vm_machine_attribute_val_t* value );

kern_return_t vm_machine_attribute( vm_map_t map,
				    vm_address_t addr,
				    vm_size_t size,
				    vm_machine_attribute_t attribute,
				    vm_machine_attribute_val_t* value );


kern_return_t mach_vm_read( vm_map_t map,
			    mach_vm_address_t addr,
			    mach_vm_size_t size,
			    pointer_t *data,
			    mach_msg_type_number_t *data_size );

kern_return_t vm_read( vm_map_t map,
		       vm_address_t addr,
		       vm_size_t size,
		       pointer_t *data,
		       mach_msg_type_number_t *data_size );

kern_return_t mach_vm_read_list( vm_map_t map,
				 mach_vm_read_entry_t data_list,
				 natural_t count );

kern_return_t vm_read_list( vm_map_t map,
			    vm_read_entry_t data_list,
			    natural_t count );

kern_return_t mach_vm_read_overwrite( vm_map_t map,
				      mach_vm_address_t address,
				      mach_vm_size_t size,
				      mach_vm_address_t data,
				      mach_vm_size_t *data_size );

kern_return_t vm_read_overwrite( vm_map_t map,
				 vm_address_t address,
				 vm_size_t size,
				 vm_address_t data,
				 vm_size_t *data_size );

kern_return_t mach_vm_write( vm_map_t map,
			     mach_vm_address_t address,
			     pointer_t data,
			     __unused mach_msg_type_number_t size );

kern_return_t vm_write( vm_map_t map,
			vm_address_t address,
			pointer_t data,
			__unused mach_msg_type_number_t size );

kern_return_t mach_vm_copy( vm_map_t map,
			    mach_vm_address_t source_address,
			    mach_vm_size_t size,
			    mach_vm_address_t dest_address );


kern_return_t vm_copy( vm_map_t	map,
		       vm_address_t source_address,
		       vm_size_t size,
		       vm_address_t dest_address );

kern_return_t vm_map( vm_map_t target_map,
		      vm_offset_t *address,
		      vm_size_t size,
		      vm_offset_t mask,
		      int flags,
		      ipc_port_t port,
		      vm_offset_t offset,
		      boolean_t copy,
		      vm_prot_t cur_protection,
		      vm_prot_t max_protection,
		      vm_inherit_t inheritance );

kern_return_t mach_vm_remap( vm_map_t target_map,
			     mach_vm_offset_t *address,
			     mach_vm_size_t size,
			     mach_vm_offset_t mask,
			     boolean_t anywhere,
			     vm_map_t src_map,
			     mach_vm_offset_t memory_address,
			     boolean_t copy,
			     vm_prot_t *cur_protection,
			     vm_prot_t *max_protection,
			     vm_inherit_t inheritance );

kern_return_t vm_remap( vm_map_t target_map,
			vm_offset_t *address,
			vm_size_t size,
			vm_offset_t mask,
			boolean_t anywhere,
			vm_map_t src_map,
			vm_offset_t memory_address,
			boolean_t copy,
			vm_prot_t *cur_protection,
			vm_prot_t *max_protection,
			vm_inherit_t inheritance );

kern_return_t vm_msync( vm_map_t map,
			vm_address_t address,
			vm_size_t size,
			vm_sync_t sync_flags );

kern_return_t vm_behavior_set( vm_map_t map,
			       vm_offset_t start,
			       vm_size_t size,
			       vm_behavior_t new_behavior );

kern_return_t mach_vm_region( vm_map_t map,
			      mach_vm_offset_t *address,
			      mach_vm_size_t *size,
			      vm_region_flavor_t flavor,
			      vm_region_info_t info,
			      mach_msg_type_number_t *count,
			      mach_port_t *object_name );

kern_return_t vm_region_64( vm_map_t map,
			    vm_offset_t *address,
			    vm_size_t *size,
			    vm_region_flavor_t flavor,
			    vm_region_info_t info,
			    mach_msg_type_number_t *count,
			    mach_port_t *object_name );
	
kern_return_t vm_region_recurse_64( vm_map_t map,
				    vm_address_t *address,
				    vm_size_t *size,
				    uint32_t *depth,
				    vm_region_recurse_info_64_t info,
				    mach_msg_type_number_t *infoCnt );

kern_return_t mach_vm_page_query( vm_map_t map,
				  mach_vm_offset_t offset,
				  int *disposition,
				  int *ref_count );

kern_return_t mach_make_memory_entry_64( vm_map_t target_map,
					 memory_object_size_t *size,
					 memory_object_offset_t offset,
					 vm_prot_t permission,
					 ipc_port_t *object_handle,
					 ipc_port_t parent_handle );

kern_return_t _mach_make_memory_entry( vm_map_t target_map,
				       memory_object_size_t *size,
				       memory_object_offset_t offset,
				       vm_prot_t permission,
				       ipc_port_t *object_handle,
				       ipc_port_t parent_entry );

kern_return_t mach_memory_object_memory_entry_64( host_t host,
						  boolean_t internal,
						  vm_object_offset_t size,
						  vm_prot_t permission,
						  memory_object_t pager,
						  ipc_port_t *entry_handle );

kern_return_t mach_memory_object_memory_entry( host_t host,
					       boolean_t internal,
					       vm_size_t size,
					       vm_prot_t permission,
					       memory_object_t ager,
					       ipc_port_t *entry_handle );


#endif /* __IG_COMPAT_MACH_VM_H__*/
