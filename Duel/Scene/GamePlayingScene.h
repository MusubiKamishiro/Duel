#pragma once
#include <memory>
#include <array>
#include "Scene.h"
#include "../Geometry.h"

#include "../Player.h"
class Judge;


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

	int _count;	
	int _bgm;

	// エフェクトリソース
	int _bgEffect;
	int _effectTime;
	Vector2<float> _effectPos;
	int _playingEffect;

public:
	GamePlayingScene(const std::array<InitStatus, 2>& initStatus, std::array<bool, 2>& aiFlags);
	~GamePlayingScene();

	void Update(const Peripheral& p);
	void Draw();
};
