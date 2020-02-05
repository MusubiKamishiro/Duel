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

	// ２ポリゴン分の頂点のデータをセットアップ
	Vertex[0].pos = VGet(0.0f, _scrSize.y, 0.0f);
	Vertex[0].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[0].dif = GetColorU8(255, 0, 255, 255);
	Vertex[0].spc = GetColorU8(0, 0, 0, 0);
	Vertex[0].u = 0.0f;
	Vertex[0].v = 0.0f;
	Vertex[0].su = 0.0f;
	Vertex[0].sv = 0.0f;

	Vertex[1].pos = VGet(_scrSize.x, _scrSize.y, 0.0f);
	Vertex[1].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[1].dif = GetColorU8(0, 0, 255, 255);
	Vertex[1].spc = GetColorU8(0, 0, 0, 0);
	Vertex[1].u = 1.0f;
	Vertex[1].v = 0.0f;
	Vertex[1].su = 0.0f;
	Vertex[1].sv = 0.0f;

	Vertex[2].pos = VGet(0.0f, 0.0f, 0.0f);
	Vertex[2].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[2].dif = GetColorU8(255, 255, 0, 255);
	Vertex[2].spc = GetColorU8(0, 0, 0, 0);
	Vertex[2].u = 0.0f;
	Vertex[2].v = 1.0f;
	Vertex[2].su = 0.0f;
	Vertex[2].sv = 0.0f;


	Vertex[3].pos = VGet(0.0f, 0.0f, 0.0f);
	Vertex[3].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[3].dif = GetColorU8(255, 255, 0, 255);
	Vertex[3].spc = GetColorU8(0, 0, 0, 0);
	Vertex[3].u = 0.0f;
	Vertex[3].v = 1.0f;
	Vertex[3].su = 0.0f;
	Vertex[3].sv = 0.0f;

	Vertex[4].pos = VGet(_scrSize.x, _scrSize.y, 0.0f);
	Vertex[4].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[4].dif = GetColorU8(0, 0, 255, 255);
	Vertex[4].spc = GetColorU8(0, 0, 0, 0);
	Vertex[4].u = 1.0f;
	Vertex[4].v = 0.0f;
	Vertex[4].su = 0.0f;
	Vertex[4].sv = 0.0f;

	Vertex[5].pos = VGet(_scrSize.x, 0.0f, 0.0f);
	Vertex[5].norm = VGet(0.0f, 0.0f, -1.0f);
	Vertex[5].dif = GetColorU8(255, 0, 0, 255);
	Vertex[5].spc = GetColorU8(0, 0, 0, 0);
	Vertex[5].u = 1.0f;
	Vertex[5].v = 1.0f;
	Vertex[5].su = 0.0f;
	Vertex[5].sv = 0.0f;

	// 頂点シェーダーを読み込む
	vshandle = LoadVertexShader("shader/VertShader.vso");
	// ピクセルシェーダーを読み込む
	pshandle = LoadPixelShader("shader/PixShader.pso");
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
		if ((_players[0]->GetPlayerData().hp <= 0) && (_players[1]->GetPlayerData().hp <= 0))
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
			if (_players[1]->GetAiFlag() == false)
			{
				DxLib::StartJoypadVibration(DX_INPUT_PAD2, 1000, 1000);
			}
			
		}
		else if(_judge->GetResult() == Result::PLAYER1WIN)
		{
			_players[1]->Damage(_players[0]->GetPower());
			if (_players[1]->GetAiFlag() == false)
			{
				DxLib::StartJoypadVibration(DX_INPUT_PAD2, 1000, 1000);
			}
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

	spos.y += 0.001;
	// 座標値を頂点シェーダー float4型定数０番にセット
	f4.x = 0.0f;
	f4.y = 0.0f;
	f4.z = 0.0f;
	f4.w = 0.0f;
	DxLib::SetVSConstF(0, f4);

	// 色の値をピクセルシェーダー float4型定数０番にセット
	f4.x = 0;
	f4.y = 1;
	f4.z = 0;
	f4.w = 1.0f;
	DxLib::SetPSConstF(0, f4);

	f4.x = spos.x;
	f4.y = spos.y;
	f4.z = 0.0f;
	f4.w = 1.0f;
	DxLib::SetPSConstF(1, f4);

	// 使用する頂点シェーダーのセット
	DxLib::SetUseVertexShader(vshandle);

	// 使用するピクセルシェーダーをセット
	DxLib::SetUsePixelShader(pshandle);

	// 使用するテクスチャを０番にセット
	DxLib::SetUseTextureToShader(0, -1);

	// シェーダーを使用した２ポリゴンの描画
	DxLib::DrawPolygon3DToShader(Vertex, 2);


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
