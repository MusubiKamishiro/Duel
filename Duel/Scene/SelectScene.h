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

	// �L�����N�^�[��ID�p(enum class�ō���Ă���������)
	const int _charID;

	/// �L�����N�^�[�g�̃f�o�b�O�`��p
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

