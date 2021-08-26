#include "Board.h"

// Default constructor.
Board::Board()
{
	// Set some default values.
	active = false;
	curWidth = curHeight = 0;
	selectedX = selectedY = 0;
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
	// If the board is not active we can not print it.
	if (!active)
		return;

	// Print currently selected column.
	std::cout << " ";
	for (int i = 0; i < curWidth; i++)
	{
		std::cout << "   ";
		if (selectedX == i)
			std::cout << "v";
		else
			std::cout << " ";
	}

	// Print number of each row.
	std::cout << "\n   ";
	for (int i = 0; i < curWidth; i++)
		std::cout << " " << i << "  ";
	std::cout << "\n";

	// Print top vertical line for looks.
	std::cout << "  -";
	for (int i = 0; i < curWidth; i++)
		std::cout << "----";

	std::cout << "\n";

	// Print by Row -> Column.		
		for (int i = 0; i < curHeight; i++)
		{
			// Print either a space or arrow depending on if this is the selected column.
			if (selectedY == i)
				std::cout << ">";
			else
				std::cout << " ";

			std::cout << i << "|";
			// printing is reversed here as to show the board correctly.
			for (int n = 0; n < curWidth; n++)
				// Print symbol depending on owned player.
				switch (board[n][i])
				{
				case 0: // Empty
					std::cout << "   " << "|";
					break;
				case -1:// Blocker
					std::cout << " B " << "|";
					break;
				case 1: // Crosser
					std::cout << " C " << "|";
					break;
				}

			// Add space between each line.
			std::cout << "\n";

			if (i < curHeight - 1)
				std::cout << "\n";
		}

	// Print bottom vertical line for looks.
	std::cout << "  -";
	for (int i = 0; i < curWidth; i++)
		std::cout << "----";
	std::cout << "\n";
}

void Board::MoveCursor(int xVal, int yVal)
{
	// Prepare some temporary values.
	int tempX, tempY;
	tempX = selectedX;
	tempY = selectedY;

	tempX += xVal;
	tempY += yVal;

	// Check if values would be within board bounds and apply them if they are.
	if (tempX >= 0 && tempX < curWidth)
		if (tempY >= 0 && tempY < curHeight)
		{
			selectedX = tempX;
			selectedY = tempY;
		}
}

// Checks for a win condition and returns winner.
// Returns:
// -1 for crosser win
//  0 for no result
//  1 for blocker win
//  2 for draw
int Board::CheckForWin()
{
	return 0;
}

// Checks if the given move is valid.
// Returns true if valid, false if invalid.
bool Board::CheckIfValidMove()
{
	// If cell is already occupied move is invalid.
	if (board[selectedX][selectedY] != 0)
		return false;

	// Other wise, move is valid.
	return true;
}

bool Board::AddMove(int player)
{
	// Check if move is valid, apply move and return true.
	if (CheckIfValidMove())
	{
		board[selectedX][selectedY] = player;
		return true;
	}
	// Failed to apply move, return false.
	return false;
}