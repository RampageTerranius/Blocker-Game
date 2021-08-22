#pragma once

#include "Board.h"

// Game state class handles every "state" or screen that is currently loaded into the game
class GameState
{
public:
	virtual bool Run() { return false; };
};

// State of currently playing game.
// During this state the game is activly playing
class PlayingGame : public GameState
{
public:
	PlayingGame();
	~PlayingGame();
	bool Run();

	void SwitchPlayer();

private:
	Board* board;
	int currentPlayer;
};

PlayingGame::PlayingGame()
{
	board = new Board(9, 9);
	currentPlayer = 1;
}

// Deconstructor
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

// State of being in the main menu.
// During this state the user is in the main menu
class MainMenu : public GameState
{
public:
	bool Run();
};

bool MainMenu::Run()
{
	std::cout << "Main Menu";

	return false;
}