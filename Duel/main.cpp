#include "Game.h"

int main(void)
{
	Game& game = Game::Instance();
	game.Initialize();
	game.InitPeripheral();
	game.Run();
	game.Terminate();
}
