#pragma once
#include <memory>
#include "Scene/Scene.h"
#include "Geometry.h"

class Peripheral;

// �Q�[���S�̂𐧌䂷��N���X
class Game
{
private:
	Game();							// �����֎~
	Game(const Game&);				// �R�s�[�֎~
	void operator=(const Game&);	// ����֎~

	const Vector2<int> ScreenSize;
	std::unique_ptr<Peripheral> peripheral;

public:
	static Game& Instance()
	{
		static Game instance;
		return instance;
	}
	~Game();

	// �������n
	// ��{�f�ނ̃��[�h�Ƃ������������s��
	void Initialize();

	// ���͊֌W�̏�����
	void InitPeripheral();

	// ���Ƀ��[�v����
	// ������ĂԂƃQ�[�����n�܂�
	void Run();

	// ���C�u�����̌㏈���Ȃ�
	void Terminate();

	const Vector2<int>& GetScreenSize()const;
};

