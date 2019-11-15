#include "GamePlayingScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "SceneManager.h"
#include "ResultScene.h"
#include "PauseScene.h"

#include "../Player.h"
#include "../Judge.h"


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
	for (int i = 0; i < 2; ++i)
	{
		if (p.IsTrigger(i, "decide"))
		{
			updater = &GamePlayingScene::FadeoutUpdate;
			break;
		}
		if (p.IsTrigger(i, "pause"))
		{
			SceneManager::Instance().PushScene(std::make_unique<PauseScene>());
			break;
		}
	
		player->Update(i, p);
	}

	judge->JudgeResult(player->GetHand(0), player->GetHand(1));
}

GamePlayingScene::GamePlayingScene()
{
	player.reset(new Player());
	judge.reset(new Judge());

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
	judge->Draw();

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, ssize.x, ssize.y, 0x000000, true);
}
