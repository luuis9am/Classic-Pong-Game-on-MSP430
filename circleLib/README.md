# circleLib from Project 3: LCD Game
## Introduction

circleLib provides a framework for rendering circles. Circles 
are represented by vectors that represent the distance of 1/2 
of a chord from a radius to the circumference as shown below.

           
        x |-x        chord[2] = 1
     x    |----x       .. [1] = 3
    x     |-----x      .. [0] = 5
    x           x   
     x         x    
        x   x       
        
## Abstract Circles

Abstract circles are subtype of abstract shapes that include
a radius, position and chord vector. As with an abstract shape
an abstract circle includes functions for bounding rectangles
and a pixel check. 

## Demo Code

makeCircles.c: Generates a set of circles of various sizes and
places the definitions in circles.h and circlesR.c where R is the
radius of the circle. These can then be compiled into code for
use elsewhere instead of having to compute them as needed.

circledemo.c: Draws a circle, square and prints a string.

## Suggested Excercises
