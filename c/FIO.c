/* automatically created by mc from /home/gaius/GM2/graft-6.4.0/gcc-6.4.0/gcc/gm2/gm2-libs/FIO.mod.  */

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

#include <stddef.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>
#   include "GStorage.h"
#   include "Gmcrts.h"
#define _FIO_H
#define _FIO_C

#   include "GSYSTEM.h"
#   include "GASCII.h"
#   include "GStrLib.h"
#   include "GStorage.h"
#   include "GNumberIO.h"
#   include "Glibc.h"
#   include "GIndexing.h"
#   include "GM2RTS.h"

typedef unsigned int FIO_File;

FIO_File FIO_StdErr;
FIO_File FIO_StdOut;
FIO_File FIO_StdIn;
#   define SEEK_SET 0
#   define SEEK_END 2
#   define UNIXREADONLY 0
#   define UNIXWRITEONLY 1
#   define CreatePermissions 0666
#   define MaxBufferLength (1024*16)
#   define MaxErrorString (1024*8)
typedef struct NameInfo_r NameInfo;

typedef struct buf_r buf;

typedef buf *Buffer;

typedef struct fds_r fds;

typedef fds *FileDescriptor;

typedef struct _T1_a _T1;

typedef char *PtrToChar;

typedef enum {successful, outofmemory, toomanyfilesopen, failed, connectionfailure, endofline, endoffile} FileStatus;

typedef enum {unused, openedforread, openedforwrite, openedforrandom} FileUsage;

struct NameInfo_r {
                    void *address;
                    unsigned int size;
                  };

struct buf_r {
               unsigned int valid;
               long int bufstart;
               unsigned int position;
               void *address;
               unsigned int filled;
               unsigned int size;
               unsigned int left;
               _T1 *contents;
             };

struct _T1_a { char array[MaxBufferLength+1]; };
struct fds_r {
               int unixfd;
               NameInfo name;
               FileStatus state;
               FileUsage usage;
               unsigned int output;
               Buffer buffer;
               long int abspos;
             };

static Indexing_Index FileInfo;
static FIO_File Error;

/*
   IsNoError - returns a TRUE if no error has occured on file, f.
*/

unsigned int FIO_IsNoError (FIO_File f);

/*
   IsActive - returns TRUE if the file, f, is still active.
*/

unsigned int FIO_IsActive (FIO_File f);
unsigned int FIO_Exists (char *fname_, unsigned int _fname_high);
FIO_File FIO_OpenToRead (char *fname_, unsigned int _fname_high);
FIO_File FIO_OpenToWrite (char *fname_, unsigned int _fname_high);
FIO_File FIO_OpenForRandom (char *fname_, unsigned int _fname_high, unsigned int towrite, unsigned int newfile);

/*
   Close - close a file which has been previously opened using:
           OpenToRead, OpenToWrite, OpenForRandom.
           It is correct to close a file which has an error status.
*/

void FIO_Close (FIO_File f);

/*
   exists - returns TRUE if a file named, fname exists for reading.
*/

unsigned int FIO_exists (void * fname, unsigned int flength);

/*
   openToRead - attempts to open a file, fname, for reading and
                it returns this file.
                The success of this operation can be checked by
                calling IsNoError.
*/

FIO_File FIO_openToRead (void * fname, unsigned int flength);

/*
   openToWrite - attempts to open a file, fname, for write and
                 it returns this file.
                 The success of this operation can be checked by
                 calling IsNoError.
*/

FIO_File FIO_openToWrite (void * fname, unsigned int flength);

/*
   openForRandom - attempts to open a file, fname, for random access
                   read or write and it returns this file.
                   The success of this operation can be checked by
                   calling IsNoError.
                   towrite, determines whether the file should be
                   opened for writing or reading.
*/

FIO_File FIO_openForRandom (void * fname, unsigned int flength, unsigned int towrite, unsigned int newfile);

/*
   FlushBuffer - flush contents of file, f.
*/

void FIO_FlushBuffer (FIO_File f);

/*
   ReadNBytes - reads nBytes of a file into memory area, a, returning
                the number of bytes actually read.
                This function will consume from the buffer and then
                perform direct libc reads. It is ideal for large reads.
*/

unsigned int FIO_ReadNBytes (FIO_File f, unsigned int nBytes, void * a);

/*
   ReadAny - reads HIGH(a) bytes into, a. All input
             is fully buffered, unlike ReadNBytes and thus is more
             suited to small reads.
*/

void FIO_ReadAny (FIO_File f, unsigned char *a, unsigned int _a_high);

/*
   WriteNBytes - writes nBytes of a file into memory area, a, returning
                 the number of bytes actually written.
                 This function will flush the buffer and then
                 write the nBytes using a direct write from libc.
                 It is ideal for large writes.
*/

unsigned int FIO_WriteNBytes (FIO_File f, unsigned int nBytes, void * a);

/*
   WriteAny - writes HIGH(a) bytes onto, file, f. All output
              is fully buffered, unlike WriteNBytes and thus is more
              suited to small writes.
*/

void FIO_WriteAny (FIO_File f, unsigned char *a, unsigned int _a_high);

/*
   WriteChar - writes a single character to file, f.
*/

void FIO_WriteChar (FIO_File f, char ch);

/*
   EOF - tests to see whether a file, f, has reached end of file.
*/

unsigned int FIO_EOF (FIO_File f);

/*
   EOLN - tests to see whether a file, f, is upon a newline.
          It does NOT consume the newline.
*/

unsigned int FIO_EOLN (FIO_File f);

/*
   WasEOLN - tests to see whether a file, f, has just seen a newline.
*/

unsigned int FIO_WasEOLN (FIO_File f);

/*
   ReadChar - returns a character read from file, f.
              Sensible to check with IsNoError or EOF after calling
              this function.
*/

char FIO_ReadChar (FIO_File f);

/*
   UnReadChar - replaces a character, ch, back into file, f.
                This character must have been read by ReadChar
                and it does not allow successive calls.  It may
                only be called if the previous read was successful
                or end of file was seen.
                If the state was previously endoffile then it
                is altered to successful.
                Otherwise it is left alone.
*/

void FIO_UnReadChar (FIO_File f, char ch);

/*
   WriteLine - writes out a linefeed to file, f.
*/

void FIO_WriteLine (FIO_File f);

/*
   WriteString - writes a string to file, f.
*/

void FIO_WriteString (FIO_File f, char *a_, unsigned int _a_high);

/*
   ReadString - reads a string from file, f, into string, a.
                It terminates the string if HIGH is reached or
                if a newline is seen or an error occurs.
*/

void FIO_ReadString (FIO_File f, char *a, unsigned int _a_high);

/*
   WriteCardinal - writes a CARDINAL to file, f.
                   It writes the binary image of the cardinal
                   to file, f.
*/

void FIO_WriteCardinal (FIO_File f, unsigned int c);

/*
   ReadCardinal - reads a CARDINAL from file, f.
                  It reads a binary image of a CARDINAL
                  from a file, f.
*/

unsigned int FIO_ReadCardinal (FIO_File f);

/*
   GetUnixFileDescriptor - returns the UNIX file descriptor of a file.
*/

int FIO_GetUnixFileDescriptor (FIO_File f);

/*
   SetPositionFromBeginning - sets the position from the beginning of the file.
*/

void FIO_SetPositionFromBeginning (FIO_File f, long int pos);

/*
   SetPositionFromEnd - sets the position from the end of the file.
*/

void FIO_SetPositionFromEnd (FIO_File f, long int pos);

/*
   FindPosition - returns the current absolute position in file, f.
*/

long int FIO_FindPosition (FIO_File f);

/*
   GetFileName - assigns, a, with the filename associated with, f.
*/

void FIO_GetFileName (FIO_File f, char *a, unsigned int _a_high);

/*
   getFileName - returns the address of the filename associated with, f.
*/

void * FIO_getFileName (FIO_File f);

/*
   getFileNameLength - returns the number of characters associated with filename, f.
*/

unsigned int FIO_getFileNameLength (FIO_File f);

/*
   FlushOutErr - flushes, StdOut, and, StdErr.
                 It is also called when the application calls M2RTS.Terminate.
                 (which is automatically placed in program modules by the GM2
                 scaffold).
*/

void FIO_FlushOutErr (void);

/*
   Max - returns the maximum of two values.
*/

static unsigned int Max (unsigned int a, unsigned int b);

/*
   Min - returns the minimum of two values.
*/

static unsigned int Min (unsigned int a, unsigned int b);

/*
   GetNextFreeDescriptor - returns the index to the FileInfo array indicating
                           the next free slot.
*/

static FIO_File GetNextFreeDescriptor (void);

/*
   SetState - sets the field, state, of file, f, to, s.
*/

static void SetState (FIO_File f, FileStatus s);

/*
   InitializeFile - initialize a file descriptor
*/

static FIO_File InitializeFile (FIO_File f, void * fname, unsigned int flength, FileStatus fstate, FileUsage use, unsigned int towrite, unsigned int buflength);

/*
   ConnectToUnix - connects a FIO file to a UNIX file descriptor.
*/

static void ConnectToUnix (FIO_File f, unsigned int towrite, unsigned int newfile);

/*
   ReadFromBuffer - attempts to read, nBytes, from file, f.
                    It firstly consumes the buffer and then performs
                    direct unbuffered reads. This should only be used
                    when wishing to read large files.

                    The actual number of bytes read is returned.
                    -1 is returned if EOF is reached.
*/

static int ReadFromBuffer (FIO_File f, void * a, unsigned int nBytes);

/*
   BufferedRead - will read, nBytes, through the buffer.
                  Similar to ReadFromBuffer, but this function will always
                  read into the buffer before copying into memory.

                  Useful when performing small reads.
*/

static int BufferedRead (FIO_File f, unsigned int nBytes, void * a);

/*
   HandleEscape - translates 
 and \t into their respective ascii codes.
*/

static void HandleEscape (char *dest, unsigned int _dest_high, char *src_, unsigned int _src_high, unsigned int *i, unsigned int *j, unsigned int HighSrc, unsigned int HighDest);

/*
   Cast - casts a := b
*/

static void Cast (unsigned char *a, unsigned int _a_high, unsigned char *b_, unsigned int _b_high);

/*
   StringFormat1 - converts string, src, into, dest, together with encapsulated
                   entity, w. It only formats the first %s or %d with n.
*/

static void StringFormat1 (char *dest, unsigned int _dest_high, char *src_, unsigned int _src_high, unsigned char *w_, unsigned int _w_high);

/*
   FormatError - provides a orthoganal counterpart to the procedure below.
*/

static void FormatError (char *a_, unsigned int _a_high);

/*
   FormatError1 - fairly generic error procedure.
*/

static void FormatError1 (char *a_, unsigned int _a_high, unsigned char *w_, unsigned int _w_high);

/*
   FormatError2 - fairly generic error procedure.
*/

static void FormatError2 (char *a_, unsigned int _a_high, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high);

/*
   CheckAccess - checks to see whether a file, f, has been
                 opened for read/write.
*/

static void CheckAccess (FIO_File f, FileUsage use, unsigned int towrite);

/*
   SetEndOfLine - 
*/

static void SetEndOfLine (FIO_File f, char ch);

/*
   BufferedWrite - will write, nBytes, through the buffer.
                   Similar to WriteNBytes, but this function will always
                   write into the buffer before copying into memory.

                   Useful when performing small writes.
*/

static int BufferedWrite (FIO_File f, unsigned int nBytes, void * a);

/*
   PreInitialize - preinitialize the file descriptor.
*/

static void PreInitialize (FIO_File f, char *fname_, unsigned int _fname_high, FileStatus state, FileUsage use, unsigned int towrite, int osfd, unsigned int bufsize);

/*
   Init - initialize the modules, global variables.
*/

static void Init (void);


/*
   Max - returns the maximum of two values.
*/

static unsigned int Max (unsigned int a, unsigned int b)
{
  if (a > b)
    return a;
  else
    return b;
}


/*
   Min - returns the minimum of two values.
*/

static unsigned int Min (unsigned int a, unsigned int b)
{
  if (a < b)
    return a;
  else
    return b;
}


/*
   GetNextFreeDescriptor - returns the index to the FileInfo array indicating
                           the next free slot.
*/

static FIO_File GetNextFreeDescriptor (void)
{
  FIO_File f;
  FIO_File h;
  FileDescriptor fd;

  f = Error+1;
  h = Indexing_HighIndice (FileInfo);
  for (;;)
  {
    if (f <= h)
      {
        fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
        if (fd == NULL)
          return f;
      }
    f += 1;
    if (f > h)
      {
        Indexing_PutIndice (FileInfo, (unsigned int) f, NULL);
        return f;
      }
  }
  ReturnException ("/home/gaius/GM2/graft-6.4.0/gcc-6.4.0/gcc/gm2/gm2-libs/FIO.def", 3, 1);
}


/*
   SetState - sets the field, state, of file, f, to, s.
*/

static void SetState (FIO_File f, FileStatus s)
{
  FileDescriptor fd;

  fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
  fd->state = s;
}


/*
   InitializeFile - initialize a file descriptor
*/

static FIO_File InitializeFile (FIO_File f, void * fname, unsigned int flength, FileStatus fstate, FileUsage use, unsigned int towrite, unsigned int buflength)
{
  PtrToChar p;
  FileDescriptor fd;

  Storage_ALLOCATE ((void **) &fd, sizeof (fds));
  if (fd == NULL)
    {
      SetState (Error, (FileStatus) outofmemory);
      return Error;
    }
  else
    {
      Indexing_PutIndice (FileInfo, (unsigned int) f, (void *) fd);
      fd->name.size = flength+1;
      fd->usage = use;
      fd->output = towrite;
      Storage_ALLOCATE (&fd->name.address, fd->name.size);
      if (fd->name.address == NULL)
        {
          fd->state = outofmemory;
          return f;
        }
      fd->name.address = libc_strncpy (fd->name.address, fname, flength);
      p = fd->name.address;
      p += flength;
      (*p) = ASCII_nul;
      fd->abspos = 0;
      Storage_ALLOCATE ((void **) &fd->buffer, sizeof (buf));
      if (fd->buffer == NULL)
        {
          SetState (Error, (FileStatus) outofmemory);
          return Error;
        }
      else
        {
          fd->buffer->valid = FALSE;
          fd->buffer->bufstart = 0;
          fd->buffer->size = buflength;
          fd->buffer->position = 0;
          fd->buffer->filled = 0;
          if (fd->buffer->size == 0)
            fd->buffer->address = NULL;
          else
            {
              Storage_ALLOCATE (&fd->buffer->address, fd->buffer->size);
              if (fd->buffer->address == NULL)
                {
                  fd->state = outofmemory;
                  return f;
                }
            }
          if (towrite)
            fd->buffer->left = fd->buffer->size;
          else
            fd->buffer->left = 0;
          fd->buffer->contents = fd->buffer->address;
          fd->state = fstate;
        }
    }
  return f;
}


/*
   ConnectToUnix - connects a FIO file to a UNIX file descriptor.
*/

static void ConnectToUnix (FIO_File f, unsigned int towrite, unsigned int newfile)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        {
          if (towrite)
            if (newfile)
              fd->unixfd = libc_creat (fd->name.address, CreatePermissions);
            else
              fd->unixfd = libc_open (fd->name.address, UNIXWRITEONLY, 0);
          else
            fd->unixfd = libc_open (fd->name.address, UNIXREADONLY, 0);
          if (fd->unixfd < 0)
            fd->state = connectionfailure;
        }
    }
}


/*
   ReadFromBuffer - attempts to read, nBytes, from file, f.
                    It firstly consumes the buffer and then performs
                    direct unbuffered reads. This should only be used
                    when wishing to read large files.

                    The actual number of bytes read is returned.
                    -1 is returned if EOF is reached.
*/

static int ReadFromBuffer (FIO_File f, void * a, unsigned int nBytes)
{
  void * t;
  int result;
  unsigned int total;
  unsigned int n;
  unsigned char * p;
  FileDescriptor fd;

  if (f != Error)
    {
      total = 0;
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if ((fd->buffer != NULL) && fd->buffer->valid)
        if (fd->buffer->left > 0)
          {
            /* avoid gcc warning by using compound statement even if not strictly necessary.  */
            if (nBytes == 1)
              {
                p = a;
                (*p) = (*fd->buffer->contents).array[fd->buffer->position];
                fd->buffer->left -= 1;
                fd->buffer->position += 1;
                nBytes = 0;
                return 1;
              }
            else
              {
                n = Min (fd->buffer->left, nBytes);
                t = fd->buffer->address;
                t += fd->buffer->position;
                p = libc_memcpy (a, t, (size_t) n);
                fd->buffer->left -= n;
                fd->buffer->position += n;
                a += n;
                nBytes -= n;
                total += n;
                return total;
              }
          }
      if (nBytes > 0)
        {
          result = libc_read (fd->unixfd, a, (size_t) (int ) (nBytes));
          if (result > 0)
            {
              total += result;
              fd->abspos += result;
              if (fd->buffer != NULL)
                fd->buffer->valid = FALSE;
            }
          else
            {
              if (result == 0)
                fd->state = endoffile;
              else
                fd->state = failed;
              if (fd->buffer != NULL)
                {
                  fd->buffer->valid = FALSE;
                  fd->buffer->left = 0;
                  fd->buffer->position = 0;
                  if (fd->buffer->address != NULL)
                    (*fd->buffer->contents).array[fd->buffer->position] = ASCII_nul;
                }
              return -1;
            }
        }
      return total;
    }
  else
    return -1;
}


/*
   BufferedRead - will read, nBytes, through the buffer.
                  Similar to ReadFromBuffer, but this function will always
                  read into the buffer before copying into memory.

                  Useful when performing small reads.
*/

static int BufferedRead (FIO_File f, unsigned int nBytes, void * a)
{
  void * t;
  int result;
  int total;
  int n;
  unsigned char * p;
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      total = 0;
      if (fd != NULL)
        if (fd->buffer != NULL)
          {
            while (nBytes > 0)
              if ((fd->buffer->left > 0) && fd->buffer->valid)
                if (nBytes == 1)
                  {
                    p = a;
                    (*p) = (*fd->buffer->contents).array[fd->buffer->position];
                    fd->buffer->left -= 1;
                    fd->buffer->position += 1;
                    total += 1;
                    return total;
                  }
                else
                  {
                    n = Min (fd->buffer->left, nBytes);
                    t = fd->buffer->address;
                    t += fd->buffer->position;
                    p = libc_memcpy (a, t, (size_t) n);
                    fd->buffer->left -= n;
                    fd->buffer->position += n;
                    a += n;
                    nBytes -= n;
                    total += n;
                  }
              else
                {
                  n = libc_read (fd->unixfd, fd->buffer->address, (size_t) fd->buffer->size);
                  if (n >= 0)
                    {
                      fd->buffer->valid = TRUE;
                      fd->buffer->position = 0;
                      fd->buffer->left = n;
                      fd->buffer->filled = n;
                      fd->buffer->bufstart = fd->abspos;
                      fd->abspos += n;
                      if (n == 0)
                        {
                          fd->state = endoffile;
                          return -1;
                        }
                    }
                  else
                    {
                      fd->buffer->valid = FALSE;
                      fd->buffer->position = 0;
                      fd->buffer->left = 0;
                      fd->buffer->filled = 0;
                      fd->state = failed;
                      return total;
                    }
                }
            return total;
          }
        else
          return -1;
    }
  else
    return -1;
}


/*
   HandleEscape - translates 
 and \t into their respective ascii codes.
*/

static void HandleEscape (char *dest, unsigned int _dest_high, char *src_, unsigned int _src_high, unsigned int *i, unsigned int *j, unsigned int HighSrc, unsigned int HighDest)
{
  char src[_src_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (src, src_, _src_high+1);

  if (((((*i)+1) < HighSrc) && (src[(*i)] == '\\')) && ((*j) < HighDest))
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if (src[(*i)+1] == 'n')
        {
          dest[(*j)] = ASCII_nl;
          (*j) += 1;
          (*i) += 2;
        }
      else if (src[(*i)+1] == 't')
        {
          dest[(*j)] = ASCII_tab;
          (*j) += 1;
          (*i) += 2;
        }
      else
        {
          (*i) += 1;
          dest[(*j)] = src[(*i)];
          (*j) += 1;
          (*i) += 1;
        }
    }
}


/*
   Cast - casts a := b
*/

static void Cast (unsigned char *a, unsigned int _a_high, unsigned char *b_, unsigned int _b_high)
{
  unsigned int i;
  unsigned char b[_b_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (b, b_, _b_high+1);

  if ((_a_high) == (_b_high))
    for (i=0; i<=_a_high; i++)
      a[i] = b[i];
  else
    FormatError ((char *) "cast failed", 11);
}


/*
   StringFormat1 - converts string, src, into, dest, together with encapsulated
                   entity, w. It only formats the first %s or %d with n.
*/

static void StringFormat1 (char *dest, unsigned int _dest_high, char *src_, unsigned int _src_high, unsigned char *w_, unsigned int _w_high)
{
  typedef struct _T2_a _T2;

  struct _T2_a { char array[MaxErrorString+1]; };
  unsigned int HighSrc;
  unsigned int HighDest;
  unsigned int c;
  unsigned int i;
  unsigned int j;
  _T2 str;
  char * p;
  char src[_src_high+1];
  unsigned char w[_w_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (src, src_, _src_high+1);
  memcpy (w, w_, _w_high+1);

  HighSrc = StrLib_StrLen ((char *) src, _src_high);
  HighDest = _dest_high;
  i = 0;
  j = 0;
  while ((((i < HighSrc) && (src[i] != ASCII_nul)) && (j < HighDest)) && (src[i] != '%'))
    if (src[i] == '\\')
      HandleEscape ((char *) dest, _dest_high, (char *) src, _src_high, &i, &j, HighSrc, HighDest);
    else
      {
        dest[j] = src[i];
        i += 1;
        j += 1;
      }
  if ((((i+1) < HighSrc) && (src[i] == '%')) && (j < HighDest))
    {
      /* avoid gcc warning by using compound statement even if not strictly necessary.  */
      if (src[i+1] == 's')
        {
          Cast ((unsigned char *) &p, (sizeof (p)-1), (unsigned char *) w, _w_high);
          while ((j < HighDest) && ((*p) != ASCII_nul))
            {
              dest[j] = (*p);
              j += 1;
              p += 1;
            }
          if (j < HighDest)
            dest[j] = ASCII_nul;
          j = StrLib_StrLen ((char *) dest, _dest_high);
          i += 2;
        }
      else if (src[i+1] == 'd')
        {
          dest[j] = ASCII_nul;
          Cast ((unsigned char *) &c, (sizeof (c)-1), (unsigned char *) w, _w_high);
          NumberIO_CardToStr (c, 0, (char *) &str.array[0], MaxErrorString);
          StrLib_StrConCat ((char *) dest, _dest_high, (char *) &str.array[0], MaxErrorString, (char *) dest, _dest_high);
          j = StrLib_StrLen ((char *) dest, _dest_high);
          i += 2;
        }
      else
        {
          dest[j] = src[i];
          i += 1;
          j += 1;
        }
    }
  while (((i < HighSrc) && (src[i] != ASCII_nul)) && (j < HighDest))
    if (src[i] == '\\')
      HandleEscape ((char *) dest, _dest_high, (char *) src, _src_high, &i, &j, HighSrc, HighDest);
    else
      {
        dest[j] = src[i];
        i += 1;
        j += 1;
      }
  if (j < HighDest)
    dest[j] = ASCII_nul;
}


/*
   FormatError - provides a orthoganal counterpart to the procedure below.
*/

static void FormatError (char *a_, unsigned int _a_high)
{
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  FIO_WriteString (FIO_StdErr, (char *) a, _a_high);
}


/*
   FormatError1 - fairly generic error procedure.
*/

static void FormatError1 (char *a_, unsigned int _a_high, unsigned char *w_, unsigned int _w_high)
{
  typedef struct _T3_a _T3;

  struct _T3_a { char array[MaxErrorString+1]; };
  _T3 s;
  char a[_a_high+1];
  unsigned char w[_w_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);
  memcpy (w, w_, _w_high+1);

  StringFormat1 ((char *) &s.array[0], MaxErrorString, (char *) a, _a_high, (unsigned char *) w, _w_high);
  FormatError ((char *) &s.array[0], MaxErrorString);
}


/*
   FormatError2 - fairly generic error procedure.
*/

static void FormatError2 (char *a_, unsigned int _a_high, unsigned char *w1_, unsigned int _w1_high, unsigned char *w2_, unsigned int _w2_high)
{
  typedef struct _T4_a _T4;

  struct _T4_a { char array[MaxErrorString+1]; };
  _T4 s;
  char a[_a_high+1];
  unsigned char w1[_w1_high+1];
  unsigned char w2[_w2_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);
  memcpy (w1, w1_, _w1_high+1);
  memcpy (w2, w2_, _w2_high+1);

  StringFormat1 ((char *) &s.array[0], MaxErrorString, (char *) a, _a_high, (unsigned char *) w1, _w1_high);
  FormatError1 ((char *) &s.array[0], MaxErrorString, (unsigned char *) w2, _w2_high);
}


/*
   CheckAccess - checks to see whether a file, f, has been
                 opened for read/write.
*/

static void CheckAccess (FIO_File f, FileUsage use, unsigned int towrite)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd == NULL)
        {
          if (f != FIO_StdErr)
            FormatError ((char *) "this file has probably been closed and not reopened successfully or alternatively never opened\\n", 96);
          M2RTS_HALT (-1);
        }
      else
        if ((use == openedforwrite) && (fd->usage == openedforread))
          {
            FormatError1 ((char *) "this file (%s) has been opened for reading but is now being written\\n", 69, (unsigned char *) &fd->name.address, (sizeof (fd->name.address)-1));
            M2RTS_HALT (-1);
          }
        else if ((use == openedforread) && (fd->usage == openedforwrite))
          {
            FormatError1 ((char *) "this file (%s) has been opened for writing but is now being read\\n", 66, (unsigned char *) &fd->name.address, (sizeof (fd->name.address)-1));
            M2RTS_HALT (-1);
          }
        else if (fd->state == connectionfailure)
          {
            FormatError1 ((char *) "this file (%s) was not successfully opened\\n", 44, (unsigned char *) &fd->name.address, (sizeof (fd->name.address)-1));
            M2RTS_HALT (-1);
          }
        else if (towrite != fd->output)
          if (fd->output)
            {
              FormatError1 ((char *) "this file (%s) was opened for writing but is now being read\\n", 61, (unsigned char *) &fd->name.address, (sizeof (fd->name.address)-1));
              M2RTS_HALT (-1);
            }
          else
            {
              FormatError1 ((char *) "this file (%s) was opened for reading but is now being written\\n", 64, (unsigned char *) &fd->name.address, (sizeof (fd->name.address)-1));
              M2RTS_HALT (-1);
            }
    }
  else
    {
      FormatError ((char *) "this file has not been opened successfully\\n", 44);
      M2RTS_HALT (-1);
    }
}


/*
   SetEndOfLine - 
*/

static void SetEndOfLine (FIO_File f, char ch)
{
  FileDescriptor fd;

  CheckAccess (f, (FileUsage) openedforread, FALSE);
  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (ch == ASCII_nl)
        fd->state = endofline;
      else
        fd->state = successful;
    }
}


/*
   BufferedWrite - will write, nBytes, through the buffer.
                   Similar to WriteNBytes, but this function will always
                   write into the buffer before copying into memory.

                   Useful when performing small writes.
*/

static int BufferedWrite (FIO_File f, unsigned int nBytes, void * a)
{
  void * t;
  int result;
  int total;
  int n;
  unsigned char * p;
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        {
          total = 0;
          if (fd->buffer != NULL)
            {
              while (nBytes > 0)
                if (fd->buffer->left > 0)
                  if (nBytes == 1)
                    {
                      p = a;
                      (*fd->buffer->contents).array[fd->buffer->position] = (*p);
                      fd->buffer->left -= 1;
                      fd->buffer->position += 1;
                      total += 1;
                      return total;
                    }
                  else
                    {
                      n = Min (fd->buffer->left, nBytes);
                      t = fd->buffer->address;
                      t += fd->buffer->position;
                      p = libc_memcpy (a, t, (size_t) (unsigned int ) (n));
                      fd->buffer->left -= n;
                      fd->buffer->position += n;
                      a += n;
                      nBytes -= n;
                      total += n;
                    }
                else
                  {
                    FIO_FlushBuffer (f);
                    if ((fd->state != successful) && (fd->state != endofline))
                      nBytes = 0;
                  }
              return total;
            }
        }
    }
  return -1;
}


/*
   PreInitialize - preinitialize the file descriptor.
*/

static void PreInitialize (FIO_File f, char *fname_, unsigned int _fname_high, FileStatus state, FileUsage use, unsigned int towrite, int osfd, unsigned int bufsize)
{
  FileDescriptor fd;
  FileDescriptor fe;
  char fname[_fname_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (fname, fname_, _fname_high+1);

  if ((InitializeFile (f, &fname, StrLib_StrLen ((char *) fname, _fname_high), state, use, towrite, bufsize)) == f)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (f == Error)
        {
          fe = Indexing_GetIndice (FileInfo, (unsigned int) FIO_StdErr);
          if (fe == NULL)
            M2RTS_HALT (-1);
          else
            fd->unixfd = fe->unixfd;
        }
      else
        fd->unixfd = osfd;
    }
  else
    M2RTS_HALT (-1);
}


/*
   Init - initialize the modules, global variables.
*/

static void Init (void)
{
  FileInfo = Indexing_InitIndex (0);
  Error = 0;
  PreInitialize (Error, (char *) "error", 5, (FileStatus) toomanyfilesopen, (FileUsage) unused, FALSE, -1, 0);
  FIO_StdIn = 1;
  PreInitialize (FIO_StdIn, (char *) "<stdin>", 7, (FileStatus) successful, (FileUsage) openedforread, FALSE, 0, MaxBufferLength);
  FIO_StdOut = 2;
  PreInitialize (FIO_StdOut, (char *) "<stdout>", 8, (FileStatus) successful, (FileUsage) openedforwrite, TRUE, 1, MaxBufferLength);
  FIO_StdErr = 3;
  PreInitialize (FIO_StdErr, (char *) "<stderr>", 8, (FileStatus) successful, (FileUsage) openedforwrite, TRUE, 2, MaxBufferLength);
  if (! (M2RTS_InstallTerminationProcedure ((PROC ) {(PROC_t) FIO_FlushOutErr})))
    M2RTS_HALT (-1);
}


/*
   IsNoError - returns a TRUE if no error has occured on file, f.
*/

unsigned int FIO_IsNoError (FIO_File f)
{
  FileDescriptor fd;

  if (f == Error)
    return FALSE;
  else
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      return (fd != NULL) && (((fd->state == successful) || (fd->state == endoffile)) || (fd->state == endofline));
    }
}


/*
   IsActive - returns TRUE if the file, f, is still active.
*/

unsigned int FIO_IsActive (FIO_File f)
{
  if (f == Error)
    return FALSE;
  else
    return (Indexing_GetIndice (FileInfo, (unsigned int) f)) != NULL;
}

unsigned int FIO_Exists (char *fname_, unsigned int _fname_high)
{
  char fname[_fname_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (fname, fname_, _fname_high+1);

  return FIO_exists (&fname, StrLib_StrLen ((char *) fname, _fname_high));
}

FIO_File FIO_OpenToRead (char *fname_, unsigned int _fname_high)
{
  char fname[_fname_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (fname, fname_, _fname_high+1);

  return FIO_openToRead (&fname, StrLib_StrLen ((char *) fname, _fname_high));
}

FIO_File FIO_OpenToWrite (char *fname_, unsigned int _fname_high)
{
  char fname[_fname_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (fname, fname_, _fname_high+1);

  return FIO_openToWrite (&fname, StrLib_StrLen ((char *) fname, _fname_high));
}

FIO_File FIO_OpenForRandom (char *fname_, unsigned int _fname_high, unsigned int towrite, unsigned int newfile)
{
  char fname[_fname_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (fname, fname_, _fname_high+1);

  return FIO_openForRandom (&fname, StrLib_StrLen ((char *) fname, _fname_high), towrite, newfile);
}


/*
   Close - close a file which has been previously opened using:
           OpenToRead, OpenToWrite, OpenForRandom.
           It is correct to close a file which has an error status.
*/

void FIO_Close (FIO_File f)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        {
          FIO_FlushBuffer (f);
          if (fd->unixfd >= 0)
            if ((libc_close (fd->unixfd)) != 0)
              {
                FormatError1 ((char *) "failed to close file (%s)\\n", 27, (unsigned char *) &fd->name.address, (sizeof (fd->name.address)-1));
                fd->state = failed;
              }
          if (fd->name.address != NULL)
            Storage_DEALLOCATE (&fd->name.address, fd->name.size);
          if (fd->buffer != NULL)
            {
              if (fd->buffer->address != NULL)
                Storage_DEALLOCATE (&fd->buffer->address, fd->buffer->size);
              Storage_DEALLOCATE ((void **) &fd->buffer, sizeof (buf));
              fd->buffer = NULL;
            }
          Storage_DEALLOCATE ((void **) &fd, sizeof (fds));
          Indexing_PutIndice (FileInfo, (unsigned int) f, NULL);
        }
    }
}


/*
   exists - returns TRUE if a file named, fname exists for reading.
*/

unsigned int FIO_exists (void * fname, unsigned int flength)
{
  FIO_File f;

  f = FIO_openToRead (fname, flength);
  if (FIO_IsNoError (f))
    {
      FIO_Close (f);
      return TRUE;
    }
  else
    {
      FIO_Close (f);
      return FALSE;
    }
}


/*
   openToRead - attempts to open a file, fname, for reading and
                it returns this file.
                The success of this operation can be checked by
                calling IsNoError.
*/

FIO_File FIO_openToRead (void * fname, unsigned int flength)
{
  FIO_File f;

  f = GetNextFreeDescriptor ();
  if (f == Error)
    SetState (f, (FileStatus) toomanyfilesopen);
  else
    {
      f = InitializeFile (f, fname, flength, (FileStatus) successful, (FileUsage) openedforread, FALSE, MaxBufferLength);
      ConnectToUnix (f, FALSE, FALSE);
    }
  return f;
}


/*
   openToWrite - attempts to open a file, fname, for write and
                 it returns this file.
                 The success of this operation can be checked by
                 calling IsNoError.
*/

FIO_File FIO_openToWrite (void * fname, unsigned int flength)
{
  FIO_File f;

  f = GetNextFreeDescriptor ();
  if (f == Error)
    SetState (f, (FileStatus) toomanyfilesopen);
  else
    {
      f = InitializeFile (f, fname, flength, (FileStatus) successful, (FileUsage) openedforwrite, TRUE, MaxBufferLength);
      ConnectToUnix (f, TRUE, TRUE);
    }
  return f;
}


/*
   openForRandom - attempts to open a file, fname, for random access
                   read or write and it returns this file.
                   The success of this operation can be checked by
                   calling IsNoError.
                   towrite, determines whether the file should be
                   opened for writing or reading.
*/

FIO_File FIO_openForRandom (void * fname, unsigned int flength, unsigned int towrite, unsigned int newfile)
{
  FIO_File f;

  f = GetNextFreeDescriptor ();
  if (f == Error)
    SetState (f, (FileStatus) toomanyfilesopen);
  else
    {
      f = InitializeFile (f, fname, flength, (FileStatus) successful, (FileUsage) openedforrandom, towrite, MaxBufferLength);
      ConnectToUnix (f, towrite, newfile);
    }
  return f;
}


/*
   FlushBuffer - flush contents of file, f.
*/

void FIO_FlushBuffer (FIO_File f)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        if (fd->output && (fd->buffer != NULL))
          if ((fd->buffer->position == 0) || ((libc_write (fd->unixfd, fd->buffer->address, (size_t) fd->buffer->position)) == ((int ) (fd->buffer->position))))
            {
              fd->abspos += fd->buffer->position;
              fd->buffer->bufstart = fd->abspos;
              fd->buffer->position = 0;
              fd->buffer->filled = 0;
              fd->buffer->left = fd->buffer->size;
            }
          else
            fd->state = failed;
    }
}


/*
   ReadNBytes - reads nBytes of a file into memory area, a, returning
                the number of bytes actually read.
                This function will consume from the buffer and then
                perform direct libc reads. It is ideal for large reads.
*/

unsigned int FIO_ReadNBytes (FIO_File f, unsigned int nBytes, void * a)
{
  int n;
  char * p;

  if (f != Error)
    {
      CheckAccess (f, (FileUsage) openedforread, FALSE);
      n = ReadFromBuffer (f, a, nBytes);
      if (n < 0)
        return 0;
      else
        {
          p = a;
          p += n;
          SetEndOfLine (f, (*p));
          return n;
        }
    }
  else
    return 0;
}


/*
   ReadAny - reads HIGH(a) bytes into, a. All input
             is fully buffered, unlike ReadNBytes and thus is more
             suited to small reads.
*/

void FIO_ReadAny (FIO_File f, unsigned char *a, unsigned int _a_high)
{
  CheckAccess (f, (FileUsage) openedforread, FALSE);
  if ((BufferedRead (f, _a_high, a)) == (_a_high))
    SetEndOfLine (f, (char) a[_a_high]);
}


/*
   WriteNBytes - writes nBytes of a file into memory area, a, returning
                 the number of bytes actually written.
                 This function will flush the buffer and then
                 write the nBytes using a direct write from libc.
                 It is ideal for large writes.
*/

unsigned int FIO_WriteNBytes (FIO_File f, unsigned int nBytes, void * a)
{
  int total;
  FileDescriptor fd;

  CheckAccess (f, (FileUsage) openedforwrite, TRUE);
  FIO_FlushBuffer (f);
  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        {
          total = libc_write (fd->unixfd, a, (size_t) (int ) (nBytes));
          if (total < 0)
            {
              fd->state = failed;
              return 0;
            }
          else
            {
              fd->abspos += (unsigned int ) (total);
              if (fd->buffer != NULL)
                fd->buffer->bufstart = fd->abspos;
              return (unsigned int ) (total);
            }
        }
    }
  return 0;
}


/*
   WriteAny - writes HIGH(a) bytes onto, file, f. All output
              is fully buffered, unlike WriteNBytes and thus is more
              suited to small writes.
*/

void FIO_WriteAny (FIO_File f, unsigned char *a, unsigned int _a_high)
{
  CheckAccess (f, (FileUsage) openedforwrite, TRUE);
  if ((BufferedWrite (f, _a_high, a)) == (_a_high))
    {}  /* empty.  */
}


/*
   WriteChar - writes a single character to file, f.
*/

void FIO_WriteChar (FIO_File f, char ch)
{
  CheckAccess (f, (FileUsage) openedforwrite, TRUE);
  if ((BufferedWrite (f, (unsigned int) sizeof (ch), &ch)) == (sizeof (ch)))
    {}  /* empty.  */
}


/*
   EOF - tests to see whether a file, f, has reached end of file.
*/

unsigned int FIO_EOF (FIO_File f)
{
  FileDescriptor fd;

  CheckAccess (f, (FileUsage) openedforread, FALSE);
  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        return fd->state == endoffile;
    }
  return TRUE;
}


/*
   EOLN - tests to see whether a file, f, is upon a newline.
          It does NOT consume the newline.
*/

unsigned int FIO_EOLN (FIO_File f)
{
  char ch;
  FileDescriptor fd;

  CheckAccess (f, (FileUsage) openedforread, FALSE);
  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        if ((fd->state == successful) || (fd->state == endofline))
          {
            ch = FIO_ReadChar (f);
            if ((fd->state == successful) || (fd->state == endofline))
              FIO_UnReadChar (f, ch);
            return ch == ASCII_nl;
          }
    }
  return FALSE;
}


/*
   WasEOLN - tests to see whether a file, f, has just seen a newline.
*/

unsigned int FIO_WasEOLN (FIO_File f)
{
  FileDescriptor fd;

  CheckAccess (f, (FileUsage) openedforread, FALSE);
  if (f == Error)
    return FALSE;
  else
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      return (fd != NULL) && (fd->state == endofline);
    }
}


/*
   ReadChar - returns a character read from file, f.
              Sensible to check with IsNoError or EOF after calling
              this function.
*/

char FIO_ReadChar (FIO_File f)
{
  char ch;

  CheckAccess (f, (FileUsage) openedforread, FALSE);
  if ((BufferedRead (f, (unsigned int) sizeof (ch), &ch)) == (sizeof (ch)))
    {
      SetEndOfLine (f, ch);
      return ch;
    }
  else
    return ASCII_nul;
}


/*
   UnReadChar - replaces a character, ch, back into file, f.
                This character must have been read by ReadChar
                and it does not allow successive calls.  It may
                only be called if the previous read was successful
                or end of file was seen.
                If the state was previously endoffile then it
                is altered to successful.
                Otherwise it is left alone.
*/

void FIO_UnReadChar (FIO_File f, char ch)
{
  FileDescriptor fd;
  unsigned int n;
  void * a;
  void * b;

  CheckAccess (f, (FileUsage) openedforread, FALSE);
  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (((fd->state == successful) || (fd->state == endoffile)) || (fd->state == endofline))
        {
          /* avoid dangling else.  */
          if ((fd->buffer != NULL) && fd->buffer->valid)
            {
              if (fd->state == endoffile)
                {
                  fd->buffer->position = MaxBufferLength;
                  fd->buffer->left = 0;
                  fd->buffer->filled = 0;
                  fd->state = successful;
                }
              if (fd->buffer->position > 0)
                {
                  fd->buffer->position -= 1;
                  fd->buffer->left += 1;
                  (*fd->buffer->contents).array[fd->buffer->position] = ch;
                }
              else
                if (fd->buffer->filled == fd->buffer->size)
                  FormatError1 ((char *) "performing too many UnReadChar calls on file (%d)\\n", 51, (unsigned char *) &f, (sizeof (f)-1));
                else
                  {
                    n = fd->buffer->filled-fd->buffer->position;
                    b = &(*fd->buffer->contents).array[fd->buffer->position];
                    a = &(*fd->buffer->contents).array[fd->buffer->position+1];
                    a = libc_memcpy (a, b, (size_t) n);
                    fd->buffer->filled += 1;
                    (*fd->buffer->contents).array[fd->buffer->position] = ch;
                  }
            }
        }
      else
        FormatError1 ((char *) "UnReadChar can only be called if the previous read was successful or end of file, error on file (%d)\\n", 102, (unsigned char *) &f, (sizeof (f)-1));
    }
}


/*
   WriteLine - writes out a linefeed to file, f.
*/

void FIO_WriteLine (FIO_File f)
{
  FIO_WriteChar (f, ASCII_nl);
}


/*
   WriteString - writes a string to file, f.
*/

void FIO_WriteString (FIO_File f, char *a_, unsigned int _a_high)
{
  unsigned int l;
  char a[_a_high+1];

  /* make a local copy of each unbounded array.  */
  memcpy (a, a_, _a_high+1);

  l = StrLib_StrLen ((char *) a, _a_high);
  if ((FIO_WriteNBytes (f, l, &a)) != l)
    {}  /* empty.  */
}


/*
   ReadString - reads a string from file, f, into string, a.
                It terminates the string if HIGH is reached or
                if a newline is seen or an error occurs.
*/

void FIO_ReadString (FIO_File f, char *a, unsigned int _a_high)
{
  unsigned int high;
  unsigned int i;
  char ch;

  CheckAccess (f, (FileUsage) openedforread, FALSE);
  high = _a_high;
  i = 0;
  do {
    ch = FIO_ReadChar (f);
    if (i <= high)
      {
        /* avoid gcc warning by using compound statement even if not strictly necessary.  */
        if (((ch == ASCII_nl) || (! (FIO_IsNoError (f)))) || (FIO_EOF (f)))
          {
            a[i] = ASCII_nul;
            i += 1;
          }
        else
          {
            a[i] = ch;
            i += 1;
          }
      }
  } while (! ((((ch == ASCII_nl) || (i > high)) || (! (FIO_IsNoError (f)))) || (FIO_EOF (f))));
}


/*
   WriteCardinal - writes a CARDINAL to file, f.
                   It writes the binary image of the cardinal
                   to file, f.
*/

void FIO_WriteCardinal (FIO_File f, unsigned int c)
{
  FIO_WriteAny (f, (unsigned char *) &c, (sizeof (c)-1));
}


/*
   ReadCardinal - reads a CARDINAL from file, f.
                  It reads a binary image of a CARDINAL
                  from a file, f.
*/

unsigned int FIO_ReadCardinal (FIO_File f)
{
  unsigned int c;

  FIO_ReadAny (f, (unsigned char *) &c, (sizeof (c)-1));
  return c;
}


/*
   GetUnixFileDescriptor - returns the UNIX file descriptor of a file.
*/

int FIO_GetUnixFileDescriptor (FIO_File f)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        return fd->unixfd;
    }
  FormatError1 ((char *) "file %d has not been opened or is out of range\\n", 48, (unsigned char *) &f, (sizeof (f)-1));
  return -1;
}


/*
   SetPositionFromBeginning - sets the position from the beginning of the file.
*/

void FIO_SetPositionFromBeginning (FIO_File f, long int pos)
{
  long int offset;
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        if ((fd->abspos != pos) || TRUE)
          {
            FIO_FlushBuffer (f);
            if (fd->buffer != NULL)
              {
                if (fd->output)
                  fd->buffer->left = fd->buffer->size;
                else
                  fd->buffer->left = 0;
                fd->buffer->position = 0;
                fd->buffer->filled = 0;
              }
            offset = libc_lseek (fd->unixfd, pos, SEEK_SET);
            if ((offset >= 0) && (pos == offset))
              fd->abspos = pos;
            else
              {
                fd->state = failed;
                fd->abspos = 0;
              }
            if (fd->buffer != NULL)
              {
                fd->buffer->valid = FALSE;
                fd->buffer->bufstart = fd->abspos;
              }
          }
    }
}


/*
   SetPositionFromEnd - sets the position from the end of the file.
*/

void FIO_SetPositionFromEnd (FIO_File f, long int pos)
{
  long int offset;
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        {
          FIO_FlushBuffer (f);
          if (fd->buffer != NULL)
            {
              if (fd->output)
                fd->buffer->left = fd->buffer->size;
              else
                fd->buffer->left = 0;
              fd->buffer->position = 0;
              fd->buffer->filled = 0;
            }
          offset = libc_lseek (fd->unixfd, pos, SEEK_END);
          if (offset >= 0)
            fd->abspos = offset;
          else
            {
              fd->state = failed;
              fd->abspos = 0;
              offset = 0;
            }
          if (fd->buffer != NULL)
            {
              fd->buffer->valid = FALSE;
              fd->buffer->bufstart = offset;
            }
        }
    }
}


/*
   FindPosition - returns the current absolute position in file, f.
*/

long int FIO_FindPosition (FIO_File f)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd != NULL)
        if ((fd->buffer == NULL) || ! fd->buffer->valid)
          return fd->abspos;
        else
          return fd->buffer->bufstart+((long int ) (fd->buffer->position));
    }
  return 0;
}


/*
   GetFileName - assigns, a, with the filename associated with, f.
*/

void FIO_GetFileName (FIO_File f, char *a, unsigned int _a_high)
{
  unsigned int i;
  FileDescriptor fd;
  char * p;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd == NULL)
        {
          FormatError ((char *) "this file has probably been closed and not reopened successfully or alternatively never opened\\n", 96);
          M2RTS_HALT (-1);
        }
      else
        if (fd->name.address == NULL)
          StrLib_StrCopy ((char *) "", 0, (char *) a, _a_high);
        else
          {
            p = fd->name.address;
            i = 0;
            while (((*p) != ASCII_nul) && (i <= (_a_high)))
              {
                a[i] = (*p);
                p += 1;
                i += 1;
              }
          }
    }
}


/*
   getFileName - returns the address of the filename associated with, f.
*/

void * FIO_getFileName (FIO_File f)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd == NULL)
        {
          FormatError ((char *) "this file has probably been closed and not reopened successfully or alternatively never opened\\n", 96);
          M2RTS_HALT (-1);
        }
      else
        return fd->name.address;
    }
}


/*
   getFileNameLength - returns the number of characters associated with filename, f.
*/

unsigned int FIO_getFileNameLength (FIO_File f)
{
  FileDescriptor fd;

  if (f != Error)
    {
      fd = Indexing_GetIndice (FileInfo, (unsigned int) f);
      if (fd == NULL)
        {
          FormatError ((char *) "this file has probably been closed and not reopened successfully or alternatively never opened\\n", 96);
          M2RTS_HALT (-1);
        }
      else
        return fd->name.size;
    }
}


/*
   FlushOutErr - flushes, StdOut, and, StdErr.
                 It is also called when the application calls M2RTS.Terminate.
                 (which is automatically placed in program modules by the GM2
                 scaffold).
*/

void FIO_FlushOutErr (void)
{
  if (FIO_IsNoError (FIO_StdOut))
    FIO_FlushBuffer (FIO_StdOut);
  if (FIO_IsNoError (FIO_StdErr))
    FIO_FlushBuffer (FIO_StdErr);
}

void _M2_FIO_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  Init ();
}

void _M2_FIO_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  FIO_FlushOutErr ();
}
