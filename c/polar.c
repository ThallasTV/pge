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

#define _polar_H
#define _polar_C

#   include "Gcoord.h"
#   include "Groots.h"
#   include "Glibm.h"
#   include "Glibc.h"
#   include "GMathLib0.h"
#   include "GM2RTS.h"

typedef struct polar_Polar_r polar_Polar;

struct polar_Polar_r {
                       double r;
                       double w;
                     };


/*
   initPolar - initialises a polar coordinate, r, is the radius (magnitude)
               and, w, is the angle.
*/

polar_Polar polar_initPolar (double r, double w);

/*
   polarToCoord - convert a polar coordinate into a cartesian coordinate.
*/

coord_Coord polar_polarToCoord (polar_Polar p);

/*
   coordToPolar - return a polar coordinate pair given a cartesian coordinate.
*/

polar_Polar polar_coordToPolar (coord_Coord c);

/*
   rotatePolar - return a polar coordinate after rotating it by, w, radians.
*/

polar_Polar polar_rotatePolar (polar_Polar p, double w);

/*
   Assert - 
*/

static void Assert (unsigned int b);

/*
   sqr - 
*/

static double sqr (double a);

/*
   assertEqual - 
*/

static void assertEqual (coord_Coord c1, coord_Coord c2);


/*
   Assert - 
*/

static void Assert (unsigned int b)
{
  if (! b)
    {
      libc_printf ((char *) "error assert failed\\n", 21);
      M2RTS_HALT (-1);
    }
}


/*
   sqr - 
*/

static double sqr (double a)
{
  return a*a;
}


/*
   assertEqual - 
*/

static void assertEqual (coord_Coord c1, coord_Coord c2)
{
  Assert ((roots_nearZero (c1.x-c2.x)) && (roots_nearZero (c1.y-c2.y)));
}


/*
   initPolar - initialises a polar coordinate, r, is the radius (magnitude)
               and, w, is the angle.
*/

polar_Polar polar_initPolar (double r, double w)
{
  polar_Polar p;

  p.r = r;
  p.w = w;
  return p;
}


/*
   polarToCoord - convert a polar coordinate into a cartesian coordinate.
*/

coord_Coord polar_polarToCoord (polar_Polar p)
{
  return coord_initCoord (p.r*(libm_cos (p.w)), p.r*(libm_sin (p.w)));
}


/*
   coordToPolar - return a polar coordinate pair given a cartesian coordinate.
*/

polar_Polar polar_coordToPolar (coord_Coord c)
{
  double r;
  polar_Polar p;

  r = libm_sqrt ((sqr (c.x))+(sqr (c.y)));
  if (roots_nearZero (r))
    p = polar_initPolar (0.0, 0.0);
  else if ((c.x >= 0.0) && (c.y >= 0.0))
    /* quadrant 1  */
    p = polar_initPolar (r, libm_asin (c.y/r));
  else if ((c.x < 0.0) && (c.y >= 0.0))
    /* quadrant 2  */
    p = polar_initPolar (r, MathLib0_pi-(libm_asin (c.y/r)));
  else if ((c.x < 0.0) && (c.y < 0.0))
    /* quadrant 3  */
    p = polar_initPolar (r, MathLib0_pi+(libm_asin (-(c.y/r))));
  else if ((c.x >= 0.0) && (c.y < 0.0))
    /* quadrant 4  */
    p = polar_initPolar (r, (2.0*MathLib0_pi)-(libm_asin (-(c.y/r))));
  assertEqual (polar_polarToCoord (p), c);
  return p;
}


/*
   rotatePolar - return a polar coordinate after rotating it by, w, radians.
*/

polar_Polar polar_rotatePolar (polar_Polar p, double w)
{
  p.w = p.w+w;
  return p;
}

void _M2_polar_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_polar_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
