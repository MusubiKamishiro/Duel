#include <DxLib.h>
#include "TitleScene.h"
#include "SelectScene.h"
#include "SceneManager.h"
#include "../Peripheral.h"
#include "../Game.h"

#include "../Loader/FileSystem.h"
#include "../Loader/ImageLoader.h"
#include "../Loader/SoundLoader.h"
#include "../TrimString.h"

void TitleScene::FadeinUpdate(const Peripheral & p)
{
	if (_pal >= 255)
	{
		_pal = 255;
		_updater = &TitleScene::StartUpdate;
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
		DxLib::StopSoundMem(_bgm);
		SceneManager::Instance().ChangeScene(std::make_unique <SelectScene>(_selectCount));
	}
	else
	{
		_pal -= 20;
	}
}

void TitleScene::WaitUpdate(const Peripheral & p)
{
	
}

void TitleScene::StartUpdate(const Peripheral& p)
{
	if (p.IsTrigger(0, "ANY"))
	{
		DxLib::PlaySoundMem(_decideSE, DX_PLAYTYPE_BACK);
		_updater = &TitleScene::SelectPlayUpdate;
		_drawer = &TitleScene::SelectPlayDraw;
		_sceneTime = 0;
	}
}

void TitleScene::SelectPlayUpdate(const Peripheral& p)
{
	if (p.IsTrigger(0, "UP"))
	{
		DxLib::PlaySoundMem(_selSE, DX_PLAYTYPE_BACK);
		--_selectCount;
		_sceneTime = 0;
	}
	if (p.IsTrigger(0, "DOWN"))
	{
		DxLib::PlaySoundMem(_selSE, DX_PLAYTYPE_BACK);
		++_selectCount;
		_sceneTime = 0;
	}
	if (p.IsTrigger(0, "DECIDE"))
	{
		DxLib::PlaySoundMem(_decideSE, DX_PLAYTYPE_BACK);
		_updater = &TitleScene::FadeoutUpdate;
	}

	if (_selectCount < 0)
	{
		_selectCount = 0;
	}
	else if (_selectCount > 1)
	{
		_selectCount = 1;
	}
}

void TitleScene::StartDraw()
{
	if ((_sceneTime / 30 % 2) == 0)
	{
		_trimString->ChangeFontSize(50);
		DxLib::DrawString(_trimString->GetStringCenterPosx("press any key"), _trimString->GetFontSize() + 500, "press any key", 0x000000);
	}
}

void TitleScene::SelectPlayDraw()
{
	_trimString->ChangeFontSize(50);
	if ((_sceneTime / 30 % 3) != 2)
	{
		DxLib::DrawString(500, 500 + _selectCount * 60, "->", 0x000000);
	}
	
	DxLib::DrawString(_trimString->GetStringCenterPosx(" 1P vs CPU"), 500, " 1P vs CPU", 0x000000);
	DxLib::DrawString(_trimString->GetStringCenterPosx(" 1P vs 2P "), _trimString->GetFontSize() + 500 + 10, " 1P vs 2P ", 0x000000);
}

TitleScene::TitleScene()
{
	_selectCount = 0;
	_pal = 0;
	_bgm = Game::Instance().GetFileSystem()->Load("sound/bgm/title.mp3");
	_decideSE = Game::Instance().GetFileSystem()->Load("sound/se/decide.mp3");
	_selSE = Game::Instance().GetFileSystem()->Load("sound/se/cursor.mp3");

	_trimString = std::make_unique<TrimString>();

	_updater = &TitleScene::FadeinUpdate;
	_drawer = &TitleScene::StartDraw;
}


TitleScene::~TitleScene()
{
}

void TitleScene::Update(const Peripheral& p)
{
	if (!DxLib::CheckSoundMem(_bgm))
	{
		DxLib::PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP);
	}

	(this->*_updater)(p);
}

void TitleScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0xffffff, true);

	_trimString->ChangeFontSize(150);
	DxLib::DrawString(_trimString->GetStringCenterPosx("Buttle"), 100, "Buttle", 0x000000);
	DxLib::DrawString(_trimString->GetStringCenterPosx("Fighters"), _trimString->GetFontSize() + 105, "Fighters", 0x000000);

	(this->*_drawer)();

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
