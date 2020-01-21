#pragma once
#include <memory>
#include "Player.h"


class Judge;

class AI
{
private:
	Skill _skill;
	std::shared_ptr<Judge> _judge;

	void Check(const int& score, const Skill& skill);
	int _scoreMax;

public:
	AI();
	~AI();

	void Update(const PlayerData& myData, const PlayerData& enemyData);

	Skill GetAISkill()const;
};

