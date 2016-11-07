# circleLib from Project 3: LCD Game
## Introduction

circleLib provides a framework for rendering circles. Circles 
are represented by chord vectors that represent the distance of 1/2 
of a chord from a radius to the circumference as shown below.

           
        x |-x        chord[3] = 1
     x    |----x       .. [2] = 3
    x     |-----x      .. [1] = 5
    x           x      .. [0] = 5
    x           x   
     x         x    
        x   x       
        

## Generating chordVecs and circle source files (run make install)

makeCircles.c: Generates a set of chordVec and AbCircles of various radii and
places the definitions in circles.h and circlesR.c where R is the
radius of the circle. 

## Abstract Circles

Abstract circles are subtype of abstract shapes that include
a radius, position and chord vector. As with an abstract shape
an abstract circle includes functions for bounding rectangles
and a pixel check. 

## Demo Code

circledemo.c: Use shape library to draw a circle.

## Suggested Excercises

- Modify technique from shapeLib's "shapedemo3" to draw pac-man figures.
- Define a pac-man abShape that includes parameters to control mouth size and orientation
