#pragma once

#include <iostream>

// Board class.
// Used to store data todo with the board.
class Board
{
public:
	// Constructors.
	Board();
	Board(int width, int height);

	// Deconstructors.
	~Board();

	// Board functions.
	void CreateBoard(int width, int height);
	void DeleteBoard();
	void PrintBoard();

private:
	bool active; // If the board has been assigned and is ready for use.
	int curWidth, curHeight; // The current width and height of the board.
	int** board;
	// 0 = no user
	//-1 = blue player
	// 1 = red player

	// board is a dynamically assigned array using board[column][row] for access (or [x][y])
};