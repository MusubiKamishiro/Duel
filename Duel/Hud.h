#pragma once
#include <array>
#include "Player.h"

class Hud
{
private:
	// ���E���h�ƃ^�[���̕`��
	void DrawRoundAndTurn()const;
	int _roundCount;
	int _turnCount;

	void DrawHp(const int& rightHp, const int& leftHp)const;

	// �v���C���[�̋Z�̕`��
	void DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;

public:
	Hud();
	~Hud();

	// �^�[����i�߂�ۂɌĂяo��
	//@return ���E���h���i�ލۂ�true���Ԃ��Ă���
	bool AdvanceTheTurn();

	// Hud�̕`��S�Ă������Ă���
	void Draw(const PlayerData& rPlayerData, const PlayerData& lPlayerData);
};

