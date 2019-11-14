#pragma once
#include "Scene.h"
#include "../KeyConfig.h"

class SelectMenu;

class SelectScene : public Scene
{
private:
	std::shared_ptr<SelectMenu> smenu;

	int img;
	int time = 0;
	int helpImg;
	int difficult;
	void (SelectScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	KeyConfig& key = KeyConfig::Instance();

public:
	SelectScene();
	~SelectScene();

	void Update(const Peripheral& p);
	void Draw();
};

