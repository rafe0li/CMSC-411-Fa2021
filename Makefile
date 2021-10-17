# Detect the target development environment.
#
# Copyright(c) 2021 Jason Tang <jtang@umbc.edu>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2 as
#  published by the Free Software Foundation.
OS_TYPE := $(shell uname -s)
MACH_TYPE := $(shell uname -m)
TARGET_ENV := $(OS_TYPE)-$(MACH_TYPE)

ifeq ($(TARGET_ENV),Darwin-arm64)
# macOS-aarch64
CC ?= clang
AARCH64_CC ?= clang
AARCH64_AS ?= clang -c -x assembler
AARCH64_LD ?= clang
else ifeq ($(TARGET_ENV),Linux-x86_64)
# Linux-x86_64
CC ?= gcc
AARCH64_CC ?= aarch64-linux-gnu-gcc
AARCH64_AS ?= aarch64-linux-gnu-as
AARCH64_LD ?= aarch64-linux-gnu-gcc -static
else ifeq ($(TARGET_ENV),Linux-aarch64)
# Linux-aarch64
CC ?= gcc
AARCH64_CC ?= gcc
AARCH64_AS ?= as
AARCH64_LD ?= gcc
else
$(error Unknown development environment. Please re-do Part1 of HW1.)
endif

CFLAGS ?= --std=c99 -Wall -O0 -g
ASFLAGS ?= -g
LDFLAGS ?=

bin_PROGRAMS = hw3
OBJS = hw3.o hw3_asm.o

$(bin_PROGRAMS): $(OBJS)
	$(AARCH64_LD) $(LDFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(AARCH64_CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(AARCH64_CC) -E -c $< | sed -e 's/__NL__/\n/' | $(AARCH64_AS) $(ASFLAGS) -o $@ -

indent:
	indent -npro -kr -i8 -ts8 -sob -l80 -ss -ncs -cp1 -il0 hw3.c

clean:
	-rm -f $(bin_PROGRAMS) $(OBJS) *.tmp.S

.PHONY: indent clean