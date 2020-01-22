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

	//@param score...現在の手の点数
	//@param count...試行回数
	int SkillThink(PlayerData myData, PlayerData enemyData, int& score, int count);

public:
	AI();
	~AI();

	void Update(const PlayerData& myData, const PlayerData& enemyData);

	Skill GetAISkill()const;
};

