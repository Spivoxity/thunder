/*
 * vmalloc.c
 * 
 * This file is part of the Oxford Oberon-2 compiler
 * Copyright (c) 2006--2016 J. M. Spivey
 * All rights reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef LINUX
#include <sys/mman.h>

#ifdef M64X32
#define MMAP_FLAGS MAP_PRIVATE|MAP_32BIT|MAP_ANONYMOUS
#else
#define MMAP_FLAGS MAP_PRIVATE|MAP_ANONYMOUS
#endif

void *vm_alloc(int size) {
     static void *last_addr = NULL;

     // Round up to whole pages
     size = (size + PAGESIZE - 1) & ~(PAGESIZE-1);

     void *p = mmap(last_addr, size, PROT_READ|PROT_WRITE, MMAP_FLAGS, -1, 0);

     if (p == MAP_FAILED) return NULL;

#ifdef M64X32
     if ((((unsigned long) p) & ~0x7fffffff) != 0) {
          fprintf(stderr, "inaccessible memory allocated at %p", p);
          exit(2);
     }
#endif

     last_addr = p + size;
     return p;
}

#else

void *vm_alloc(int size) {
     void *mem = NULL;
     if (posix_memalign(&mem, 4096, size) < 0) {
          fprintf(stderr, "Allocation failed\n");
          exit(2);
     }

     printf("Alloc %d at %p\n", size, mem);

     return mem;
}

#endif
