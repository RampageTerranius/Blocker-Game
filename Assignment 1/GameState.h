#pragma once
#include "Board.h"
#include "Player.h"

#include <string>

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

private:
	void SwitchPlayer();
	bool GetPlayerTurn();
	Board* board;
	int currentPlayer; // -1 = crosser, 1 = blocker.
	Player* player1;
	Player* player2;
};


// State of being in the main menu.
// During this state the user is in the main menu.
class MainMenu : public GameState
{
public:
	bool Run();
};