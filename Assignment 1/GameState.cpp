#include "GameState.h"
#include "Game.h"
#include "Player.h"

#include <stdlib.h>

// PlayingGame functions.
// Constructor.
PlayingGame::PlayingGame(int player1Type, int player2Type)
{
	board = new Board(9, 9);
	currentPlayer = -1;

	// Determien what kind of palyer to put into each slot
	// Crosser player.
	switch (player1Type)
	{
	case 0: // Human.
		crosserPlayer = new HumanPlayer(-1);
		break;

	case 1: // AI - Random.
		crosserPlayer = new AIRandomPlayer(-1);
		break;

	}

	// Blocker player.
	switch (player2Type)
	{
	case 0: // Human.
		blockerPlayer = new HumanPlayer(1);
		break;

	case 1: // AI - Random.
		blockerPlayer = new AIRandomPlayer(1);
		break;
	}
}

// Deconstructor.
PlayingGame::~PlayingGame()
{
	board->DeleteBoard();
	delete board;
	delete crosserPlayer;
	delete blockerPlayer;
}

// Main loop when in PlayingGame state.
bool PlayingGame::Run()
{
	// Clear console.
	system("CLS");

	// get the players move and switch to next player.
	bool result;
	result = GetPlayerTurn();

	// Only apply user moves/check for win conditions once blocker has set his move.
	if (currentPlayer == 1)
	{
		// Apply moves of players.
		board->ApplyMoves();

		// Check for any win conditon
		switch (board->CheckForWin())
		{
		case -1:
			board->PrintBoard(); // print the final result of the board.
			std::cout << "Crosser wins!\n"
				      << "Press any key to finish match\n";
			_getch(); // wait for user to push a key before continuing.
			return false;
			break;

		case 1:
			board->PrintBoard(); // print the final result of the board.
			std::cout << "Blocker wins!\n"
					  << "Press any key to finish match\n";
			_getch(); // wait for user to push a key before continuing.
			return false;
			break;
		}
	}

	// Switch player after getting moves/applying moves and checking for win conditions.
	SwitchPlayer();
	

	return result;
}

// Switch the current player.
void PlayingGame::SwitchPlayer()
{
	// If the current player is blocker then apply both moves.
	if (currentPlayer == 1)		
		currentPlayer = -1;
	else
		currentPlayer = 1;
}

// Get the players turn.
// If the user entered a move return true, if the user hit esc then return false.
bool PlayingGame::GetPlayerTurn()
{
	if (currentPlayer == -1)
		return crosserPlayer->GetPlayerTurn(board);
	else
		return blockerPlayer->GetPlayerTurn(board);
}

// MainMenu functions.
// Main loop when in MainMenu state.
bool MainMenu::Run()
{
	bool running = true;
	int selectedOption = 0;
	int player1Type = 0;
	int player2Type = 0;

	// Continue to loop until user enters 0 for exit.
	while (running)
	{
		// Clear console (incase coming back to main menu) and print credits.
		system("CLS");
		std::cout << "Blocker Game\n"
			<< "Created by Tyler Brown\n\n";

		// Print main menu.
		std::cout << "==Main Menu==\n";

		if (selectedOption == 0)
			std::cout << ">Play\n";
		else
			std::cout << " Play\n";

		if (selectedOption == 1)		
			std::cout << ">Player 1: ";
		else
			std::cout << " Player 1: ";

		switch (player1Type)
		{
		case 0:
			std::cout << "Human\n";
			break;
		case 1:
			std::cout << "AI - Random\n";
			break;
		}

		if (selectedOption == 2)
			std::cout << ">Player 2: ";
		else
			std::cout << " Player 2: ";

		switch (player2Type)
		{
		case 0:
			std::cout << "Human\n";
			break;
		case 1:
			std::cout << "AI - Random\n";
			break;
		}

		if (selectedOption == 3)
			std::cout << ">Exit\n";
		else
			std::cout << " Exit\n";

		// Get next pressed key from user and process it.
		int input = _getch();
		switch (input)
		{
			// Move cursor up.
		case (int)'w':
			selectedOption--;
			if (selectedOption < 0)
				selectedOption = 0;
			break;

			// Move cursor down.
		case (int)'s':
			selectedOption++;
			if (selectedOption > 3)
				selectedOption = 3;
			break;

			// Move cursor left.
		case (int)'a':
			if (selectedOption == 1)
			{
				player1Type--;
				if (player1Type < 0)
					player1Type = 0;
			}
			if (selectedOption == 2)
			{
				player2Type--;
				if (player2Type < 0)
					player2Type = 0;
			}
			break;

			// Move cursor right.
		case (int)'d':
			if (selectedOption == 1)
			{
				player1Type++;
				if (player1Type > 1)
					player1Type = 1;
			}
			if (selectedOption == 2)
			{
				player2Type++;
				if (player2Type > 1)
					player2Type = 1;
			}
			break;

			// Enter current cell as move.
		case (int)'e':	
			// Determine what to do from given input.
			switch (selectedOption)
			{
			case 0:
				std::cout << "\nStarting game...\n";
				game.PushState(new PlayingGame(player1Type, player2Type));
				return true;
				break;

			case 3: // Exit program
				std::cout << "\nExiting...\n"
					<< "Thank you for playing!\n";

				running = false;
				break;
			}
			break;
		}		
	}


	return false;
}
