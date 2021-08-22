#pragma once

#include "Board.h"

// Primary game class.
// Stores all game related values.
class BlockerGame
{
public:
	void Initialize();
	void Cleanup();
	void Run();

private:
	Board* board;
	bool running;
};

void BlockerGame::Initialize()
{
	board = new Board(9, 9);
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
		running = !running;
	}
}