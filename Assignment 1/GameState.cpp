#include "GameState.h"
#include "Game.h"
#include "Player.h"

#include <stdlib.h>

// PlayingGame functions.
// Constructor.
PlayingGame::PlayingGame()
{
	board = new Board(9, 9);
	currentPlayer = -1;

	crosserPlayer = new AIRandomPlayer(-1);
	blockerPlayer = new AIRandomPlayer(1);
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
	// Clear console (incase coming back to main menu) and print credits.
	system("CLS");
	std::cout << "Blocker Game\n"
		      << "Created by Tyler Brown\n\n";

	int result = 0;

	// Continue to loop until user enters 0 for exit.
	do
	{
		std::cout << "==Main Menu==\n"
			<< "0 = Exit\n"
			<< "1 = play\n"
			<< "Please enter your choice: ";

		// Attempt to convert input into a number and if fails return -1.
		try
		{
			std::string str;
			std::cin >> str;

			result = std::stoi(str);
		}
		catch (std::exception e)
		{
			result = -1;
		}

		// Determine what to do from given input.
		switch (result)
		{
		case 0: // Exit program
			std::cout << "\nExiting...\n"
				<< "Thank you for playing!\n";
			break;

		case 1:
			std::cout << "\nStarting game...\n";
			game.PushState(new PlayingGame());
			return true;
			break;

		default: // no acceptable input given. 
			std::cout << "\nInvalid input\n";
			break;
		}
	} while (result != 0);

	return false;
}
