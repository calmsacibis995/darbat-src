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
 * Copyright (c) 2000 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 * 
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
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
 * @OSF_FREE_COPYRIGHT@
 */

#define VERBOSE 0

#include <ppc/setjmp.h>

int recursed(jmp_buf_t *bufp, int retval, int depth)
{
  int mumbojumbo[16];
  int i;
 
#if VERBOSE
  for (i=0;i<depth;i++)
    printf(" ");
  printf("in recursed(0x%x,%d,%d)\n",bufp,retval,depth);
#endif
  if (depth == 0) {
#if VERBOSE
    printf("LONGJUMPING from depth %d to buffer at 0x%x!\n",retval, bufp);
#endif
    _longjmp(bufp, retval);
    printf("SHOULDN'T GET HERE\n");
  } else {
    recursed(bufp,retval,depth-1);
  }
  return mumbojumbo[15]=-1; /* make sure we generate our own frame */
}

int testjump()
{
  jmp_buf_t  buf;
  int val;
  int i;

  printf("calling setjmp\n");

  val = _setjmp(&buf);
#if VERBOSE
  for (i=0; i<64; i++) {
    if ((i % 8) == 0) printf("\n%2d :",i);
    printf(" %8x",buf.jmp_buf[i]);
  }
#endif
  printf("\nsetjmp returned %d, structure at 0x%x\n",val,&buf);

  if (val < 5)
    recursed(&buf,val+1,val+1);

  printf("returning from setjmp/longjmp test\n");
}

