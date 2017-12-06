# Project 3: Pong Video Game

## Introduction
Pong is a game that allows 2 players to use the msp430 to direct paddles in the left and right direction in an attempt to project the game ball into the opponents side of the screen. Once a paddle strikes the ball the velocity of the ball will increase therefor making  the game more difficulty. Once a player scores a total of 5 points the game ends, declares a winner and starts over.


## How to play

1. After connecting your msp430 to your machine it's necessary you enter "make load" via the emacs bufer, after doing so the game will begin to install and display the intro screen.

2. To start playing either press any of the buttons on your msp430 below the display

3. SW2 - SW3 controls the bottom paddle, while SW4 - SW5 controls the upper paddle

4. Whenever a player makes a goal the paddle of the opposing player will turn red indicating the last person to have been scored on. Both paddles will alternate colors as the ball interacts with the paddle.


## Functions within pong_game.c

#### movLayerDraw(MovLayer *movLayers, Layer *layers)

Function movLayerDraw() is taken from Lab3 demo "shape-motion_demo" shapemotion.c, which takes a given movLayer and a Layer which will be in charge of drawing and probing all moving layers.
param movLayers 
param layers

#### mlAdvance(MovLayer *ml, MovLayer *ml1, MovLayer *ml2, Region *fence)

Function m1Advance() is taken from Lab3 "shape-motion_demo" shapemotion.c

With modified functionality, m1Advance advances a moving shape within a vertical fence while incorporating logic statements to check if the game ball has collided with any of the paddles or upper fence. If a paddle is struck the ball's velocity will then increase. If the ball collides with the external fence a point will be added to corresponding player.

param ml The moving shape to be advanced 
param ml1 The moving paddle to be advanced
param ml2 The moving paddle to be advanced
param fence The region which will serve as a boundary for ml
 

#### wdt_c_handler()

Watchdog timer interrupt handler serves as handler for 15 interrupts/sec. Logic statements have been implemented for switch handlers on SW2-SW5 buttons SW2-SW5 that will move the corresponding paddles.
