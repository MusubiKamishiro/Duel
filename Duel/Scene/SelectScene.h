#pragma once
#include <memory>
#include <array>
#include "Scene.h"

#include "../Player.h"

class TrimString;

class SelectScene : public Scene
{
private:
	void (SelectScene::* updater)(const Peripheral& p);

	void FadeinUpdate(const Peripheral& p);
	void FadeoutUpdate(const Peripheral& p);
	void WaitUpdate(const Peripheral& p);

	void ChangeCharacter(const Peripheral& p, const int& num);

	// キャラクターのID用(enum classで作ってもいいかも)
	const int _charID;

	/// キャラクター枠のデバッグ描画用
	const Vector2<int> _boxSize;

	// 
	std::array<InitStatus, 2> _initStatus;
	std::unique_ptr<TrimString> _trimString;

public:
	SelectScene();
	~SelectScene();

	void Update(const Peripheral& p);
	void Draw();

	std::array<bool, 2> _isDecide;
};

