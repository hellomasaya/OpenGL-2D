#Assignment 1 - Jetpack Joyride 2D
==================================

#3Harshita Sharma

###Run game:
- mkdir build/
- cd build/
- cmake ..
- make all
- ./graphics_asgn1

###Elements(all have beautiful representation):
-    Player - with better Representation(BONUS)
-    Wall
-    Platform
-    Coins - 2 types
-    Fireline
-    Firebeam
-    Dragon(BONUS)
-    Boomerang
-    Sword(BONUS)
-    2 Special flying objects - arrow and diamond
-    Magnet
-    Score
-    Level

###Gameplay:
-    Zooming
-    Automatic Panning
-    Upward movement using Jetpack
-    LEft-Right movement

###Controls:
-    Arrow left - Left
-    Arrow right - Right
-    SPACE - Up
-    Drag(Trackpad) - Zoom

###Scoring:
-    Levels : 3
-    Points 0-20 : Level 1
-    Points 20-50 : Level 2
-    Points 50-75 : Level 3
-    Initial score: 10 Points.
-    Colliding with yellow coins : 5 Points
-    Colliding with pink coins : 3 Points.
-    Colliding with firebeam : -2 Points.
-    Colliding with fireline : -1 Points.
-    Colliding with boomerang(fox) : -4 Points.
-    Colliding with Dragon : -20 Points.
-    After reaching level 2 the magnet become active.
-    After reaching level 3 the dragonbecomes active.
-    **Score and Level displayed using 7-Segment Display.

###Physics:
-   Gravity
-    Magnet influences player's motion
-    Projectile nature of special flying objects(power-ups)


