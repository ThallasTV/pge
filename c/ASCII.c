/* This file is part of GNU Modula-2.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#define _ASCII_H
#define _ASCII_C


#   define ASCII_nul (char) 000
#   define ASCII_soh (char) 001
#   define ASCII_stx (char) 002
#   define ASCII_etx (char) 003
#   define ASCII_eot (char) 004
#   define ASCII_enq (char) 005
#   define ASCII_ack (char) 006
#   define ASCII_bel (char) 007
#   define ASCII_bs (char) 010
#   define ASCII_ht (char) 011
#   define ASCII_nl (char) 012
#   define ASCII_vt (char) 013
#   define ASCII_np (char) 014
#   define ASCII_cr (char) 015
#   define ASCII_so (char) 016
#   define ASCII_si (char) 017
#   define ASCII_dle (char) 020
#   define ASCII_dc1 (char) 021
#   define ASCII_dc2 (char) 022
#   define ASCII_dc3 (char) 023
#   define ASCII_dc4 (char) 024
#   define ASCII_nak (char) 025
#   define ASCII_syn (char) 026
#   define ASCII_etb (char) 027
#   define ASCII_can (char) 030
#   define ASCII_em (char) 031
#   define ASCII_sub (char) 032
#   define ASCII_esc (char) 033
#   define ASCII_fs (char) 034
#   define ASCII_gs (char) 035
#   define ASCII_rs (char) 036
#   define ASCII_us (char) 037
#   define ASCII_sp (char) 040
#   define ASCII_lf ASCII_nl
#   define ASCII_ff ASCII_np
#   define ASCII_eof ASCII_eot
#   define ASCII_tab ASCII_ht
#   define ASCII_del (char) 0177
#   define ASCII_EOL ASCII_nl

void _M2_ASCII_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_ASCII_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
