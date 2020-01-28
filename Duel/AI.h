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

	// どの手を出すかを考える
	//@param score...現在の手の点数
	//@param count...試行回数
	int SkillThink(PlayerData myData, PlayerData enemyData, int& score, int count);

public:
	AI();
	~AI();

	void Update(const PlayerData& myData, const PlayerData& enemyData);

	// AIが決めたスキルを取得する
	Skill GetAISkill()const;
};
