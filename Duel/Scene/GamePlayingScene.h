#pragma once
#include <memory>
#include <array>
#include "Scene.h"
#include "../Geometry.h"

class Player;
class Judge;

class GamePlayingScene : public Scene
{
private:
	void (GamePlayingScene::*updater)(const Peripheral& p);
	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);
	void RoundUpdate(const Peripheral& p);
	void ResultUpdate(const Peripheral& p);

	void (GamePlayingScene::*drawer)();
	void RoundDraw();
	void GameDraw();
	void ResultDraw();

	std::array<std::shared_ptr<Player>, 2> players;	
	std::unique_ptr<Judge> judge;

	int _count		= 0;	
	int _roundCount = 1;
public:
	GamePlayingScene();
	~GamePlayingScene();

	void Update(const Peripheral& p);
	void Draw();
};
