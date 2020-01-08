#include <DxLib.h>
#include "SelectScene.h"
#include "GamePlayingScene.h"
#include "SceneManager.h"
#include "../Peripheral.h"

void SelectScene::FadeinUpdate(const Peripheral& p)
{
	if (_pal >= 255)
	{
		_pal = 255;
		updater = &SelectScene::WaitUpdate;
	}
	else
	{
		_pal += 20;
	}
}

void SelectScene::FadeoutUpdate(const Peripheral& p)
{
	if (_pal <= 0)
	{
		_initStatus[0].hp = 1000;
		_initStatus[0].power[0] = 250;
		_initStatus[0].power[1] = 200;
		_initStatus[0].power[2] = 300;
		_initStatus[0].skillName[0] = "腹パン";
		_initStatus[0].skillName[1] = "喉切";
		_initStatus[0].skillName[2] = "ビンタ";
		_initStatus[1].hp = 1200;
		_initStatus[1].power[0] = 200;
		_initStatus[1].power[1] = 1000;
		_initStatus[1].power[2] = 250;
		_initStatus[1].skillName[0] = "ふくろだたき";
		_initStatus[1].skillName[1] = "ハサミギロチン";
		_initStatus[1].skillName[2] = "はっけい";
		

		SceneManager::Instance().ChangeScene(std::make_unique <GamePlayingScene>(_initStatus));
	}
	else
	{
		_pal -= 20;
	}
}

void SelectScene::WaitUpdate(const Peripheral& p)
{
	if (p.IsTrigger(0, "DECIDE"))
	{
		_pal = 255;
		updater = &SelectScene::FadeoutUpdate;
	}
}

SelectScene::SelectScene() : _charID(10), _boxSize(150, 150)
{
	_pal = 0;

	updater = &SelectScene::FadeinUpdate;
}

SelectScene::~SelectScene()
{
}

void SelectScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void SelectScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);

	DxLib::DrawString(0, 0, "セレクト", 0x00ff00);
	DxLib::DrawExtendString(_scrSize.x / 3, _scrSize.y / 10, 2.5, 2.5, "キャラクターを選んでね！", 0xffffff);

	for (int i = 0; i < _charID; ++i)
	{
		DxLib::DrawBox(_scrSize.x / 4 + _boxSize.x * (i % (_charID / 2)), _scrSize.y / 2 + _boxSize.y * (i / (_charID / 2)),
					   _scrSize.x / 4 + _boxSize.x * (i % (_charID / 2) + 1), _scrSize.y / 2 + _boxSize.y * (i / (_charID / 2) + 1),
					    0xff0000, false);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
