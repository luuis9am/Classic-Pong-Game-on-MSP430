# Project 3: LCD Game
## Introduction

Continuing your effort to help ACME Solutions provide Christmas toys, 
your task is now to develop a game for the LCD screen.  You should 
utilize the knowledge you havegained working with the buttons and 
buzzer.  In addition, a series of libraries have been found to assist
you in creating your game.

Students can propose alternate projects that demonstrate
similar skills.  These proposals must approved by the course
instructor in writing (e.g. email) at least two weeks before the
project due date. 

## Requirements
Your game should meet the following minimum criteria:

- dynamically render graphical elements that move
-- including one original algorithmically rendered graphical element 
- handle colisions properly with other shapes and area boundaries
- produce sounds triggered by game events
-- in a manner that does not cause the game to pause
- communicate with the player using text
- include a state machine written in assembly language
- respond to user input (from buttons)

Don't forget to properly document your source code and how to play the game.

## Grading Criteria

Your lab will be graded based on the proficiencies it demonstrates.
While we appreciate the complexity of an
arcade quality game, our primary objective is that you demonstrate
course-relevant skills including

- relevant development tools such as make and emacs
- use of timer interrupts to control program timing
- use of switch interrupts to determine when swiches change
- modularization into multiple source files (including header files)
- use of explicit state machines to implement program functionality
- ability to develop or modify (and of course use) linked data structures in c
- mature programming
-- readable, appropriate algorithms, modularization, data structures, symbol names etc

Below is an example of a sample "pong" application that would fully satisfy
requirments.  The graphics would include

- an arena to play in
- a ball
- two paddles (using a shape of your own design)
- a score

And behaviors that include

- the ball moves in 2d, with direction changing when it collides with
  screen elements
- a sound plays when a collision occurs
-- without causing the ball's motion to pause
- scores
 - that advance through multiple rounds of play
 - that the ball either moves in-front-of or behind

## Libraries

Several libraries are provided.  
They can be installed by the default production of Makefile in the repostiory's 
root directory, or by a "$make install" in each of their subdirs.

- timerLib: Provides code to configure Timer A to generate watchdog timer interrupts at 250 Hz

- p2SwLib: Provides an interrupt-driven driver for the four switches on the LCD board and a demo program illustrating its intended functionality.

- lcdLib: Provides low-level lcd control primitives, defines several fonts, 
and a simple demo program that uses them.

- shapeLib: Provides an translatable model for shapes that can be translated 
and rendered as layers.

- circleLib: Provides a circle model as a vector of demi-chord lengths,
pre-computed circles as layers with a variety of radii, 
and a demonstration program that renders a circle.


## Demonstration program

- shape-motion-demo: A demonstration program that uses shapeLib to represent
and render shapes that move.


