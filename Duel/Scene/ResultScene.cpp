#include <DxLib.h>
#include "ResultScene.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "../Peripheral.h"

#include "../Game.h"
#include "../Loader/FileSystem.h"
#include "../Loader/ImageLoader.h"
#include "../Loader/SoundLoader.h"
#include "../TrimString.h"


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
		DxLib::StopSoundMem(_bgm);
		SceneManager::Instance().ChangeScene(std::make_unique <TitleScene>());
	}
	else
	{
		_pal -= 20;
	}
}

void ResultScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "DECIDE"))
	{
		_pal = 255;
		updater = &ResultScene::FadeoutUpdate;
	}
}

ResultScene::ResultScene(const int& rpImg, const int& lpImg, const Result& result)
{
	_center = Vector2<int>(_scrSize.x / 2, _scrSize.y / 4 - 20);
	_pal = 0;
	_bgm = Game::Instance().GetFileSystem()->Load("sound/bgm/result.mp3");
	_rpImg = rpImg;
	_lpImg = lpImg;
	_frameImg = Game::Instance().GetFileSystem()->Load("img/frame2.png");
	_result = result;

	_trimString = std::make_unique<TrimString>();

	updater = &ResultScene::FadeinUpdate;
}


ResultScene::~ResultScene()
{
}

void ResultScene::Update(const Peripheral& p)
{
	if (!DxLib::CheckSoundMem(_bgm))
	{
		DxLib::PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP);
	}

	(this->*updater)(p);
}

void ResultScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0xffffff, true);
	_trimString->ChangeFontSize(100);

	if (_result == Result::DRAW)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("à¯Ç´ï™ÇØ"), 20, "à¯Ç´ï™ÇØ", 0xff0000);

		DxLib::DrawRotaGraph(_center.x / 2 * 3 + 75, _center.y * 3 + 150, 0.25, DX_PI_F / 2, _lpImg, true);
		DxLib::DrawRotaGraph(_center.x / 2 * 3 + 75, _center.y * 3 + 150, 0.23, DX_PI_F / 2, _frameImg, true);

		DxLib::DrawRotaGraph(_center.x / 2 - 75, _center.y * 3 + 150, 0.25, DX_PI_F / 2 * 3, _rpImg, true);
		DxLib::DrawRotaGraph(_center.x / 2 - 75, _center.y * 3 + 150, 0.23, DX_PI_F / 2 * 3, _frameImg, true);
	}
	else if (_result == Result::PLAYER1WIN)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("ç∂ÇÃèüÇø"), 20, "ç∂ÇÃèüÇø", 0xff0000);
		
		DxLib::DrawExtendGraph(_center.x - 450 / 2, _center.y - 30, _center.x + 450 / 2, _center.y + 570, _rpImg, true);
		DxLib::DrawExtendGraph(_center.x - 500 / 2, _center.y - 50, _center.x + 500 / 2, _center.y + 590, _frameImg, true);

		DxLib::DrawRotaGraph(_center.x / 2 * 3 + 75, _center.y * 3 + 150, 0.25, DX_PI_F / 2, _lpImg, true);
		DxLib::DrawRotaGraph(_center.x / 2 * 3 + 75, _center.y * 3 + 150, 0.23, DX_PI_F / 2, _frameImg, true);
	}
	else if (_result == Result::PLAYER2WIN)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("âEÇÃèüÇø"), 20, "âEÇÃèüÇø", 0xff0000);

		DxLib::DrawExtendGraph(_center.x - 450 / 2, _center.y - 30, _center.x + 450 / 2, _center.y + 570, _lpImg, true);
		DxLib::DrawExtendGraph(_center.x - 500 / 2, _center.y - 50, _center.x + 500 / 2, _center.y + 590, _frameImg, true);

		DxLib::DrawRotaGraph(_center.x / 2 - 75, _center.y * 3 + 150, 0.25, DX_PI_F / 2 * 3, _rpImg, true);
		DxLib::DrawRotaGraph(_center.x / 2 - 75, _center.y * 3 + 150, 0.23, DX_PI_F / 2 * 3, _frameImg, true);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
