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
		_updater = &GamePlayingScene::RoundUpdate;
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
	for (int i = 0; i < _players.size(); ++i)
	{
		if (p.IsTrigger(i, "decide"))
		{
			_updater = &GamePlayingScene::FadeoutUpdate;
			break;
		}
		if (p.IsTrigger(i, "pause"))
		{
			SceneManager::Instance().PushScene(std::make_unique<PauseScene>());
			break;
		}
		_players[i]->Update(i, p);
	}

	if ((_players[0]->GetHand() != 3) && ((_players[1]->GetHand() != 3)))
	{
		_judge->JudgeResult(_players[0]->GetHand(), _players[1]->GetHand());
		_updater = &GamePlayingScene::ResultUpdate;
		_drawer = &GamePlayingScene::ResultDraw;
	}
}

void GamePlayingScene::RoundUpdate(const Peripheral& p)
{
	if (_count > 60)
	{
		_updater = &GamePlayingScene::WaitUpdate;
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
		if (_turnCount == 3)
		{
			for (auto player : _players)
			{
				player->ResetCount();
			}
			++_roundCount;
			_turnCount = 1;
		}
		else
		{
			++_turnCount;
		}

		for (auto player : _players)
		{
			player->SetHand();
		}
		_updater = &GamePlayingScene::RoundUpdate;
		_drawer = &GamePlayingScene::RoundDraw;
		_count = 0;
	}
	else
	{
		++_count;
	}
}

void GamePlayingScene::RoundDraw()
{
	std::string round = "ラウンド";
	std::string turn = "ターン";
	round += std::to_string(_roundCount);
	turn += std::to_string(_turnCount);
	DxLib::DrawString(500, 0, round.c_str(), 0x00ff00);
	DxLib::DrawString(500, 20, turn.c_str(), 0x00ff00);

	for (auto player : _players)
	{
		player->HandDraw();
	}
}

void GamePlayingScene::GameDraw()
{
}

void GamePlayingScene::ResultDraw()
{
	for (auto player : _players)
	{
		player->Draw();
	}
	_judge->Draw();
}

GamePlayingScene::GamePlayingScene()
{
	for (int i = 0; i < _players.size(); ++i)
	{
		_players[i].reset(new Player(Vector2<int>(150 * (i + 1), 150)));
	}
	_judge.reset(new Judge());

	_updater = &GamePlayingScene::FadeinUpdate;
	_drawer  = &GamePlayingScene::RoundDraw;
}

GamePlayingScene::~GamePlayingScene()
{
}

void GamePlayingScene::Update(const Peripheral& p)
{
	(this->*_updater)(p);
}

void GamePlayingScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	DxLib::DrawString(0, 0, "ゲームシーン", 0xff0000);
	
	(this->*_drawer)();

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
