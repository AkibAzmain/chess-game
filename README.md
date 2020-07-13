# A chess game, in terminal

-------------------------------------------------------

I just made this game for practicing C++ programming. You can play this game very easily in terminal. But remember, to play this game you have to be honest.

## Compiling

This game doesn't use any libraries other than C++ standard library. So, this game doesn't have any extenal dependency and should compile easily with any compiler on any OS. To compile this game, I have created a `Makefile` . You'll need `g++` and `make` installed on a linux computer. Just open a terminal and change working directory to downloaded repository, then execute this:

```bash
make
```

Or you can also do this:

```bash
g++ chess.cpp mini-chess.cpp -o chess
```

I don't know why, but it compiles even with `gcc` (GNU C Compiler) on linux. If you don't have C++ compiler but have GNU C compiler, you can try like this (it should also work on your computer, but I'm not sure):

```bash
make CXX=gcc CXXFLAGS=-lstdc++
```

For other compilers and operating systems, use appropriate commands. You can try this:

```bash
make CXX=CommandOfYourCompiler
```

If you don't know the command, just Google "How to compile C++ program with your compiler on your OS".

After compiling, you'll get a executable named `chess` . As this executable doesn't depend on any files in the repository, you can place it anywhere you want.

## Playing

To game this game, just start the executable by executing

```bash
./chess
```

After starting, you'll see a output like this:

```
  +---+---+---+---+---+---+---+---+
8 | r | n | b | q | k | b | n | r |
  +---+---+---+---+---+---+---+---+
7 | p | p | p | p | p | p | p | p |
  +---+---+---+---+---+---+---+---+
6 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
5 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
4 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
3 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
2 | P | P | P | P | P | P | P | P |
  +---+---+---+---+---+---+---+---+
1 | R | N | B | Q | K | B | N | R |
  +---+---+---+---+---+---+---+---+
    a   b   c   d   e   f   g   h
```

Here uppercase letters are pieces of white and lowercase letters are pieces of black. The meaning every letters are:

Letter | Piece
-- | --
K | King
Q | Queen
B | Bishop
N | Knight
R | Rook
P | Pawn

After the board, you'll see a prompt which will want command. Commands are:

Command | Meaning
--------| -------
play    | Start playing
move    | Just one move for white, one for black
reset   | Reset the board
exit    | Exit the game

To start playing, just type `play` and hit enter. You'll see a prompt again like this:

```
white >>>
```

Here, `white` means it's white's turn. In the prompt, type the square where the piece is now, then hit space key, and type the square where the piece will go. Note that this game will check if the move is valid, but it won't be able to check correctly most of the time. Here is an example:

```
white >>> e2 e4
  +---+---+---+---+---+---+---+---+
8 | r | n | b | q | k | b | n | r |
  +---+---+---+---+---+---+---+---+
7 | p | p | p | p | p | p | p | p |
  +---+---+---+---+---+---+---+---+
6 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
5 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
4 |   |   |   |   | P |   |   |   |
  +---+---+---+---+---+---+---+---+
3 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
2 | P | P | P | P |   | P | P | P |
  +---+---+---+---+---+---+---+---+
1 | R | N | B | Q | K | B | N | R |
  +---+---+---+---+---+---+---+---+
    a   b   c   d   e   f   g   h
```

Here, white moved the pawn at e2 square to e4 square.

After entering white's move, you'll see a similar prompt again, like this:

```
black >>>
```

It means it's black's turn. Now enter your move and you'll see the result after the move.

To get out from playing mode, type exit and hit enter. You'll return to the default mode. Note that this command is disabled for black, as this will cause black to lose his chance to move.

## For enthusiasts and developers

In this repository, the file `chess-ui.cpp` contains the main function, `chess.h` contains declarations of namespaces, classes, functions and `chess.cpp` contains their definitions.