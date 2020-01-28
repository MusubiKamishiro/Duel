#pragma once
#include <memory>
#include "Player.h"

class Judge;

class AI
{
private:
	Skill _skill;
	std::shared_ptr<Judge> _judge;

	void ScoreCheck(const int& score, const Skill& skill);
	int _scoreMax;

	// �ǂ̎���o�������l����
	//@param score...���݂̎�̓_��
	//@param count...���s��
	int SkillThink(PlayerData myData, PlayerData enemyData, int& score, int count);

public:
	AI();
	~AI();

	void Update(const PlayerData& myData, const PlayerData& enemyData);

	// AI�����߂��X�L�����擾����
	Skill GetAISkill()const;
};
