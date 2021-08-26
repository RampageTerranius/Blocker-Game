#pragma once
#include "GameState.h"

#include <vector>

// Primary game class.
// Stores all game related values.
class BlockerGame
{
public:
	void Initialize();
	void Run();
	void PushState(GameState* newState);
	void PopState();

private:
	// Game state vector, top state is active state
	std::vector<GameState*> state;
};


extern BlockerGame game;