#include "PauseScene.h"
#include <DxLib.h>
#include "../Peripheral.h"
#include "SceneManager.h"
#include "TitleScene.h"


void PauseScene::FadeinUpdate(const Peripheral & p)
{
	_pal = 255;
	updater = &PauseScene::WaitUpdate;
}

void PauseScene::FadeoutUpdate(const Peripheral & p)
{
	SceneManager::Instance().PopScene();
}

void PauseScene::WaitUpdate(const Peripheral & p)
{
	if (p.IsTrigger(0, "PAUSE"))
	{
		updater = &PauseScene::FadeoutUpdate;
	}
}

PauseScene::PauseScene()
{
	updater = &PauseScene::FadeinUpdate;
}


PauseScene::~PauseScene()
{
}

void PauseScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void PauseScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);
	
	DxLib::DrawString(100, 100, "�|�[�Y��", 0x0000ff);

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);

}
