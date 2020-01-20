#pragma once
#include "Player.h"

class AI
{
private:
	Skill skill;

public:
	AI();
	~AI();

	void Update(const PlayerData& myData, const PlayerData& enemyData);

	Skill GetAISkill()const;
};

