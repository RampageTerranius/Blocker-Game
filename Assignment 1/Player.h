#pragma once
#include "Board.h"

#include <conio.h>
// Player class, handles input etc...
class Player
{
public:
	virtual bool GetPlayerTurn(Board* board) { return false; };
	int PlayerID() { return playerID; };

protected:
	int playerID;
};

// Human controlled player, asks for user input
class HumanPlayer : public Player
{
public:
	HumanPlayer(int id) { playerID = id; };
	bool GetPlayerTurn(Board* board);
};

// AI controlled player, does not ask for input and automatically makes a move.
class AIPlayer : public Player
{
public:
	AIPlayer(int id) { playerID = id; };
	bool GetPlayerTurn(Board* board);
};