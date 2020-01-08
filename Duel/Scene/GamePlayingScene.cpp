#include <DxLib.h>
#include "GamePlayingScene.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "../Peripheral.h"

#include "../Player.h"
#include "../Judge.h"
#include "../Hud.h"


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
		if (p.IsTrigger(i, "DECIDE"))
		{
			_updater = &GamePlayingScene::FadeoutUpdate;
			break;
		}
		if (p.IsTrigger(i, "PAUSE"))
		{
			SceneManager::Instance().PushScene(std::make_unique<PauseScene>());
			break;
		}
		_players[i]->Update(i, p);
	}

	if ((_players[0]->GetPlayerData().skill != Skill::MAX) && ((_players[1]->GetPlayerData().skill != Skill::MAX)))
	{
		_judge->JudgeResult(static_cast<int>(_players[0]->GetPlayerData().skill), static_cast<int>(_players[1]->GetPlayerData().skill));
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
		if (_judge->GetResult() == Result::DRAW)
		{
			_players[0]->Damage(_players[1]->GetPower());
			_players[1]->Damage(_players[0]->GetPower());
		}
		else if(_judge->GetResult() == Result::PLAYER1WIN)
		{
			_players[1]->Damage(_players[0]->GetPower());
		}
		else if (_judge->GetResult() == Result::PLAYER2WIN)
		{
			_players[0]->Damage(_players[1]->GetPower());
		}

		for (auto player : _players)
		{
			player->SetHand();
		}

		if (_hud->AdvanceTheTurn())
		{
			for (auto player : _players)
			{
				player->ResetCount();
			}
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
	_hud.reset(new Hud());

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

	_hud->Draw(_players[0]->GetPlayerData(), _players[1]->GetPlayerData());
	//_hud->DrawHp(_players[0]->GetHp(), _players[1]->GetHp());

	(this->*_drawer)();

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
