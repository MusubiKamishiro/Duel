#include <DxLib.h>
#include "GamePlayingScene.h"
#include "ResultScene.h"
#include "SceneManager.h"
#include "PauseScene.h"
#include "../Peripheral.h"

#include "../Game.h"
#include "../Judge.h"
#include "../Hud.h"

#include "../Loader/FileSystem.h"
#include "../Loader/ImageLoader.h"
#include "../Loader/SoundLoader.h"


GamePlayingScene::GamePlayingScene(const std::array<InitStatus, 2> & initStatus, std::array<bool, 2> & aiFlags)
{
	_players[0].reset(new Player(Vector2<int>(_scrSize.x / 5, 125), initStatus[0], aiFlags[0]));
	_players[1].reset(new Player(Vector2<int>(_scrSize.x / 5 * 4, 125), initStatus[1], aiFlags[1]));

	_judge.reset(new Judge());
	Hud::Instance().Init();

	_count = 0;
	_bgm = Game::Instance().GetFileSystem()->Load("sound/bgm/game.mp3");

	_typeColor[0] = Game::Instance().GetFileSystem()->Load("img/ki.png");
	_typeColor[1] = Game::Instance().GetFileSystem()->Load("img/ao.png");
	_typeColor[2] = Game::Instance().GetFileSystem()->Load("img/aka.png");

	_updater = &GamePlayingScene::FadeinUpdate;
	_drawer = &GamePlayingScene::RoundDraw;
}

GamePlayingScene::~GamePlayingScene()
{
}

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
		Result _result;
		if (_players[0]->GetPlayerData().hp <= 0 && _players[1]->GetPlayerData().hp <= 0)
		{
			_result = Result::DRAW;
		}
		else if (_players[0]->GetPlayerData().hp <= 0)
		{
			_result = Result::PLAYER2WIN;
		}
		else if (_players[1]->GetPlayerData().hp <= 0)
		{
			_result = Result::PLAYER1WIN;
		}
		
		DxLib::StopSoundMem(_bgm);
		SceneManager::Instance().ChangeScene(std::make_unique<ResultScene>(_players[0]->GetPlayerData().img, _players[1]->GetPlayerData().img, _result));
	}
	else
	{
		_pal -= 20;
	}
}

void GamePlayingScene::WaitUpdate(const Peripheral & p)
{
	if (_count > 60)
	{
		if ((_players[0]->GetPlayerData().hp <= 0) || (_players[1]->GetPlayerData().hp <= 0))
		{
			_updater = &GamePlayingScene::FadeoutUpdate;
		}
		else
		{
			for (auto player : _players)
			{
				player->SetSkill();
			}
			if (Hud::Instance().AdvanceTheTurn())
			{
				for (auto player : _players)
				{
					player->ResetCount();
				}
			}

			_updater = &GamePlayingScene::RoundUpdate;
		}
		_count = 0;
	}
	else
	{
		for (auto& player : _players)
		{
			player->DamageUpdate(_count);
		}
		++_count;
	}
}

void GamePlayingScene::RoundUpdate(const Peripheral& p)
{
	for (int i = 0; i < _players.size(); ++i)
	{
		if (p.IsTrigger(i, "PAUSE"))
		{
			SceneManager::Instance().PushScene(std::make_unique<PauseScene>());
			break;
		}
		_players[i]->Update(i, _players[((i + 1) % _players.size())]->GetPlayerData(), p);
	}

	if ((_players[0]->GetPlayerData().skill != Skill::MAX) && ((_players[1]->GetPlayerData().skill != Skill::MAX)))
	{
		_judge->JudgeResult(static_cast<int>(_players[0]->GetPlayerData().skill), static_cast<int>(_players[1]->GetPlayerData().skill));
		_updater = &GamePlayingScene::ResultUpdate;
		_drawer = &GamePlayingScene::ResultDraw;
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
			DxLib::StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000);
			DxLib::StartJoypadVibration(DX_INPUT_PAD2, 1000, 1000);
		}
		else if(_judge->GetResult() == Result::PLAYER1WIN)
		{
			_players[1]->Damage(_players[0]->GetPower());
			DxLib::StartJoypadVibration(DX_INPUT_PAD2, 1000, 1000);
		}
		else if (_judge->GetResult() == Result::PLAYER2WIN)
		{
			_players[0]->Damage(_players[1]->GetPower());
			DxLib::StartJoypadVibration(DX_INPUT_PAD1, 1000, 1000);
		}

		_updater = &GamePlayingScene::WaitUpdate;
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

void GamePlayingScene::ResultDraw()
{
	_judge->Draw();
	for (auto& player : _players)
	{
		DxLib::DrawExtendGraph(player->GetPos().x - 200, 150, player->GetPos().x + 200, 550, 
			_typeColor[static_cast<int>(player->GetPlayerData().skill)], true);
	}
}

void GamePlayingScene::Update(const Peripheral& p)
{
	if (!DxLib::CheckSoundMem(_bgm))
	{
		DxLib::PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP);
	}

	(this->*_updater)(p);
}

void GamePlayingScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0xffffff, true);

	for (auto& player : _players)
	{
		player->Draw();
	}
	Hud::Instance().Draw(_players[0]->GetPlayerData(), _players[1]->GetPlayerData());

	(this->*_drawer)();

	// フェードイン,アウトのための幕
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
