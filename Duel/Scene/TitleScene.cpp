#include "TitleScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "SceneManager.h"
#include "GamePlayingScene.h"


void TitleScene::FadeinUpdate(const Peripheral & p)
{
	if (_pal >= 255)
	{
		_pal = 255;
		updater = &TitleScene::WaitUpdate;
	}
	else
	{
		_pal += 20;
	}
}

void TitleScene::FadeoutUpdate(const Peripheral & p)
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

void TitleScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "decide"))
	{
		updater = &TitleScene::FadeoutUpdate;
	}
}

TitleScene::TitleScene()
{
	_pal = 0;

	updater = &TitleScene::FadeinUpdate;
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void TitleScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);

	DxLib::DrawString(0, 0, "ƒ^ƒCƒgƒ‹", 0x00ff00);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
