/* This file is part of GNU Modula-2.

GNU Modula-2 is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GNU Modula-2 is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License along
with gm2; see the file COPYING.  If not, write to the Free Software
Foundation, 51 Franklin Street, Fifth Floor,
Boston, MA 02110-1301, USA.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#   if !defined (TRUE)
#      define TRUE (1==1)
#   endif

#   if !defined (FALSE)
#      define FALSE (1==0)
#   endif

#define _gdbif_H
#define _gdbif_C

#   include "Glibc.h"
#   include "GFIO.h"
#   include "GNumberIO.h"

static unsigned int invoked;
static unsigned int mustWait;

/*
   finishSpin - sets boolean mustWait to FALSE.
*/

void gdbif_finishSpin (void);

/*
   sleepSpin - waits for the boolean variable mustWait to become FALSE.
               It sleeps for a second between each test of the variable.
*/

void gdbif_sleepSpin (void);

/*
   connectSpin - breakpoint placeholder.
*/

void gdbif_connectSpin (void);

/*
   gdbinit - create a ".gdbinit" file in the current directory.
*/

static void gdbinit (void);


/*
   gdbinit - create a ".gdbinit" file in the current directory.
*/

static void gdbinit (void)
{
  typedef struct _T1_a _T1;

  struct _T1_a { char array[7+1]; };
  FIO_File file;
  _T1 pidstr;

  file = FIO_OpenToWrite ((char *) ".gdbinit", 8);
  if (FIO_IsNoError (file))
    {
      FIO_WriteString (file, (char *) "attach ", 7);
      NumberIO_IntToStr (libc_getpid (), 0, (char *) &pidstr.array[0], 7);
      FIO_WriteString (file, (char *) &pidstr.array[0], 7);
      FIO_WriteLine (file);
      FIO_WriteString (file, (char *) "set mustWait=0", 14);
      FIO_WriteLine (file);
      FIO_WriteString (file, (char *) "fin", 3);
      FIO_WriteLine (file);
      FIO_Close (file);
    }
}


/*
   finishSpin - sets boolean mustWait to FALSE.
*/

void gdbif_finishSpin (void)
{
  mustWait = FALSE;
}


/*
   sleepSpin - waits for the boolean variable mustWait to become FALSE.
               It sleeps for a second between each test of the variable.
*/

void gdbif_sleepSpin (void)
{
  if (mustWait)
    {
      gdbinit ();
      libc_printf ((char *) "process %d is waiting for you to:\\n", 35, libc_getpid ());
      libc_printf ((char *) "(gdb) attach %d\\n", 17, libc_getpid ());
      libc_printf ((char *) "(gdb) break connectSpin\\n", 25);
      libc_printf ((char *) "(gdb) print finishSpin()\\n", 26);
      do {
        libc_sleep (1);
        libc_printf ((char *) ".", 1);
      } while (! (! mustWait));
      libc_printf ((char *) "ok continuing\\n", 15);
      gdbif_connectSpin ();
    }
}


/*
   connectSpin - breakpoint placeholder.
*/

void gdbif_connectSpin (void)
{
}

void _M2_gdbif_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  mustWait = TRUE;
}

void _M2_gdbif_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
