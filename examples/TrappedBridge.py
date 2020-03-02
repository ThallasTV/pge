#!/usr/bin/env python3

import pge, sys
from pygame.locals import *

pge.interactive ()

t = pge.rgb (1.0/2.0, 2.0/3.0, 3.0/4.0)
wood_light = pge.rgb (166.0/256.0, 124.0/256.0, 54.0/256.0)
wood_dark = pge.rgb (76.0/256.0, 47.0/256.0, 0.0)
red = pge.rgb (1.0, 0.0, 0.0)
green = pge.rgb (0.0, 1.0, 0.0)
blue = pge.rgb (0.0, 0.0, 1.0)
blue_dark = pge.rgb (0.1, 0.1, 0.8)
steel = pge.rgb (0.5, 0.5, 0.5)
copper = pge.rgb (0.5, 0.3, 0.2)
gold = pge.rgb (0.8, 0.6, 0.15)
ball_size = 0.02
boarder = 0.01
white = pge.rgb (1.0, 1.0, 1.0)
gap = 0.01
captured = None
sides = []
yellow = pge.rgb (0.8, 0.6, 0.15)
fps_text = None
last_fps = 0
angle = 0
pi2 = (3.14*2)
t1 = None

def myquit (e):
    print("Goodbye!")
    sys.exit (0)

def key_pressed (e):
    if e.key --K_ESCAPE:
        myquit (e)

def placeBoarders (thickness, color):
    print("placing the boarders")
    e1 = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    e2 = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    e3 = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    e4 = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    return e1, e2, e3, e4

def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)

def placeRamps ():
   ## r1 = pge.poly4 (0.05 , 0.4,
     #               0.6, 0.4,
      #              0.6, 0.4,
       #             0.05 ,0.46, blue).fix ()
    r2 = pge.poly4 (0.15, 0.6,
                    0.75, 0.6,
                    0.75, 0.6,
                    0.15, 0.6, wood_dark).fix ()


def push_it (o, e):
    p = e.collision_between ()
    if p != None and p != []:
        for i in p:
            if i != o:
                i.put_xvel (i.get_xvel () * 1.15)
                i.put_yvel (i.get_yvel () * 1.15)


def timer (e = None, f = None):
    global angle, t1
    print ("timer called: ", angle)
    angle += 20
    angle = angle % 360
    t1.rotate (angle * pi2 / 360.0)
    pge.at_time (0.1, timer)

def placeTriangle (p0, p1, p2, colour):
    global t1
    t1 = pge.poly3 (p0[0], p0[1], p1[0], p1[1], p2[0], p2[1], colour).on_collision (push_it).fix ()




def mouse_hit (e):
    global gb
    mouse = pge.pyg_to_unit_coord (e.pos)
    if e.button == 1:
        gb.put_xvel (gb.get_xvel ()-0.3)
    elif e.button == 3:
        gb.put_xvel (gb.get_xvel ()+0.3)
    elif gb.moving_towards (mouse[0], mouse[1]):
        ball = gb.get_unit_coord ()
        print ("mouse ="), mouse, ("ball ="), ball
        gb.apply_impulse (pge.sub_coord (mouse, ball), 0.3)
    else:
        gb.put_yvel (gb.get_yvel ()+0.3)

def snap_it (e, o):
    o.rm ()

def drop_gb (e, o):
    gb = placeBall (gold, 0.7, 0.92, 0.03).mass (2.0)
    print("Ball is dropped")
    pge.at_time (6.0, drop_gb)

def placeSilos ():
    for x in [0.1, 0.2]:
        pge.poly4 (x, 0.0,
                   x, 0.07,
                   x+0.01, 0.07,
                   x+0.01, 0.0, red).fix ()

        pge.poly4 (x+0.25, 0.0,
                   x+0.25, 0.07,
                   x+0.26, 0.07,
                   x+0.26, 0.0, green).fix ()

        pge.poly4 (x+0.5, 0.0,
                   x+0.5, 0.07,
                   x+0.51, 0.07,
                   x+0.51, 0.0, blue).fix ()

        pge.poly4 (x+0.75, 0.0,
                   x+0.75, 0.07,
                   x+0.76, 0.07,
                   x+0.76, 0.0, yellow).fix ()


def main ():
    global gb, sides, springs

    spring_power = 1000.0
    damping = 7.0
    snap_length = 1.0

    placeBoarders (0.01, wood_dark)
   # placeRamps ()
    placeSilos ()
   # t1 = placeTriangle ([0.2, 0.3+0.3], [0.4, 0.3+0.3], [0.3, 0.4+0.3], white)
    placeTriangle ([0.2, 0.3+0.3], [0.4, 0.3+0.3], [0.3, 0.4+0.3], white)
    timer ()
    left = placeBall (wood_light, 0.05, 0.45, 0.03).fix ()
    right = placeBall (wood_light, 0.95, 0.45, 0.03).fix ()

    prev = left
    springs = []
    for x in range (5, 95, 20): #3rd value in the parameter deals with interation
       # pge.at_time (2.0, drop_gb)
        step = placeBall (wood_dark, float (x) / 100.0, 0.33, 0.03).mass (0.9)
        s = pge.spring (prev, step, spring_power, damping, 0.1).draw (yellow, 0.002)
        s.when (snap_length, snap_it)
        springs += [s]
        prev = step

    s = pge.spring (right, prev, spring_power, damping, 0.1).draw (yellow, 0.002)
    s.when (snap_length, snap_it)
    #pge.at_time (2.0, drop_gb)
    drop_gb (10, None)
    print("before run")
    pge.record ()
    pge.draw_collision (True, False)
    pge.collision_colour (red)
    pge.gravity ()
    pge.dump_world ()
    pge.slow_down (2.5)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.display_set_mode ([600, 1000])
    pge.local_fps ()
    pge.run (10.0)
    pge.finish_record ()

print("before main()")
main ()
