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
		SceneManager::Instance().ChangeScene(std::make_unique <GamePlayingScene>());
	}
	else
	{
		_pal -= 20;
	}
}

void SelectScene::WaitUpdate(const Peripheral& p)
{
	if (p.IsTrigger(0, "decide"))
	{
		_pal = 255;
		updater = &SelectScene::FadeoutUpdate;
	}
}

SelectScene::SelectScene()
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

	DxLib::DrawString(0, 0, "ÉZÉåÉNÉg", 0x00ff00);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
