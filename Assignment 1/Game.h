#pragma once

#include "Board.h"
#include "Player.h"

// Primary game class.
// Stores all game related values.
class BlockerGame
{
public:
	void Initialize();
	void Cleanup();
	void Run();
	void GetPlayerInput();

private:
	Board* board;
	bool running;
	int currentPlayer;
	Player players[2];
};

void BlockerGame::Initialize()
{
	board = new Board(9, 9);
	running = true;
	currentPlayer = 1;
}

// Clean up data.
void BlockerGame::Cleanup()
{
	board->DeleteBoard();
	delete board;
}

void BlockerGame::Run()
{
	while (running)
	{
		board->PrintBoard();

		GetPlayerInput();
		running = !running;
	}
}

void BlockerGame::GetPlayerInput()
{

}