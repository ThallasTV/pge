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
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
MA  02110-1301  USA  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <string.h>
#include <limits.h>
#define _STextIO_H
#define _STextIO_C

#   include "GStdChans.h"
#   include "GTextIO.h"

void STextIO_ReadChar (char *ch);
void STextIO_ReadRestLine (char *s, unsigned int _s_high);
void STextIO_ReadString (char *s, unsigned int _s_high);
void STextIO_ReadToken (char *s, unsigned int _s_high);
void STextIO_SkipLine (void);
void STextIO_WriteChar (char ch);
void STextIO_WriteLn (void);
void STextIO_WriteString (char *s_, unsigned int _s_high);

void STextIO_ReadChar (char *ch)
{
  /* If possible, removes a character from the default input
     stream, and assigns the corresponding value to ch.
     The read result is set to allRight, endOfLine or endOfInput.
  */
  TextIO_ReadChar ((IOChan_ChanId) StdChans_StdInChan (), ch);
}

void STextIO_ReadRestLine (char *s, unsigned int _s_high)
{
  /* Removes any remaining characters from the default input
     stream before the next line mark, copying to s as many
     as can be accommodated as a string value.  The read result
     is set to the value allRight, outOfRange, endOfLine, or
     endOfInput.
  */
  TextIO_ReadRestLine ((IOChan_ChanId) StdChans_StdInChan (), (char *) s, _s_high);
}

void STextIO_ReadString (char *s, unsigned int _s_high)
{
  /* Removes only those characters from the default input stream
     before the next line mark that can be accommodated in s as
     a string value, and copies them to s. The read result
     is set to the value allRight, endOfLine, or endOfInput.
  */
  TextIO_ReadString ((IOChan_ChanId) StdChans_StdInChan (), (char *) s, _s_high);
}

void STextIO_ReadToken (char *s, unsigned int _s_high)
{
  /* Skips leading spaces, and then removes characters from the
     default input stream before the next space or line mark,
     copying to s as many as can be accommodated as a string
     value.  The read result is set to the value allRight,
     outOfRange, endOfLine, or endOfInput.
  */
  TextIO_ReadToken ((IOChan_ChanId) StdChans_StdInChan (), (char *) s, _s_high);
}

void STextIO_SkipLine (void)
{
  /* Removes successive items from the default input stream up
     to and including the next line mark or until the end of
     input is reached. The read result is set to the value
     allRight, or endOfInput.
  */
  TextIO_SkipLine ((IOChan_ChanId) StdChans_StdInChan ());
}

void STextIO_WriteChar (char ch)
{
  /* Writes the value of ch to the default output stream.  */
  TextIO_WriteChar ((IOChan_ChanId) StdChans_StdOutChan (), ch);
}

void STextIO_WriteLn (void)
{
  /* Writes a line mark to the default output stream.  */
  TextIO_WriteLn ((IOChan_ChanId) StdChans_StdOutChan ());
}

void STextIO_WriteString (char *s_, unsigned int _s_high)
{
  char s[_s_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (s, s_, _s_high+1);

  /* Writes the string value of s to the default output stream.  */
  TextIO_WriteString ((IOChan_ChanId) StdChans_StdOutChan (), (char *) s, _s_high);
}

void _M2_STextIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_STextIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
