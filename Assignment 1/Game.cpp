#include "Game.h"

void BlockerGame::Initialize()
{
	state.push_back(new MainMenu());
}

// Gets the top (back) state in the array and runs it.
// Upon the top state exiting (returning false) the state is deleted and popped from the vector
void BlockerGame::Run()
{
	while (!state.empty())
		if (!state.back()->Run())
		{
			// If the state has ended (returned false) delete the object and pop it from the vector.
			PopState();
		}
}

// Clean up data.
void BlockerGame::Cleanup()
{

}

// Push the given state to the top (back) of the vector
// This makes the given state the active state.
void BlockerGame::PushState(GameState* newState)
{
	state.push_back(newState);
}

// Delete and pop the top (back) state.
void BlockerGame::PopState()
{
	delete state.back();
	state.pop_back();
}

BlockerGame game = BlockerGame();