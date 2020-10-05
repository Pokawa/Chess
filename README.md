# Chess

Chess is a 3D chess game visualizer. Built using C++, openGL, GLFW and GLM. 

## Required
```
opengl 3.3
libglfw3
libglm-dev
```

## Compilation

download: 
```
git clone https://github.com/pokawa/Chess.git
```

cd into downloaded repository

compile and run:
```
make
./main_file
```

## Features

Spherical camera movement

![Gif of camera movement](https://i.ibb.co/nP1BRgN/cam.gif "Spherical camera")


Dynamicly animated models

![Gif of models animation](https://i.ibb.co/QPVhLYP/animation.gif "animated model")

Models are shared, so for 32 visible pieces, memory contains only 6 different models (except for the board)

## Gamefiles

To read game from the file, just drop it on the window.
Files are not checked for game laws correctness to make them more flexible.
In fact there is plenty of different games that can be represented in this format, not only the classic chess.

### file format

First two lines are for names of the player, first white, second black, both spaces allowed.
Then there are two rows of \[oa-j]\[01-9] tuples, 16 each, one for every chessman.
These are starting positions for all of the pieces, always in order of: king, queen, 2x rook, 2x knight, 2x bishop and 8x pawn.
Position of **o0** means that chessman is not present on the board.
After that there is a series of rounds in format of:

**who from what where**
```
b h4 m h6
```
who can be values **b** for black and **w** for white, after that comes position of piece that is moving, then what kind of action is this, and finally destination position.
Posiible kinds of actions are: **m** for move, **t** for take, **e** for en passant, **l** for long castling, **s** for short one, **p** for promotion, **q r k b** fro different priomotions, and lastly **w** for a winning round.

example file: 
```
whoite
block
e1 d1 a1 h1 b1 g1 c1 f1 a2 b2 c2 d2 e2 f2 g2 h2
e8 d8 a8 h8 b8 g8 c8 f8 a7 b7 c7 d7 e7 f7 g7 h7
w h2 m h4
b h7 m h5
w e2 m e3
b h8 m h6
w d1 t h5
b h6 m a6
w h5 m a5
b a6 t a5
w h4 m h5
b a5 m a6
w h5 m h6
b a6 m a5
w h6 m h7
b a5 m a6
w h7 mtpq g8
w o0 w o0
```
for more excample files look into **games** folder
