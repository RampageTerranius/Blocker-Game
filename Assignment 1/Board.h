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

// Default constructor.
Board::Board()
{
	// Set some default values.
	active = false;
	curWidth = curHeight = 0;
	board = nullptr;
}

// Constructor.
Board::Board(int width, int height)
{
	CreateBoard(width, height);
}

Board::~Board()
{
	DeleteBoard();
}

void Board::CreateBoard(int width, int height)
{
	if (!active)
	{
		// Prepare board to store dynamic 2d array.
		// Create row objects.
		board = new int* [width];

		// Create column objects.
		for (int i = 0; i < width; i++)
			board[i] = new int[height];

		// Assign default values to each cell.
		for (int i = 0; i < width; i++)
			for (int n = 0; n < height; n++)
				board[i][n] = 0;

		// Set variables for cleaning up data in deconstructor.
		curHeight = height;
		curWidth = width;		

		// Board is now active, set active to true.
		active = true;
	}
}

// Checks if board is active and completely deletes all data for it.
void Board::DeleteBoard()
{
	if (active)
	{
		// Clear all dynamically addressed data.
		// Clear all row objects.
		for (int i = 0; i < curWidth; i++) {
			delete[] board[i];
		}

		// Clear all column objects.
		delete[] board;

		// Set board to inactive.
		active = false;
	}
}

// Prints the current board onto the screen.
void Board::PrintBoard()
{
	// Print number of each row
	std::cout << "  ";
	for (int i = 0; i < curWidth; i++)
		std::cout << " " << i << "  ";
	std::cout << "\n";

	// Print top vertical line for looks.
	std::cout << " -";
	for (int i = 0; i < curWidth; i++)
		std::cout << "----";

	std::cout << "\n";

	// Print by Row -> Column.	
	if (active)
		for (int i = 0; i < curHeight; i++)
		{
			std::cout << i << "|";
			// printing is reversed here as to show the board correctly.
			for (int n = 0; n < curWidth; n++)
				// Print symbol depending on owned player.
				switch (board[n][i])
				{
				case 0:
					std::cout << "   " << "|";
					break;
				case -1:
					std::cout << " B " << "|";
					break;
				case 1:
					std::cout << " C " << "|";
					break;
				}				
			
			// Add space between each line
			std::cout << "\n";

			if (i < curHeight - 1)
				std::cout << "\n";
		}

	// Print bottom vertical line for looks.
	std::cout << " -";
	for (int i = 0; i < curWidth; i++)
		std::cout << "----";
}