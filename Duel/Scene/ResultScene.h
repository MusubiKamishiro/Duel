#pragma once
#include "Scene.h"
#include <memory>
#include "../Judge.h"
#include "../Geometry.h"

class TrimString;

class ResultScene : public Scene
{
private:
	void (ResultScene::*updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	Vector2<int> _center;

	int _bgm;

	int _rpImg;
	int _lpImg;
	int _frameImg;

	Result _result;
	std::unique_ptr<TrimString> _trimString;

public:
	ResultScene(const int& rpImg, const int& lpImg, const Result& result);
	~ResultScene();

	void Update(const Peripheral& p);
	void Draw();
};

