#include "Game.h"

int main(int argc, char* argv[])
{
	// BlockerClass will handle all initialization.
	game.Initialize();

	// BlockerClass will handle running loop.
	game.Run();

	// BlockerClass will handle cleanup upon exit.
	game.Cleanup();

	return 0;
}