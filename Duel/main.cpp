#include "Game.h"

void main(void)
{
	Game& game = Game::Instance();
	game.Initialize();
	game.Run();
	game.Terminate();
}
