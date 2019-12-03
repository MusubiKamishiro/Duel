#pragma once
#include <array>
#include "Scene.h"

class SelectScene : public Scene
{
private:
	void (SelectScene::* updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	// キャラクターのID用(enum classで作ってもいいかも)
	const int _charID;

	/// キャラクター枠のデバッグ描画用
	const Vector2<int> _boxSize;
public:
	SelectScene();
	~SelectScene();

	void Update(const Peripheral& p);
	void Draw();
};

