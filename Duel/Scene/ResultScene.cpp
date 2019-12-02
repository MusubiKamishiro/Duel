#include "ResultScene.h"
#include <DxLib.h>
#include <string>
#include "../Peripheral.h"
#include "SceneManager.h"
#include "TitleScene.h"


void ResultScene::FadeinUpdate(const Peripheral & p)
{
	if (_pal >= 255)
	{
		_pal = 255;
		updater = &ResultScene::WaitUpdate;
	}
	else
	{
		_pal +=20;
	}
}

void ResultScene::FadeoutUpdate(const Peripheral & p)
{
	if (_pal <= 0)
	{
		SceneManager::Instance().ChangeScene(std::make_unique <TitleScene>());
	}
	else
	{
		_pal -= 20;
	}
}

void ResultScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "decide"))
	{
		_pal = 255;
		updater = &ResultScene::FadeoutUpdate;
	}
}

ResultScene::ResultScene()
{
	_pal = 0;
	updater = &ResultScene::FadeinUpdate;
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void ResultScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);

	DxLib::DrawString(0, 0, "ƒŠƒUƒ‹ƒg", 0x00ff00);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
