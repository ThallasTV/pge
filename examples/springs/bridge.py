#!/usr/bin/env python

import pge, sys
from pygame.locals import *


print("starting exampleBoxes")
# pge.batch ()
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


def myquit (e):
    print("goodbye")
    sys.exit (0)

def key_pressed (e):
    if e.key == K_ESCAPE:
        myquit (e)

def placeBoarders (thickness, color):
    print("placeBoarders")
    e1 = pge.box (0.0, 0.0, 1.0, thickness, color).fix ()
    e2 = pge.box (0.0, 0.0, thickness, 1.0, color).fix ()
    e3 = pge.box (1.0-thickness, 0.0, thickness, 1.0, color).fix ()
    e4 = pge.box (0.0, 1.0-thickness, 1.0, thickness, color).fix ()
    return e1, e2, e3, e4

def placeBall (kind, x, y, r):
    return pge.circle (x, y, r, kind)

def snap_it (e, o):
    o.rm ()

def drop_gb (e, o):
    gb = placeBall (steel, 0.7, 0.92, 0.03).mass (2.0)
    # pge.at_time (3.0, drop_gb)

def main ():
    global gb, sides, springs

    spring_power = 1000.0
    damping = 10.0
    snap_length = 0.16

    placeBoarders (0.01, wood_dark)

    left = placeBall (wood_light, 0.25, 0.45, 0.03).fix ()
    right = placeBall (wood_light, 0.75, 0.45, 0.03).fix ()

    prev = left
    springs = []
    for x in range (35, 75, 10):
        step = placeBall (wood_dark, float (x) / 100.0, 0.33, 0.03).mass (0.9)
        s = pge.spring (prev, step, spring_power, damping, 0.1).draw (yellow, 0.002)
        s.when (snap_length, snap_it)
        springs += [s]
        prev = step

    s = pge.spring (right, prev, spring_power, damping, 0.1).draw (yellow, 0.002)
    s.when (snap_length, snap_it)
    pge.at_time (0.6, drop_gb)
    drop_gb (None, None)
    print("before run")
    pge.record ()
    pge.draw_collision (False, False)
    pge.collision_colour (red)
    pge.gravity ()
    pge.dump_world ()
    pge.slow_down (6.0)  # slows down real time by a factor of
    pge.register_handler (myquit, [QUIT])
    pge.register_handler (key_pressed, [KEYDOWN])
    pge.display_set_mode ([1000, 1000])
    pge.local_fps ()
    pge.run (10.0)
    pge.finish_record ()

print("before main()")
main ()
