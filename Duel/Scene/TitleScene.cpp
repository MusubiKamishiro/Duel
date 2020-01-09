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
		_updater = &TitleScene::WaitUpdate;
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
		SceneManager::Instance().ChangeScene(std::make_unique <SelectScene>());
	}
	else
	{
		_pal -= 20;
	}
}

void TitleScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "DECIDE"))
	{
		DxLib::PlaySoundMem(_decideSE, DX_PLAYTYPE_BACK);
		_updater = &TitleScene::FadeoutUpdate;
	}
}

TitleScene::TitleScene()
{
	_pal = 0;
	_bgm = Game::Instance().GetFileSystem()->Load("sound/bgm/title.mp3");
	_decideSE = Game::Instance().GetFileSystem()->Load("sound/se/decide.mp3");
	_trimString = std::make_unique<TrimString>();

	_updater = &TitleScene::FadeinUpdate;
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
	DxLib::DrawString(_trimString->GetStringCenterPosx("Buttle"), 200, "Buttle", 0x000000);
	DxLib::DrawString(_trimString->GetStringCenterPosx("Fighters"), _trimString->GetFontSize() + 205, "Fighters", 0x000000);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
