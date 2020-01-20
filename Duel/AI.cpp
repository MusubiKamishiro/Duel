#include "AI.h"
#include <random>

AI::AI()
{
	skill = Skill::ROCK;
}

AI::~AI()
{
}

void AI::Update(const PlayerData& myData, const PlayerData& enemyData)
{
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	skill = static_cast<Skill>(engine() % static_cast<int>(Skill::MAX));
}

Skill AI::GetAISkill() const
{
	return skill;
}
