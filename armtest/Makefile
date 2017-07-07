#
# Makefile.  Generated from Makefile.in by configure.
#
# thunder/Makefile.in
# 
# This file is part of the Oxford Oberon-2 compiler
# Copyright (c) 2006--2016 J. M. Spivey
# All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
# 3. The name of the author may not be used to endorse or promote products
#    derived from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
# OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
# IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

# Config stuff
CC = arm-linux-gnueabihf-gcc
AR = arm-linux-gnueabihf-ar
RANLIB = arm-linux-gnueabihf-ranlib
CFLAGS = -g -O2
RTFLAGS = ${CFLAGS} -fno-strict-aliasing
SHELL = /bin/sh
DEBUG = 1
VPATH = ../lib
PAGESIZE = 4096
VM = vmpi.o
# End

vpath %.c ..
vpath %.h ..

all: libthunder.a

ALL_CFLAGS = $(RTFLAGS) -Wall -I ..

libthunder.a: $(VM) labels.o vmdebug.o codebuf.o
	$(AR) cr $@ $^; $(RANLIB) $@

%.o : %.c
	$(CC) $(ALL_CFLAGS) -c $< -o $@

fact: fact.o libthunder.a
	$(CC) $^ -o $@

mgrep: mgrep.o libthunder.a
	$(CC) $^ -o $@

## Cleanup

# clean: remove all object files
clean:
	rm -f *.[ao]

quiteclean: clean
	rm -f fact mgrep

# distclean: also remove all non-distributed files
distclean: quiteclean

realclean: distclean

.DELETE_ON_ERROR:

###

$(VM) codebuf.o labels.o vmdebug.o fact.o mgrep.o: \
	vm.h config.h vminternal.h
