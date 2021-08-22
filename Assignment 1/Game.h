#pragma once

#include <vector>

#include "GameState.h"
#include "Player.h"


// Primary game class.
// Stores all game related values.
class BlockerGame
{
public:
	void Initialize();
	void Cleanup();
	void Run();

private:
	// Game state vector, top state is active state
	std::vector<GameState*> state;
};

void BlockerGame::Initialize()
{
	state.push_back(new MainMenu());
}

// Clean up data.
void BlockerGame::Cleanup()
{
	
}

// Runs
void BlockerGame::Run()
{
	while (state.size() != 0)	
		if (!state.back()->Run())
		{
			delete state.back();
			state.pop_back();
		}

}