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

#   include "GpopWorld.h"
#   include "GtwoDsim.h"
#   include "GdeviceGroff.h"
#   include "GFractions.h"
#   include "GPoints.h"
#   include "GmacroObjects.h"

#   define testCorner FALSE
#   define testRight FALSE
static Fractions_Fract size;

/*
   placeWall - 
*/

static void placeWall (void);

/*
   fireCue - 
*/

static void fireCue (void);

/*
   placeWall - 
*/

static void placeWall (void);

/*
   fireCue - 
*/

static void fireCue (void);


/*
   placeWall - 
*/

static void placeWall (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 2, 10), Fractions_initFract (0, 8, 10)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), Fractions_initFract (0, 6, 10), Fractions_initFract (0, 1, 10));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 2, 10), Fractions_initFract (0, 2, 10)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), Fractions_initFract (0, 6, 10), Fractions_initFract (0, 1, 10));
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   fireCue - 
*/

static void fireCue (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  if (testCorner)
    if (testRight)
      /* this will hit the right corner  */
      m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 8, 10), Fractions_initFract (0, 5, 10)));
    else
      /* this will hit the left corner  */
      m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 2, 10), Fractions_initFract (0, 5, 10)));
  else
    /* fire against the wall  */
    m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 5, 10), Fractions_initFract (0, 5, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (3));
  popWorld_velocity (Points_initPoint (Fractions_initFract (0, 1, 2), Fractions_negate (Fractions_initFract (2, 0, 0))));
  popWorld_populate (m, FALSE, TRUE);
  twoDsim_simulateFor (0.75);
}

void _M2_wall_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (FALSE);
  size = Fractions_initFract (0, 1, 21);
  placeWall ();
  fireCue ();
}

void _M2_wall_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
