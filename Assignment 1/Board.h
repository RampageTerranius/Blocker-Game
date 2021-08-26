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
	void MoveCursor(int xVal, int yVal);
	int CheckForWin(); // Returns -1 for crosser win, 1 for blocker win, 0 for no result and 2 for draw.
	bool CheckIfValidMove();
	bool AddMove(int player);
		

private:
	bool active; // If the board has been assigned and is ready for use.
	int curWidth, curHeight; // The current width and height of the board.
	int selectedX, selectedY; // What cell on the board is currently selected, used checkifvalidmove,printboard and addmove
	int** board;
	// 0 = no user
	//-1 = crosser
	// 1 = blocker
	// board is a dynamically assigned array using board[column][row] for access (or [x][y])
};