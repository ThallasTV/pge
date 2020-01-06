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
#   include "GdeviceIf.h"
#   include "GFractions.h"
#   include "GPoints.h"
#   include "GmacroObjects.h"

#   define testCorner FALSE
#   define testRight FALSE
#   define useGroff FALSE
static deviceIf_Colour light;
static deviceIf_Colour dark;

/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m);

/*
   placeRamps - 
*/

static void placeRamps (void);

/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c, Fractions_Fract x);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c, Fractions_Fract x);

/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m);

/*
   placeRamps - 
*/

static void placeRamps (void);

/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c, Fractions_Fract x);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c, Fractions_Fract x);


/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m)
{
  /* left edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 1, 100), Fractions_one ());
  /* right edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 99, 100), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_initFract (0, 1, 100), Fractions_one ());
  /* bot edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_one (), Fractions_initFract (0, 1, 100));
  /* top edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_initFract (0, 99, 100)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), dark, Fractions_one (), Fractions_initFract (0, 1, 100));
}


/*
   placeRamps - 
*/

static void placeRamps (void)
{
  macroObjects_Macro m;
  macroObjects_Macro n;
  macroObjects_Macro p;

  m = macroObjects_initMacro ();
  n = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 3, 10), Fractions_initFract (0, 8, 10)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_initFract (0, 7, 10), Fractions_initFract (0, 1, 20)), Points_initPoint (Fractions_zero (), Fractions_initFract (0, 1, 40)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 7, 10), Fractions_initFract (0, 6, 10)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_negate (Fractions_initFract (0, 7, 10)), Fractions_initFract (0, 1, 20)), Points_initPoint (Fractions_zero (), Fractions_initFract (0, 1, 40)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 3, 10), Fractions_initFract (0, 4, 10)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_initFract (0, 7, 10), Fractions_initFract (0, 1, 20)), Points_initPoint (Fractions_zero (), Fractions_initFract (0, 1, 40)));
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 7, 10), Fractions_initFract (0, 2, 10)));
  m = macroObjects_angledRect (m, TRUE, Fractions_zero (), light, Points_initPoint (Fractions_negate (Fractions_initFract (0, 7, 10)), Fractions_initFract (0, 1, 20)), Points_initPoint (Fractions_zero (), Fractions_initFract (0, 1, 40)));
  placeBoundary (m);
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   dropBox - 
*/

static void dropBox (deviceIf_Colour c, Fractions_Fract x)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (x, Fractions_initFract (0, 37, 40)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), c, Fractions_initFract (0, 1, 20), Fractions_initFract (0, 1, 20));
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}


/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c, Fractions_Fract x)
{
  macroObjects_Macro m;
  Fractions_Fract size;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (x, Fractions_initFract (0, 37, 40)));
  size = Fractions_initFract (0, 1, 21);
  m = macroObjects_circle (m, TRUE, Fractions_zero (), c, size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_ramps2_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (useGroff);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  placeRamps ();
  /* 
   dropBox(green()) ;
  */
  twoDsim_gravity (-9.81);
  /* 
   twoDsim.skipFor(0.0) ;
  */
  dropBall ((deviceIf_Colour) deviceIf_yellow (), Fractions_initFract (0, 17, 20));
  dropBall ((deviceIf_Colour) deviceIf_purple (), Fractions_initFract (0, 14, 20));
  dropBox ((deviceIf_Colour) deviceIf_red (), Fractions_initFract (0, 10, 20));
  twoDsim_simulateFor (20.0);  /* 15.0 ok  */
}

void _M2_ramps2_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
