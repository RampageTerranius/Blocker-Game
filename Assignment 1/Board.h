#pragma once

// Board class.
// Used to store data todo with the board.
class Board
{
public:
	Board();
	Board(int width, int height);
	~Board();

	void CreateBoard(int width, int height);
	void DeleteBoard();

private:
	bool active; // If the board has been assigned and is ready for use.
	int curWidth, curHeight; // The current width and height of the board.
	int** board;
	// 0 = no user
	//-1 = blue player
	// 1 = red player
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
		// Create column objects.
		board = new int* [width];

		// Create row objects.
		for (int i = 0; i < width; i++)
			board[i] = new int[height];

		// Assign default values to each cell.
		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				board[i][j] = 0;

		// Set variables for cleaning up data in deconstructor.
		curWidth = width;
		curHeight = height;

		// Board is now active, set active to true.
		active = true;
	}
}

// Checks if board is active and completely deles all data for it.
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
