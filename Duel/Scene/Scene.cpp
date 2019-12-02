#include "Scene.h"
#include "../Game.h"


Scene::Scene()
{
	_pal = 255;
	_scrSize = Game::Instance().GetScreenSize();
}


Scene::~Scene()
{
}
