# shapeLib from Project 3: LCD Game
## Introduction

ShapeLib provides a framework for rendering simple graphical elements
called AbShapes.  AbShapes represent abstract shapes that can be
rendered at any screen position.  

Two structs are defined that are used to represent pixel positions:

 - Vec2 structs store (row, col) pairs and are used to specify pixel location coordinates and 
   vectors between pixel locations.  Utility functions that compute foundational arithmetic 
   operations upon Vec2s such as addition, subtraction, and absolute value.

 - Rect structs represent rectangular regions.   They are implemented as a pair of Vec2 structs 
   specifying the region's top-left and bottom-right coordinates.

## Abstract Shapes

An AbShape can be arbitrarily positioned by specifying the pixel coordinates of its "logical" center.

An AbShape is implemented as a struct that contains:

 - a pointer to a "getBounds" function that computes the bounding rectangle surrounding an AbShape.

 - a pointer to a "check" function that determines whether an contains a specified pixel locatin.

Both functions require the following two parameters:

 - shape: a pointer to the AbShape.  Shape may be used by these functions to determine attributes of the AbShape.

 - center: a pointer to a Vec2 specifying the screen coordinates of the shape's center.

Additional parameters required for each function:

 - the getBounds function's third parameter "bounds" is a pointer to a Region structure.

 - the check function's third parameter "pixel" is a pointer to a Vec2 specifying the pixel 
   coordinate being queried.


## AbShapes defined in this library

 - An AbRect defines a filled rectangle.  HalfSize is a Vec2 specifiying the relative (row, col) 
   screen coordinte of its bottom-right corner.  The other 3 corners are mirror 
   reflections of this vector.  

 - AbRectOutline is a single-pixel width outline of a rectangle.  Like AbRect, an AbRectOutline's 
   size is also specified by a HalfSize vector.
 
 - AbRArrow is a right-pointing arrow.  The arrow's size is determined by a "size" field in this 
   struct.

## Layering

A layering model is also defined.  Layers are represented by "Layer" structs which can be stacked in a linked list.  Each layer contains:

 - shape: a pointer to an AbShape.
 - center: the screen coordinate of shape's center.
 - color: the shape's color.
 - next: the next element in the linked list.  The linked list is terminated by a zero pointer.

## Demo code

- Shapedemo.c displays multiple abshapes without using layering.  It can be loaded using the "load" make
production.

- Shapedemo2.c displays multiple abshapes using layering.  It can be
  loaded using the "load2" make production.

- Shapedemo3.c slices a right triangle off of a square.  This is a
  powerful idiom worth examining carefully.  It can be loaded using
  the "load3" make production.

## Suggested exercises

In order to explore shape rendering, students are encouraged to create additinal "demo" programs that: 

 - render rectangles with different heights, widths, and colors

 - like, shapedemo3, slice out portions of a rectangle.  

 - define additional AbShapes such as diamond and rectangular boxes
   containing text strings.

 - create composite shapes that are unions, intersections, or even XORs of other shapes

## Installing the shape lib (for other programs)

$ make install

## See Also

shapeLib requires lcdLib (in directory ../lcdLib).  Be sure to "make install" it first!

circleLib (in directory ../circleLib) defines AbCircles of various diameters.  It requires shapeLib.

Shape-motion-demo (in directory shape-motion-demo) implements moving AbShapes.

