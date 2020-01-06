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
static Fractions_Fract size;
static deviceIf_Colour light;
static deviceIf_Colour dark;

/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m);

/*
   placeStairs - 
*/

static void placeStairs (void);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c);

/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m);

/*
   placeStairs - 
*/

static void placeStairs (void);

/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c);


/*
   placeBoundary - 
*/

static void placeBoundary (macroObjects_Macro m)
{
  /* left edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Fractions_initFract (0, 1, 100), Fractions_one ());
  /* right edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 99, 100), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Fractions_initFract (0, 1, 100), Fractions_one ());
  /* bot edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Fractions_one (), Fractions_initFract (0, 1, 100));
  /* top edge  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_initFract (0, 99, 100)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceIf_red (), Fractions_one (), Fractions_initFract (0, 1, 100));
}


/*
   placeStairs - 
*/

static void placeStairs (void)
{
  macroObjects_Macro m;
  unsigned int i;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 7, 10), Fractions_initFract (0, 6, 10)));
  m = macroObjects_triangle (m, TRUE, Fractions_zero (), dark, Points_initPoint (Fractions_initFract (0, 3, 10), Fractions_zero ()), Points_initPoint (Fractions_zero (), Fractions_initFract (0, 1, 10)));
  for (i=0; i<=5; i++)
    {
      m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 2+i, 10), Fractions_initFract (0, (long unsigned int) i, 10)));
      m = macroObjects_rectangle (m, TRUE, Fractions_zero (), light, Fractions_initFract (0, 8-i, 10), Fractions_initFract (0, 1, 10));
    }
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_zero (), Fractions_zero ()));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), light, Fractions_initFract (0, 1, 10), Fractions_one ());
  placeBoundary (m);
  m = macroObjects_rootMacro (m);
  popWorld_populate (m, TRUE, TRUE);
}


/*
   dropBall - 
*/

static void dropBall (deviceIf_Colour c)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  /* drop the ball at the top of stairs with a leftwards velocity  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 17, 20), Fractions_initFract (0, 15, 20)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), c, size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (1));
  popWorld_velocity (Points_initPoint (Fractions_zero (), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
}

void _M2_slope_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (TRUE);
  light = deviceIf_defineColour (Fractions_initFract (0, 166, 256), Fractions_initFract (0, 124, 256), Fractions_initFract (0, 54, 256));
  dark = deviceIf_defineColour (Fractions_initFract (0, 76, 256), Fractions_initFract (0, 47, 256), Fractions_zero ());
  size = Fractions_initFract (0, 1, 21);
  placeStairs ();
  dropBall ((deviceIf_Colour) deviceIf_green ());
  twoDsim_gravity (-9.81);
  twoDsim_simulateFor (1.0);
  dropBall ((deviceIf_Colour) deviceIf_yellow ());
  twoDsim_simulateFor (1.0);
  dropBall ((deviceIf_Colour) deviceIf_red ());
  twoDsim_simulateFor (1.0);
  /* dropBall(purple()) ;  */
  twoDsim_simulateFor (4.0);
}

void _M2_slope_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
