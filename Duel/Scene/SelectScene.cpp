#include "SelectScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "../Game.h"
#include "SceneManager.h"
#include "GamePlayingScene.h"
#include "../Menu/SelectMenu.h"
#include "../Character/CharacterObject.h"
#include "../Score.h"
#include "../Sound.h"


void SelectScene::FadeinUpdate(const Peripheral & p)
{
	if (pal >= 255)
	{
		pal = 255;
		updater = &SelectScene::WaitUpdate;
	}
	else
	{
		pal += 20;
	}
}

void SelectScene::FadeoutUpdate(const Peripheral & p)
{
	if (pal <= 0)
	{
		Sound::Instance().DeleteBGM();
		Score::Instance().InitScore();
		SceneManager::Instance().ChangeScene(std::make_unique <GamePlayingScene>(1, difficult));
	}
	else
	{
		pal -= 20;
	}
}

void SelectScene::WaitUpdate(const Peripheral & p)
{
	//if (smenu->Update(p, difficult))
	if (p.IsTrigger(key.GetNowKey(ATTACK)))
	{
		pal = 255;
		updater = &SelectScene::FadeoutUpdate;
	}
}

SelectScene::SelectScene()
{
	difficult = 1;

	pal = 0;
	img = DxLib::LoadGraph("img/bg4.png");
	helpImg = DxLib::LoadGraph("img/description.png");
	updater = &SelectScene::FadeinUpdate;

	smenu.reset(new SelectMenu());
}


SelectScene::~SelectScene()
{
}

void SelectScene::Update(const Peripheral& p)
{
	++time;
	(this->*updater)(p);
}

void SelectScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);
	//DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, img, true);
	//DxLib::DrawString(50, 50, "SelectScene", 0x000000);

	//smenu->Draw();
	DxLib::DrawExtendGraph(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, helpImg, true);
	if (time / 60 % 2 == 0)
	{
		DxLib::DrawString(550, 400, "Attackボタンで", 0x000000);
		DxLib::DrawString(550, 430, "ゲームスタート!!!", 0x000000);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(pal - 255));
	DxLib::DrawBox(0, 0, Game::Instance().GetScreenSize().x, Game::Instance().GetScreenSize().y, 0x000000, true);

}
