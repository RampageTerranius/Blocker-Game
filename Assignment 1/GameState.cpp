#include "GameState.h"
#include "Game.h"


// PlayingGame functions.
// Constructor.
PlayingGame::PlayingGame()
{
	board = new Board(9, 9);
	currentPlayer = 1;
}

// Deconstructor.
PlayingGame::~PlayingGame()
{
	board->DeleteBoard();
	delete board;
}

// Main loop when in PlayingGame state.
bool PlayingGame::Run()
{
	return false;
}

// Switch the current player.
void PlayingGame::SwitchPlayer()
{
	if (currentPlayer == 1)
		currentPlayer = -1;
	else
		currentPlayer = 1;
}

// MainMenu functions.
// Main loop when in MainMenu state.
bool MainMenu::Run()
{
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
