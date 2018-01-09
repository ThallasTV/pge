/* automatically created by mc from /home/gaius/GM2/graft-6.4.0/gcc-6.4.0/gcc/gm2/gm2-libs/NumberIO.mod.  */

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

#include <string.h>
#include <limits.h>
#include <stdlib.h>
#define _NumberIO_H
#define _NumberIO_C

#   include "GASCII.h"
#   include "GStrIO.h"
#   include "GStrLib.h"
#   include "GM2RTS.h"

#   define MaxLineLength 79
#   define MaxDigits 20
#   define MaxHexDigits 20
#   define MaxOctDigits 40
#   define MaxBits 64
void NumberIO_ReadCard (unsigned int *x);
void NumberIO_WriteCard (unsigned int x, unsigned int n);
void NumberIO_ReadHex (unsigned int *x);
void NumberIO_WriteHex (unsigned int x, unsigned int n);
void NumberIO_ReadInt (int *x);
void NumberIO_WriteInt (int x, unsigned int n);
void NumberIO_CardToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
void NumberIO_StrToCard (char *a_, unsigned int _a_high, unsigned int *x);
void NumberIO_HexToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
void NumberIO_StrToHex (char *a_, unsigned int _a_high, unsigned int *x);
void NumberIO_IntToStr (int x, unsigned int n, char *a, unsigned int _a_high);
void NumberIO_StrToInt (char *a_, unsigned int _a_high, int *x);
void NumberIO_ReadOct (unsigned int *x);
void NumberIO_WriteOct (unsigned int x, unsigned int n);
void NumberIO_OctToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
void NumberIO_StrToOct (char *a_, unsigned int _a_high, unsigned int *x);
void NumberIO_ReadBin (unsigned int *x);
void NumberIO_WriteBin (unsigned int x, unsigned int n);
void NumberIO_BinToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high);
void NumberIO_StrToBin (char *a_, unsigned int _a_high, unsigned int *x);
void NumberIO_StrToBinInt (char *a_, unsigned int _a_high, int *x);
void NumberIO_StrToHexInt (char *a_, unsigned int _a_high, int *x);
void NumberIO_StrToOctInt (char *a_, unsigned int _a_high, int *x);

void NumberIO_ReadCard (unsigned int *x)
{
  typedef struct _T1_a _T1;

  struct _T1_a { char array[MaxLineLength+1]; };
  _T1 a;

  StrIO_ReadString ((char *) &a.array[0], MaxLineLength);
  NumberIO_StrToCard ((char *) &a.array[0], MaxLineLength, x);
}

void NumberIO_WriteCard (unsigned int x, unsigned int n)
{
  typedef struct _T2_a _T2;

  struct _T2_a { char array[MaxLineLength+1]; };
  _T2 a;

  NumberIO_CardToStr (x, n, (char *) &a.array[0], MaxLineLength);
  StrIO_WriteString ((char *) &a.array[0], MaxLineLength);
}

void NumberIO_ReadHex (unsigned int *x)
{
  typedef struct _T3_a _T3;

  struct _T3_a { char array[MaxLineLength+1]; };
  _T3 a;

  StrIO_ReadString ((char *) &a.array[0], MaxLineLength);
  NumberIO_StrToHex ((char *) &a.array[0], MaxLineLength, x);
}

void NumberIO_WriteHex (unsigned int x, unsigned int n)
{
  typedef struct _T4_a _T4;

  struct _T4_a { char array[MaxLineLength+1]; };
  _T4 a;

  NumberIO_HexToStr (x, n, (char *) &a.array[0], MaxLineLength);
  StrIO_WriteString ((char *) &a.array[0], MaxLineLength);
}

void NumberIO_ReadInt (int *x)
{
  typedef struct _T5_a _T5;

  struct _T5_a { char array[MaxLineLength+1]; };
  _T5 a;

  StrIO_ReadString ((char *) &a.array[0], MaxLineLength);
  NumberIO_StrToInt ((char *) &a.array[0], MaxLineLength, x);
}

void NumberIO_WriteInt (int x, unsigned int n)
{
  typedef struct _T6_a _T6;

  struct _T6_a { char array[MaxLineLength+1]; };
  _T6 a;

  NumberIO_IntToStr (x, n, (char *) &a.array[0], MaxLineLength);
  StrIO_WriteString ((char *) &a.array[0], MaxLineLength);
}

void NumberIO_CardToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high)
{
  typedef struct _T7_a _T7;

  struct _T7_a { unsigned int array[MaxDigits-1+1]; };
  unsigned int i;
  unsigned int j;
  unsigned int Higha;
  _T7 buf;

  i = 0;
  do {
    i += 1;
    if (i > MaxDigits)
      {
        StrIO_WriteString ((char *) "NumberIO - increase MaxDigits", 29);
        StrIO_WriteLn ();
        M2RTS_HALT (-1);
      }
    buf.array[i-1] = x % 10;
    x = x / 10;
  } while (! (x == 0));
  j = 0;
  Higha = _a_high;
  while ((n > i) && (j <= Higha))
    {
      a[j] = ' ';
      j += 1;
      n -= 1;
    }
  while ((i > 0) && (j <= Higha))
    {
      a[j] = (char) (buf.array[i-1]+((unsigned int) ('0')));
      j += 1;
      i -= 1;
    }
  if (j <= Higha)
    a[j] = ASCII_nul;
}

void NumberIO_StrToCard (char *a_, unsigned int _a_high, unsigned int *x)
{
  unsigned int i;
  unsigned int ok;
  unsigned int higha;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  StrLib_StrRemoveWhitePrefix ((char *) a, _a_high, (char *) a, _a_high);
  higha = StrLib_StrLen ((char *) a, _a_high);
  i = 0;
  ok = TRUE;
  while (ok)
    if (i < higha)
      if ((a[i] < '0') || (a[i] > '9'))
        i += 1;
      else
        ok = FALSE;
    else
      ok = FALSE;
  (*x) = 0;
  if (i < higha)
    {
      ok = TRUE;
      do {
        (*x) = (10*(*x))+(((unsigned int) (a[i]))-((unsigned int) ('0')));
        if (i < higha)
          {
            i += 1;
            if ((a[i] < '0') || (a[i] > '9'))
              ok = FALSE;
          }
        else
          ok = FALSE;
      } while (! (! ok));
    }
}

void NumberIO_HexToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high)
{
  typedef struct _T8_a _T8;

  struct _T8_a { unsigned int array[MaxHexDigits-1+1]; };
  unsigned int i;
  unsigned int j;
  unsigned int Higha;
  _T8 buf;

  i = 0;
  do {
    i += 1;
    if (i > MaxHexDigits)
      {
        StrIO_WriteString ((char *) "NumberIO - increase MaxDigits", 29);
        StrIO_WriteLn ();
        M2RTS_HALT (-1);
      }
    buf.array[i-1] = x % 0x010;
    x = x / 0x010;
  } while (! (x == 0));
  j = 0;
  Higha = _a_high;
  while ((n > i) && (j <= Higha))
    {
      a[j] = '0';
      j += 1;
      n -= 1;
    }
  while ((i != 0) && (j <= Higha))
    {
      if (buf.array[i-1] < 10)
        a[j] = (char) (buf.array[i-1]+((unsigned int) ('0')));
      else
        a[j] = (char) ((buf.array[i-1]+((unsigned int) ('A')))-10);
      j += 1;
      i -= 1;
    }
  if (j <= Higha)
    a[j] = ASCII_nul;
}

void NumberIO_StrToHex (char *a_, unsigned int _a_high, unsigned int *x)
{
  int i;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  NumberIO_StrToHexInt ((char *) a, _a_high, &i);
  (*x) = (unsigned int ) (i);
}

void NumberIO_IntToStr (int x, unsigned int n, char *a, unsigned int _a_high)
{
  typedef struct _T9_a _T9;

  struct _T9_a { unsigned int array[MaxDigits-1+1]; };
  unsigned int i;
  unsigned int j;
  unsigned int c;
  unsigned int Higha;
  _T9 buf;
  unsigned int Negative;

  if (x < 0)
    {
      Negative = TRUE;
      c = ((unsigned int ) (abs (x+1)))+1;
      if (n > 0)
        n -= 1;
    }
  else
    {
      c = x;
      Negative = FALSE;
    }
  i = 0;
  do {
    i += 1;
    if (i > MaxDigits)
      {
        StrIO_WriteString ((char *) "NumberIO - increase MaxDigits", 29);
        StrIO_WriteLn ();
        M2RTS_HALT (-1);
      }
    buf.array[i-1] = c % 10;
    c = c / 10;
  } while (! (c == 0));
  j = 0;
  Higha = _a_high;
  while ((n > i) && (j <= Higha))
    {
      a[j] = ' ';
      j += 1;
      n -= 1;
    }
  if (Negative)
    {
      a[j] = '-';
      j += 1;
    }
  while ((i != 0) && (j <= Higha))
    {
      a[j] = (char) (buf.array[i-1]+((unsigned int) ('0')));
      j += 1;
      i -= 1;
    }
  if (j <= Higha)
    a[j] = ASCII_nul;
}

void NumberIO_StrToInt (char *a_, unsigned int _a_high, int *x)
{
  unsigned int i;
  unsigned int ok;
  unsigned int Negative;
  unsigned int higha;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  StrLib_StrRemoveWhitePrefix ((char *) a, _a_high, (char *) a, _a_high);
  higha = StrLib_StrLen ((char *) a, _a_high);
  i = 0;
  Negative = FALSE;
  ok = TRUE;
  while (ok)
    if (i < higha)
      if (a[i] == '-')
        {
          i += 1;
          Negative = ! Negative;
        }
      else if ((a[i] < '0') || (a[i] > '9'))
        i += 1;
      else
        ok = FALSE;
    else
      ok = FALSE;
  (*x) = 0;
  if (i < higha)
    {
      ok = TRUE;
      do {
        if (Negative)
          (*x) = (10*(*x))-((int ) (((unsigned int) (a[i]))-((unsigned int) ('0'))));
        else
          (*x) = (10*(*x))+((int ) (((unsigned int) (a[i]))-((unsigned int) ('0'))));
        if (i < higha)
          {
            i += 1;
            if ((a[i] < '0') || (a[i] > '9'))
              ok = FALSE;
          }
        else
          ok = FALSE;
      } while (! (! ok));
    }
}

void NumberIO_ReadOct (unsigned int *x)
{
  typedef struct _T10_a _T10;

  struct _T10_a { char array[MaxLineLength+1]; };
  _T10 a;

  StrIO_ReadString ((char *) &a.array[0], MaxLineLength);
  NumberIO_StrToOct ((char *) &a.array[0], MaxLineLength, x);
}

void NumberIO_WriteOct (unsigned int x, unsigned int n)
{
  typedef struct _T11_a _T11;

  struct _T11_a { char array[MaxLineLength+1]; };
  _T11 a;

  NumberIO_OctToStr (x, n, (char *) &a.array[0], MaxLineLength);
  StrIO_WriteString ((char *) &a.array[0], MaxLineLength);
}

void NumberIO_OctToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high)
{
  typedef struct _T12_a _T12;

  struct _T12_a { unsigned int array[MaxOctDigits-1+1]; };
  unsigned int i;
  unsigned int j;
  unsigned int Higha;
  _T12 buf;

  i = 0;
  do {
    i += 1;
    if (i > MaxOctDigits)
      {
        StrIO_WriteString ((char *) "NumberIO - increase MaxDigits", 29);
        StrIO_WriteLn ();
        M2RTS_HALT (-1);
      }
    buf.array[i-1] = x % 8;
    x = x / 8;
  } while (! (x == 0));
  j = 0;
  Higha = _a_high;
  while ((n > i) && (j <= Higha))
    {
      a[j] = ' ';
      j += 1;
      n -= 1;
    }
  while ((i > 0) && (j <= Higha))
    {
      a[j] = (char) (buf.array[i-1]+((unsigned int) ('0')));
      j += 1;
      i -= 1;
    }
  if (j <= Higha)
    a[j] = ASCII_nul;
}

void NumberIO_StrToOct (char *a_, unsigned int _a_high, unsigned int *x)
{
  int i;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  NumberIO_StrToOctInt ((char *) a, _a_high, &i);
  (*x) = (unsigned int ) (i);
}

void NumberIO_ReadBin (unsigned int *x)
{
  typedef struct _T13_a _T13;

  struct _T13_a { char array[MaxLineLength+1]; };
  _T13 a;

  StrIO_ReadString ((char *) &a.array[0], MaxLineLength);
  NumberIO_StrToBin ((char *) &a.array[0], MaxLineLength, x);
}

void NumberIO_WriteBin (unsigned int x, unsigned int n)
{
  typedef struct _T14_a _T14;

  struct _T14_a { char array[MaxLineLength+1]; };
  _T14 a;

  NumberIO_BinToStr (x, n, (char *) &a.array[0], MaxLineLength);
  StrIO_WriteString ((char *) &a.array[0], MaxLineLength);
}

void NumberIO_BinToStr (unsigned int x, unsigned int n, char *a, unsigned int _a_high)
{
  typedef struct _T15_a _T15;

  struct _T15_a { unsigned int array[MaxBits-1+1]; };
  unsigned int i;
  unsigned int j;
  unsigned int Higha;
  _T15 buf;

  i = 0;
  do {
    i += 1;
    if (i > MaxBits)
      {
        StrIO_WriteString ((char *) "NumberIO - increase MaxBits", 27);
        StrIO_WriteLn ();
        M2RTS_HALT (-1);
      }
    buf.array[i-1] = x % 2;
    x = x / 2;
  } while (! (x == 0));
  j = 0;
  Higha = _a_high;
  while ((n > i) && (j <= Higha))
    {
      a[j] = ' ';
      j += 1;
      n -= 1;
    }
  while ((i > 0) && (j <= Higha))
    {
      a[j] = (char) (buf.array[i-1]+((unsigned int) ('0')));
      j += 1;
      i -= 1;
    }
  if (j <= Higha)
    a[j] = ASCII_nul;
}

void NumberIO_StrToBin (char *a_, unsigned int _a_high, unsigned int *x)
{
  int i;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  NumberIO_StrToBinInt ((char *) a, _a_high, &i);
  (*x) = (unsigned int ) (i);
}

void NumberIO_StrToBinInt (char *a_, unsigned int _a_high, int *x)
{
  unsigned int i;
  unsigned int ok;
  unsigned int higha;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  StrLib_StrRemoveWhitePrefix ((char *) a, _a_high, (char *) a, _a_high);
  higha = StrLib_StrLen ((char *) a, _a_high);
  i = 0;
  ok = TRUE;
  while (ok)
    if (i < higha)
      if ((a[i] < '0') || (a[i] > '1'))
        i += 1;
      else
        ok = FALSE;
    else
      ok = FALSE;
  (*x) = 0;
  if (i < higha)
    {
      ok = TRUE;
      do {
        (*x) = (2*(*x))+((int ) (((unsigned int) (a[i]))-((unsigned int) ('0'))));
        if (i < higha)
          {
            i += 1;
            if ((a[i] < '0') || (a[i] > '1'))
              ok = FALSE;
          }
        else
          ok = FALSE;
      } while (! (! ok));
    }
}

void NumberIO_StrToHexInt (char *a_, unsigned int _a_high, int *x)
{
  unsigned int i;
  unsigned int ok;
  unsigned int higha;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  StrLib_StrRemoveWhitePrefix ((char *) a, _a_high, (char *) a, _a_high);
  higha = StrLib_StrLen ((char *) a, _a_high);
  i = 0;
  ok = TRUE;
  while (ok)
    if (i < higha)
      if (((a[i] >= '0') && (a[i] <= '9')) || ((a[i] >= 'A') && (a[i] <= 'F')))
        ok = FALSE;
      else
        i += 1;
    else
      ok = FALSE;
  (*x) = 0;
  if (i < higha)
    {
      ok = TRUE;
      do {
        if ((a[i] >= '0') && (a[i] <= '9'))
          (*x) = (0x010*(*x))+((int ) (((unsigned int) (a[i]))-((unsigned int) ('0'))));
        else if ((a[i] >= 'A') && (a[i] <= 'F'))
          (*x) = (0x010*(*x))+((int ) ((((unsigned int) (a[i]))-((unsigned int) ('A')))+10));
        if (i < higha)
          {
            i += 1;
            if (((a[i] < '0') || (a[i] > '9')) && ((a[i] < 'A') || (a[i] > 'F')))
              ok = FALSE;
          }
        else
          ok = FALSE;
      } while (! (! ok));
    }
}

void NumberIO_StrToOctInt (char *a_, unsigned int _a_high, int *x)
{
  unsigned int i;
  unsigned int ok;
  unsigned int higha;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  StrLib_StrRemoveWhitePrefix ((char *) a, _a_high, (char *) a, _a_high);
  higha = StrLib_StrLen ((char *) a, _a_high);
  i = 0;
  ok = TRUE;
  while (ok)
    if (i < higha)
      if ((a[i] < '0') || (a[i] > '7'))
        i += 1;
      else
        ok = FALSE;
    else
      ok = FALSE;
  (*x) = 0;
  if (i < higha)
    {
      ok = TRUE;
      do {
        (*x) = (8*(*x))+((int ) (((unsigned int) (a[i]))-((unsigned int) ('0'))));
        if (i < higha)
          {
            i += 1;
            if ((a[i] < '0') || (a[i] > '7'))
              ok = FALSE;
          }
        else
          ok = FALSE;
      } while (! (! ok));
    }
}

void _M2_NumberIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_NumberIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
