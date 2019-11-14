#pragma once
#include <memory>
#include "Scene/Scene.h"
#include "Geometry.h"


// �Q�[���S�̂𐧌䂷��N���X
class Game
{
private:
	Game();							// �����֎~
	Game(const Game&);				// �R�s�[�֎~
	void operator=(const Game&);	// ����֎~

	const Vector2<int> ScreenSize;

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

	// ���Ƀ��[�v����
	// ������ĂԂƃQ�[�����n�܂�
	void Run();

	// ���C�u�����̌㏈���Ȃ�
	void Terminate();

	const Vector2<int>& GetScreenSize()const;
};

