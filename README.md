# John Conway's Game of Life

Hi! And thanks for showing interest in my repo. As the description says, this is a simple implmentation of 
John Conway's Game of Life I decided to make over a weekend.

## How to run

### Dependencies

In order to compile and run the program you're going to need:

* A Linux system or Linux VM.
* Header files for the POSIX threads and SDL2 libraries.

Any other dependencies of the program should be available on any Linux distribution, as it mostly uses Standard Library stuff.

### Compilation Instructions

* Create a `target` directory in the root of this repository.
* Invoke `make` from the root of this repository.

The compiled binary will then be available to you in `target/GameOfLife`.

## Usage

The program can be invoked in the following ways:

* `target/GameOfLife`: The program will begin the game with a randomized initial state.
* `target/GameOfLife <FILE_PATH>`: The program will begin, using the state defined by the text file located in `<FILE_PATH>`.
* `target/GameOfLife --create | -c <FILE_PATH>/<FILE_NAME>`: The program will generate a randomized initial state file of name `<FILE_NAME>` in `<FILE_PATH>`. 
* `target/GameOfLife --help | -h`: Prints the program ussage manual to stdout.

## Input files

The input files for initial states are stored as plain text. An input file consists solely of a matrix of 1s and 0s where a 1 indicate the position is alive and 0 
indicates it's dead. For example, a 10x10 grid for a beacon pattern would translate into the following input file:

```
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 1 1 0 0 0 0 0 0
0 0 1 0 0 0 0 0 0 0
0 0 0 0 0 1 0 0 0 0
0 0 0 0 1 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```

In its current state the program only supports working on a 50x50 grid. However, one of the next goals is the add the ability to specify the grid dimmensions via command line arguments.

## Iteration Ideas:

This is more of a personal section so I can keep track of the things I want to implement later on. Following iterations of the project would add:

* Ability to specify grid-dimmensions via command line arguments.
* Ability to specify thread-count via command-line arguments.
* Ability to modify the probability of a cell being alive when generating initial states via command-line arguments
* Ability to specify the time delta between generations via command-line arguments
* Ability to pause/unpause the game by clicking on the display window.