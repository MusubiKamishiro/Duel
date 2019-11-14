#include "Scene.h"
#include "../Game.h"


Scene::Scene()
{
	pal = 255;
	ssize = Game::Instance().GetScreenSize();
}


Scene::~Scene()
{
}
