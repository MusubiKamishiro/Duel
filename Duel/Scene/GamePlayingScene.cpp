#include <DxLib.h>
#include "GamePlayingScene.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "../Peripheral.h"

#include "../Player.h"
#include "../Judge.h"


void GamePlayingScene::FadeinUpdate(const Peripheral & p)
{
	if (_pal > 255)
	{
		_pal = 255;
		updater = &GamePlayingScene::RoundUpdate;
	}
	else
	{
		_pal += 20;
	}
}

void GamePlayingScene::FadeoutUpdate(const Peripheral & p)
{
	if (_pal <= 0)
	{
		SceneManager::Instance().ChangeScene(std::make_unique<ResultScene>());
	}
	else
	{
		_pal -= 20;
	}
}

void GamePlayingScene::WaitUpdate(const Peripheral & p)
{
	for (int i = 0; i < players.size(); ++i)
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
		players[i]->Update(i, p);
	}

	if ((players[0]->GetHand() != 3) && ((players[1]->GetHand() != 3)))
	{
		judge->JudgeResult(players[0]->GetHand(), players[1]->GetHand());
		updater = &GamePlayingScene::ResultUpdate;
		drawer = &GamePlayingScene::ResultDraw;
	}
}

void GamePlayingScene::RoundUpdate(const Peripheral& p)
{
	if (_count > 60)
	{
		updater = &GamePlayingScene::WaitUpdate;
		_count = 0;
	}
	else
	{
		++_count;
	}
}

void GamePlayingScene::ResultUpdate(const Peripheral& p)
{
	if (_count > 60)
	{
		++_roundCount;
		for (auto player : players)
		{
			player->SetHand();
		}
		updater = &GamePlayingScene::RoundUpdate;
		drawer = &GamePlayingScene::RoundDraw;
		_count = 0;
	}
	else
	{
		++_count;
	}
}

void GamePlayingScene::RoundDraw()
{
	std::string s = "ラウンド";
	s += std::to_string(_roundCount);
	DxLib::DrawString(500, 0, s.c_str(), 0x00ff00);
}

void GamePlayingScene::GameDraw()
{
}

void GamePlayingScene::ResultDraw()
{
	for (auto player : players)
	{
		player->Draw();
	}
	judge->Draw();
}

GamePlayingScene::GamePlayingScene()
{
	for (int i = 0; i < players.size(); ++i)
	{
		players[i].reset(new Player(Vector2<int>(150 * (i + 1), 150)));
	}
	judge.reset(new Judge());

	updater = &GamePlayingScene::FadeinUpdate;
	drawer  = &GamePlayingScene::RoundDraw;
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
	
	(this->*drawer)();

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
