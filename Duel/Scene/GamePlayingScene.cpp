#include "GamePlayingScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "PauseScene.h"

#include "../Player.h"


void GamePlayingScene::FadeinUpdate(const Peripheral & p)
{
	if (pal > 255)
	{
		pal = 255;
		updater = &GamePlayingScene::WaitUpdate;
	}
	else
	{
		pal += 20;
	}
}

void GamePlayingScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		SceneManager::Instance().ChangeScene(std::make_unique<ResultScene>());
	}
	else
	{
		pal -= 20;
	}
}

void GamePlayingScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, PAD_INPUT_1))
	{
		updater = &GamePlayingScene::FadeoutUpdate;
	}
	if (p.IsTrigger(0, PAD_INPUT_8))
	{
		SceneManager::Instance().PushScene(std::make_unique<PauseScene>());
	}
	for (int i = 0; i < 2; ++i)
	{
		player->Update(i, p);
	}
}

GamePlayingScene::GamePlayingScene()
{
	player.reset(new Player());
	updater = &GamePlayingScene::FadeinUpdate;
}

GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void GamePlayingScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DxLib::DrawString(0, 0, "ゲームシーン", 0xff0000);
	player->Draw();

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}
