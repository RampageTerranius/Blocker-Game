#include "Board.h"

#include <algorithm>

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

// Deconstructor
Board::~Board()
{
	DeleteBoard();
}

void Board::CreateBoard(int width, int height)
{
	// Check width and height, they MUST be at least 3 wide and high.
	if (width < 3)
		width = 3;
	if (height < 3)
		height = 3;


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

	// Print top arrow for currently selected column.
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
				case -1:// Crosser
					std::cout << " C " << "|";
					break;
				case 1: // Blocker
					std::cout << " B " << "|";
					break;
				}

			// print arrow on right side for column if selected.
			if (selectedY == i)
				std::cout << "<";

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

	// Print top arrow for currently selected column.
	std::cout << " ";
	for (int i = 0; i < curWidth; i++)
	{
		std::cout << "   ";
		if (selectedX == i)
			std::cout << "^";
		else
			std::cout << " ";
	}
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
int Board::CheckForWin()
{
	// Check for crosser win
	std::vector<int> rows;	

	int currentColumn = 0;

	// Check all of first column for crosser pieces.
	for (int i = 0; i < curHeight; i++)
		if (board[0][i] == -1)
			rows.push_back(i);	

	while (rows.size() > 0 && currentColumn < curWidth - 1)
	{
		// Check for above and below cells that are connected to this cell, add them to the list if they are connected.
		// Check cells above current.		

		for (size_t n = 0; n < rows.size(); n++)
		{
			for (int i = rows[n] - 1; i >= 0; i--)
				if (board[currentColumn][i] == -1)
				{
				
					if (std::find(rows.begin(), rows.end(), i) == rows.end())
						rows.push_back(i);
				}
				else
					break;

			// Check cells below current.
			for (int i = rows[n] + 1; i < curHeight; i++)
				if (board[currentColumn][i] == -1)
				{
					if (std::find(rows.begin(), rows.end(), i) == rows.end())
						rows.push_back(i);
				}
				else
					break;
		}

		std::vector<int> tempRows;
		// Check for chains to cells in next column.
		for (size_t n = 0; n < rows.size(); n++)
		{			
			if (board[currentColumn][rows[n]] == -1)
			{
				

				// Check top right cell.
				if (rows[n] > 0)
					if (board[currentColumn + 1][rows[n] - 1] == -1)
						tempRows.push_back(rows[n] - 1);

				// Check right cell.
				if (board[currentColumn + 1][rows[n]] == -1)
					tempRows.push_back(rows[n]);

				// Check bottom right cell.
				if (rows[n] < curHeight)
					if (board[currentColumn + 1][rows[n] + 1] == -1)
						tempRows.push_back(rows[n] + 1);
			}

			// Remove any duplicate values.
			if (tempRows.size() != 0)
			{
				std::sort(tempRows.begin(), tempRows.end());
				tempRows.erase(std::unique(tempRows.begin(), tempRows.end()), tempRows.end());				
			}			
		}

		// Check if we got any values, if we did, increase the currentColumn count.
		if (tempRows.size() != 0)
			currentColumn++;
		rows = tempRows;
	}

	// If the final connected row we found is the same as the width, then we know the crosser won.
	if (currentColumn == curWidth - 1)
		return -1;


	// Check for blocker win.
	int blankSpacesLeft = 0;
	for (int i = 0; i < curWidth; i++)
		for (int n = 0; n < curHeight; n++)
			if (board[i][n] == 0)
				blankSpacesLeft++;

	// There is no spaces left, blocker wins.
	if (blankSpacesLeft == 0)
		return 1;

	// None of the above conditions have been met, no result.
	return 0;
}

// Checks if the move at cursor is valid.
// Returns true if valid, false if invalid.
bool Board::CheckIfValidMove()
{
	// If cell is already occupied move is invalid.
	if (board[selectedX][selectedY] != 0)
		return false;

	// Other wise, move is valid.
	return true;
}

// Checks if the given move is valid.
// Returns true if valid, false if invalid.
bool Board::CheckIfValidMove(int x, int y)
{
	// If cell is already occupied move is invalid.
	if (board[x][y] != 0)
		return false;

	// Other wise, move is valid.
	return true;
}

// Get a list of all valid (nothing current in cell) moves that can be done.
std::vector<Move> Board::GetAllValidMoves()
{
	std::vector<Move> moves;

	// Check the entire board for blank spots and return a list of them.
	for (int i = 0; i < curWidth; i++)
		for (int n = 0; n < curHeight; n++)
			if (board[i][n] == 0)
			{
				Move currMove(i, n);
				moves.push_back(currMove);
			}

	return moves;
}

// Add a move to the list of moves to process, this move is determined by current cursor location.
// This list is processed by ApplyMoves.
// Please note that ApplyMoves can only apply two moves at a time(front and back move).
bool Board::AddMove()
{
	// Check if move is valid, push move and return true.
	if (CheckIfValidMove())
	{
		moves.push_back({ selectedX, selectedY });		
		return true;
	}
	// Move was invalid, return false.
	return false;
}

// Add a move to the list of moves to process.
// This list is processed by ApplyMoves.
// Please note that ApplyMoves can only apply two moves at a time(front and back move).
bool Board::AddMove(int x, int y)
{
	// Check if move is valid, push move and return true.
	if (CheckIfValidMove(x, y))
	{
		moves.push_back({ x, y });
		return true;
	}
	// Move was invalid, return false.
	return false;
}

// Gets the two moves and applies them.
void Board::ApplyMoves()
{
	// Apply crossers move first.
	board[moves.front().x][moves.front().y] = -1;
	// Apply blockers move last.
	// This allows blocker to override crossers move if both chose same square.
	board[moves.back().x][moves.back().y] = 1;

	// clear the vector for next round.
	moves.clear();
}