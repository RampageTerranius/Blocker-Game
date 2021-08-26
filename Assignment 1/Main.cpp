/*********** Declaration*******
I hereby certify that no part of this assignment has been copied from
any other student’s work or from any other source. No part of the code
has been written/produced for me by another person or copied from any
other source.
I hold a copy of this assignment that I can produce if the original is
lost or damaged.
**************************/

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