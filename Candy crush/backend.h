#pragma once
#include "variables.h";
#ifndef BACKEND_H
#define BACKEND_H
#include <windows.h>

//displays the grid in cmd.
//used for testing
void display(int grid[row][column]);

//crushes the wrapped candies when matches are made.
void eliminatewrappedcandy(int grid[row][column]);

//checks if striped candies are being formed -when 4 candies of same color lie in same column, or row of grid-and forms them.
void stripedcandies(int grid[][column]);

//shifts the existing candies from the top, downwards filling the empty spaces where candies have been crushed.
void shift(int grid[row][column]);
void wrappedcandy(int grid[][column]);

//Checks for existing matches in the grid when it is initialized
int initialMatchCheck(int grid[row][column]);

// If player swaps striped candy with wrapped candy, then 3 rows and 3 columns centered on the candy that was swapped will be cleared. 
void wrappedPlusStriped(int grid[row][column], int a1, int b1, int a2, int b2);

//refills the grid with new candies
void refill(int grid[row][column]);

//checks if color bomb is being formed, when 5 candies of same color lie in row or column. 
void candybomb(int grid[][column]);

//Calculates the points with respect to the color of candies being crushed.
void score(int scoreGrid[][column], int grid[][column]);

//creates a copy of the grid
//this function assists the score function in calculating points
void copyOfGrid(int scoreGrid[][column], int grid[row][column]);

//Randomly initializes the grid with candies
void initialize(int grid[row][column]);

//eliminates three by three square around wrapped candy, used in eliminate color bomb function
void eliminatethreeBythree(int k, int l);

//dislays the score on the screen.
void showscore(int points, int turn);

//checks if player swaps color bomb with another color bomb, then crushes all the candies on the grid
//checks if player swaps color bomb with a striped candy, then transforms all the candies of the respective color into striped candies and clears the rows and columns accordingly
//checks if player swaps color bomb with wrapped candy, then transforms all the candies of the respective color into wrapped candiesy. All candies in (3 x 3) square area, around swapped wrapped candy, will also be crushed.  
void eliminatecolorbomb(int grid[row][column], int x1, int Y1, int x2, int y2);

//saves the game into a file.
void savetofile();

//loads the previously saved game from file.
void pastetogrid();

//swaps the position of two candies picked by the player
void swap(int grid[][column], int a1, int b1, int a2, int b2);

//checks for matches of 3 candies
void simplythree(int grid[][column]);

//Checks if player swaps wrapped candy with another wrapped candy, then crushes all  candies in (5 x 5) square area around swapped candies
void eliminateWrappedPlusWrapped(int grid[row][column], int a1, int b1, int a2, int b2);
#endif