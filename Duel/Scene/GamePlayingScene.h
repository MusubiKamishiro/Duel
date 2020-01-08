#pragma once
#include <memory>
#include <array>
#include "Scene.h"
#include "../Geometry.h"

class Player;
class Judge;
class Hud;

class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*_updater)(const Peripheral& p);
	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);
	void RoundUpdate(const Peripheral& p);
	void ResultUpdate(const Peripheral& p);

	void (GamePlayingScene::*_drawer)();
	void RoundDraw();
	void GameDraw();
	void ResultDraw();

	std::array<std::shared_ptr<Player>, 2> _players;	
	std::unique_ptr<Judge> _judge;
	std::unique_ptr<Hud> _hud;

	int _count = 0;	

public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p);
	void Draw();
};
