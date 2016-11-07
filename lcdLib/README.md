# lcdLib from Project 3: LCD Game
## Introduction

lcdLib provides primitives for a pixel, rectangle, clearing the screen and a 5x7 font. Handles all the lower-level "messy stuff". 


Two types are defined (used as shortcut to typing "unsigned [type]"):

 - u_char : unsigned char

 - u_int : unsigned int

## Files

 - lcdutils.h, lcdutils.c: these provide the lowest level interface to
   the lcd such as

    - lcd_init: initialization of the lcd
    - defining screenWidth and screeenHeight
    - colors (at end of lcdutils.h (represented as 16 bit BGR values: 5 bits of blue, 6 bits
      of green, and 5 bits of red)
    - lcd_setArea, lcd_writeColor: methods for selecting rectangular
      regions and setting the colors of the pixels they contain.
    

 - lcddraw.h: simple drawing facilities that utilize lcdutils

 - lcddraw.c: 
     - drawPixel(): sets the color of a pixel
     - fillRect(): fill a rectangle with a color
     - drawChar5x7, drawString5x7: draws characters/strings at
     particular locations

 - font5x7.c, font11x16.c font8x12.c: tables of bitmapped fonts

## Demo code

lcddemo.c is a program that displays a string and a rectangle.  A
"load" make production loads it into the launchpad board.

## Suggested exercises

In order to explore shape rendering, students are encouraged to create additinal "demo" programs that: 

 - draw a diagonal line (for example, where row = col or row = screenWidth-col)

 - draw a filled or outline of a right triangle

 - draw the other fonts hidden in the source files

## Installing the LCD lib (for other programs)

$ make install

## See Also

lcdLib requires timerLib (in directory ../timerLib).  Be sure to "make install" it first!
