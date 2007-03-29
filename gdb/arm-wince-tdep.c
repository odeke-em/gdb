/* Target-dependent code for Windows CE running on ARM processors,
   for GDB.

   Copyright (C) 2007 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

#include "defs.h"
#include "osabi.h"
#include "solib-svr4.h"
#include "target.h"

#include "gdb_string.h"

#include "arm-tdep.h"

static const char arm_wince_le_breakpoint[] = { 0x10, 0x00, 0x00, 0xe6 };

/* Description of the longjmp buffer.  */
#define ARM_WINCE_JB_ELEMENT_SIZE	INT_REGISTER_SIZE
#define ARM_WINCE_JB_PC			21

static void
arm_wince_init_abi (struct gdbarch_info info, struct gdbarch *gdbarch)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (gdbarch);

  tdep->arm_breakpoint = arm_wince_le_breakpoint;
  tdep->arm_breakpoint_size = sizeof (arm_wince_le_breakpoint);
  tdep->struct_return = pcc_struct_return;

  tdep->fp_model = ARM_FLOAT_SOFT_VFP;

  tdep->jb_pc = ARM_WINCE_JB_PC;
  tdep->jb_elt_size = ARM_WINCE_JB_ELEMENT_SIZE;

  /* On ARM WinCE char defaults to signed.  */
  set_gdbarch_char_signed (gdbarch, 1);

  set_solib_svr4_fetch_link_map_offsets
    (gdbarch, svr4_ilp32_fetch_link_map_offsets);

  /* Shared library handling.  */
  set_gdbarch_skip_trampoline_code (gdbarch, find_solib_trampoline_target);
}

static enum gdb_osabi
arm_wince_osabi_sniffer (bfd *abfd)
{
  const char *target_name = bfd_get_target (abfd);

  if (strcmp (target_name, "pei-arm-wince-little") == 0)
    return GDB_OSABI_WINCE;

  return GDB_OSABI_UNKNOWN;
}

/* Provide a prototype to silence -Wmissing-prototypes.  */
void _initialize_arm_wince_tdep (void);

void
_initialize_arm_wince_tdep (void)
{
  gdbarch_register_osabi_sniffer (bfd_arch_arm, bfd_target_coff_flavour,
                                  arm_wince_osabi_sniffer);

  gdbarch_register_osabi (bfd_arch_arm, 0, GDB_OSABI_WINCE,
                          arm_wince_init_abi);
}
