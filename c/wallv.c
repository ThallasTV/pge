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
   fireBox - 
*/

static void fireBox (void);

/*
   placeWall - 
*/

static void placeWall (void);

/*
   fireCue - 
*/

static void fireCue (void);

/*
   fireBox - 
*/

static void fireBox (void);


/*
   placeWall - 
*/

static void placeWall (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 1, 10), Fractions_initFract (0, 1, 10)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_red (), Fractions_initFract (0, 1, 10), Fractions_initFract (0, 8, 10));
  /* 
   m := moveTo(m, initPoint(initFract(0, 0, 0), initFract(0, 0, 0))) ;
   m := rectangle(m, TRUE, zero(), red(), one(), initFract(0, 1, 10)) ;

   m := moveTo(m, initPoint(initFract(0, 0, 0), initFract(0, 8, 10))) ;
   m := rectangle(m, TRUE, zero(), red(), one(), initFract(0, 1, 10)) ;
  */
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
  /* fire against the wall  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 5, 10), Fractions_initFract (0, 5, 10)));
  m = macroObjects_circle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), size);
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (3));
  /* 
   popWorld.velocity(initPoint(initFract(2, 0, 0), negate(initFract(1, 0, 0)))) ;
  */
  popWorld_velocity (Points_initPoint (Fractions_negate (Fractions_initFract (2, 0, 0)), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
  twoDsim_simulateFor (1.0);
}


/*
   fireBox - 
*/

static void fireBox (void)
{
  macroObjects_Macro m;

  m = macroObjects_initMacro ();
  /* fire against the wall  */
  m = macroObjects_moveTo (m, Points_initPoint (Fractions_initFract (0, 5, 10), Fractions_initFract (0, 5, 10)));
  m = macroObjects_rectangle (m, TRUE, Fractions_zero (), (deviceIf_Colour) deviceGroff_green (), Fractions_initFract (0, 1, 20), Fractions_initFract (0, 1, 20));
  m = macroObjects_rootMacro (m);
  popWorld_mass (Fractions_cardinal (3));
  /* 
   popWorld.velocity(initPoint(initFract(2, 0, 0), negate(initFract(1, 0, 0)))) ;
  */
  popWorld_velocity (Points_initPoint (Fractions_negate (Fractions_initFract (2, 0, 0)), Fractions_zero ()));
  popWorld_populate (m, FALSE, TRUE);
  twoDsim_simulateFor (1.0);
}

void _M2_wallv_init (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  popWorld_init (FALSE);
  size = Fractions_initFract (0, 1, 21);
  placeWall ();
  fireBox ();
}

void _M2_wallv_finish (__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
}
