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


// AI controlled players, do not ask for input and automatically makes a move.
class AIRandomPlayer : public Player
{
public:
	AIRandomPlayer(int id) { playerID = id; };
	bool GetPlayerTurn(Board* board);
};