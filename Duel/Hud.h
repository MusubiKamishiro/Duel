#pragma once
#include <array>
#include "Player.h"
#include "Geometry.h"

class Hud
{
private:
	// ���E���h�ƃ^�[���̕`��
	void DrawRoundAndTurn()const;
	int _roundCount;
	int _turnCount;

	// HP�̕`��
	void DrawHp(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;
	Vector2<int> _maxHpLenght;

	// �v���C���[�̋Z�̕`��
	void DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;

	// �����̕��������ʂ̒����ɑ�������W��Ԃ�
	int GetStringCenterPosx(const std::string& name)const;
	
	// �Q�[����ʂ̃T�C�Y
	Vector2<int> ssize;

public:
	Hud();
	~Hud();

	// �^�[����i�߂�ۂɌĂяo��
	//@return ���E���h���i�ލۂ�true���Ԃ��Ă���
	bool AdvanceTheTurn();

	// Hud�̕`��S�Ă������Ă���
	void Draw(const PlayerData& rPlayerData, const PlayerData& lPlayerData);
};

