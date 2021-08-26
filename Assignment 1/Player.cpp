#include "Player.h"

#include <stdlib.h>

bool HumanPlayer::GetPlayerTurn(Board* board)
{
	// Print board for first screen.
	board->PrintBoard();

	bool chosen = false;
	while (!chosen)
	{
		// Print current player.
		if (playerID == -1)
			std::cout << "Crosser's turn!\n";
		else
			std::cout << "Blocker's turn!\n";

		// Print controls.
		std::cout << "wsad for movement, e to enter move into selected cell\n"
			      << "press x at any time to quit\n";

		// Get next pressed key from user and process it.
		int input = _getch();		
		switch (input)
		{
		// Move cursor up.
		case (int)'w': 
			board->MoveCursor(0, -1);
			system("CLS");
			board->PrintBoard();
			break;

		// Move cursor down.
		case (int)'s': 
			board->MoveCursor(0, 1);
			system("CLS");
			board->PrintBoard();
			break;

		// Move cursor left.
		case (int)'a':
			board->MoveCursor(-1, 0);
			system("CLS");
			board->PrintBoard();
			break;

		// Move cursor right.
		case (int)'d':
			board->MoveCursor(1, 0);
			system("CLS");
			board->PrintBoard();
			break;

		// Enter current cell as move.
		case (int)'e':
			if (board->AddMove(playerID))
				return true;
			else
				std::cout << "\nInvalid move!\n";
			break;

		// Quit from program.
		case (int)'x':
			return false;
			break;
		}
	}

	return true;
}