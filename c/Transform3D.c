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
Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */

#   if !defined (PROC_D)
#      define PROC_D
       typedef void (*PROC_t) (void);
       typedef struct { PROC_t proc; } PROC;
#   endif

#include <stddef.h>
#define _Transform3D_H
#define _Transform3D_C

#   include "GFractions.h"
#   include "GPolyMatrix3D.h"
#   include "GM2RTS.h"

typedef struct Points_Point_r Points_Point;

struct Points_Point_r {
                        Fractions_Fract x;
                        Fractions_Fract y;
                      };


/*
   reflect - returns a Matrix representing the reflect
             transformation in line: y = mx + c.
*/

PolyMatrix3D_Matrix Transform3D_reflect (Fractions_Fract m, Fractions_Fract x, Fractions_Fract c);

/*
   rotate - returns a Matrix representing the rotate
            transformation about 0, 0 with r radians.
*/

PolyMatrix3D_Matrix Transform3D_rotate (Fractions_Fract r);

/*
   scale - returns a Matrix representing the scale
           transformation by vector, p.
*/

PolyMatrix3D_Matrix Transform3D_scale (Points_Point p);

/*
   translate - returns a Matrix representing the translate
               transformation by vector, p.
*/

PolyMatrix3D_Matrix Transform3D_translate (Points_Point p);


/*
   reflect - returns a Matrix representing the reflect
             transformation in line: y = mx + c.
*/

PolyMatrix3D_Matrix Transform3D_reflect (Fractions_Fract m, Fractions_Fract x, Fractions_Fract c)
{
  M2RTS_HALT (-1);
  return NULL;
}


/*
   rotate - returns a Matrix representing the rotate
            transformation about 0, 0 with r radians.
*/

PolyMatrix3D_Matrix Transform3D_rotate (Fractions_Fract r)
{
  PolyMatrix3D_Matrix m;
  PolyMatrix3D_MatrixValue v;

  v.array[1-1].array[1-1] = Fractions_cos (r);
  v.array[1-1].array[2-1] = Fractions_negate (Fractions_sin (r));
  v.array[1-1].array[3-1] = Fractions_zero ();
  v.array[2-1].array[1-1] = Fractions_sin (r);
  v.array[2-1].array[2-1] = Fractions_cos (r);
  v.array[2-1].array[3-1] = Fractions_zero ();
  v.array[3-1].array[1-1] = Fractions_zero ();
  v.array[3-1].array[2-1] = Fractions_zero ();
  v.array[3-1].array[3-1] = Fractions_one ();
  return PolyMatrix3D_set (PolyMatrix3D_init (), v);
}


/*
   scale - returns a Matrix representing the scale
           transformation by vector, p.
*/

PolyMatrix3D_Matrix Transform3D_scale (Points_Point p)
{
  PolyMatrix3D_Matrix m;
  PolyMatrix3D_MatrixValue v;

  v.array[1-1].array[1-1] = Fractions_dup (p.x);
  v.array[1-1].array[2-1] = Fractions_zero ();
  v.array[1-1].array[3-1] = Fractions_zero ();
  v.array[2-1].array[1-1] = Fractions_zero ();
  v.array[2-1].array[2-1] = Fractions_dup (p.y);
  v.array[2-1].array[3-1] = Fractions_zero ();
  v.array[3-1].array[1-1] = Fractions_zero ();
  v.array[3-1].array[2-1] = Fractions_zero ();
  v.array[3-1].array[3-1] = Fractions_one ();
  return PolyMatrix3D_set (PolyMatrix3D_init (), v);
}


/*
   translate - returns a Matrix representing the translate
               transformation by vector, p.
*/

PolyMatrix3D_Matrix Transform3D_translate (Points_Point p)
{
  PolyMatrix3D_Matrix m;
  PolyMatrix3D_MatrixValue v;

  v.array[1-1].array[1-1] = Fractions_one ();
  v.array[1-1].array[2-1] = Fractions_zero ();
  v.array[1-1].array[3-1] = Fractions_zero ();
  v.array[2-1].array[1-1] = Fractions_zero ();
  v.array[2-1].array[2-1] = Fractions_one ();
  v.array[2-1].array[3-1] = Fractions_zero ();
  v.array[3-1].array[1-1] = Fractions_dup (p.x);
  v.array[3-1].array[2-1] = Fractions_dup (p.y);
  v.array[3-1].array[3-1] = Fractions_one ();
  return PolyMatrix3D_set (PolyMatrix3D_init (), v);
}

void _M2_Transform3D_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}

void _M2_Transform3D_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
