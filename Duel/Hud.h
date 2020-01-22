#pragma once
#include <memory>
#include <array>
#include "Player.h"
#include "Geometry.h"

class TrimString;

class Hud
{
private:
	Hud();							// �����֎~
	Hud(const Hud&);				// �R�s�[�֎~
	void operator=(const Hud&);	// ����֎~

	// ���E���h�ƃ^�[���̕`��
	void DrawRoundAndTurn()const;
	int _roundCount;
	int _turnCount;

	// HP�̕`��
	void DrawHp(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;
	Vector2<int> _maxHpLenght;

	// �����\�̕`��
	void DrawType();
	int _typeImg;

	// �v���C���[�̋Z�̕`��
	void DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;

	// �Q�[����ʂ̃T�C�Y
	Vector2<int> _ssize;
	// ��ʂ̒���
	Vector2<int> _center;

	// �Z�̐F(�̂��ɉ摜�ň�������)
	std::array<int, 3> _typeColor;

	// ���Hud�̏c��
	int _topHudHeight;
	// ���Hud�̉���
	int _topHudEdge;

	std::unique_ptr<TrimString> _trimString;

public:
	static Hud& Instance()
	{
		static Hud instance;
		return instance;
	}
	~Hud();

	void Init();

	// �^�[����i�߂�ۂɌĂяo��
	//@return ���E���h���i�ލۂ�true���Ԃ��Ă���
	bool AdvanceTheTurn();

	// Hud�̕`��S�Ă������Ă���
	void Draw(const PlayerData& rPlayerData, const PlayerData& lPlayerData);

	const int& GetNowTurn()const;
};

