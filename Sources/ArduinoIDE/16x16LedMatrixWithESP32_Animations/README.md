# Description

This version of the project is built upon the original, but with a [16x16 led matrix board](https://www.aliexpress.com/item/1005005648151934.html).
The board contains 4 8bit drivers, 2 for the 16 rows and 2 for the 16 columns.
The sketch code is modified to map a 16x16 matrix, and to push four bytes at each cycle instead of two. the data is pushed in the following order:
high rows (8-15), low rows (0-7), low columns (0-7), high columns (8-15).
This order can be explained if we look at the order of the drivers as they are layed out on the board.

Along this implementation, a well-structured animation classes are used. these classes shows various animations and the base classes can be further inherited to expand the animation set.
Some animations are interactive, including two well known games

To control the animation set, six simple push buttons are connected to provide a way to interact with the program. Up, Down, Left, Right, Back and Enter buttons are placed for this purpose.

A well-structured code is added to provide generic and expandable way to read and response to the buttons input.

Animation list:  
BeatingHeart - a simple heart beating. buttons control the speed of the animation.  
TheMatrix - a cool animation inspired by the iconic matrix code. buttons control the speed and density of the animation.  
Spiral - a spiral that fill the screen and the empty it. buttons control the speed of the animation.  
TextDisplay - a demo of text being displayed. all english charaters are mapped correctly. Hebrew characters also but the resolution is not sufficient to distinctively show each character.  
SnakeGame - a simple implementation of the classic Snake game. buttons control the snake.  
TetrisGame - a simple implementation of the classic tetris game. the impl' is incomplete but the core of the game works correctly. Left and Right buttons move the tetriminos, Up and Down buttons rotate it.  

# Connecting it together
The led matrix board is connected in the same way, there's no change.
Six push buttons are connected directly between six pins on the ESP32 board and the ground.

# Results
The enter button switches to the next animation in the set.
The back button resets the current animation.
The Up, Down, Left and Right buttons control eacn animation in a different way.


# Modifying the Code
The animation base classes can easily be expanded to add more animations.
Simply inherit from InteractiveAnim class, and add your implementation.
Then, add its header to the sketch .ino file, increase the "ANIME_COUNT" definition, and add it to the anime switch selector in the function "initCurrAnime".

