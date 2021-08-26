#include "Player.h"

#include <stdlib.h>

bool HumanPlayer::GetPlayerTurn(Board* board)
{
	// Print whos turn it is.

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


		int input = _getch();
		// Get next pressed key from user and process it.
		switch (input)
		{
		case (int)'w':
			board->MoveCursor(0, -1);
			system("CLS");
			board->PrintBoard();
			break;
		case (int)'s':
			board->MoveCursor(0, 1);
			system("CLS");
			board->PrintBoard();
			break;
		case (int)'a':
			board->MoveCursor(-1, 0);
			system("CLS");
			board->PrintBoard();
			break;
		case (int)'d':
			board->MoveCursor(1, 0);
			system("CLS");
			board->PrintBoard();
			break;
		case (int)'e':
			if (board->AddMove(playerID))
				return true;
			else
				std::cout << "Invalid move\n";
			break;

		case (int)'x':
			return false;
			break;
		}
	}

	return true;
}