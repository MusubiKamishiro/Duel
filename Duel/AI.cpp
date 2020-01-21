#include "AI.h"
#include "Judge.h"
//#include <random>


AI::AI()
{
	_skill = Skill::ROCK;
	_judge.reset(new Judge());
	_scoreMax = 0;
}

AI::~AI()
{
}

void AI::Check(const int& score, const Skill& skill)
{
	if (_scoreMax < score)
	{
		_scoreMax = score;
		_skill = skill;
	}
}

void AI::Update(const PlayerData& myData, const PlayerData& enemyData)
{
	/*std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	_skill = static_cast<Skill>(engine() % static_cast<int>(Skill::MAX));*/

	Skill skill = Skill::MAX;
	int score = 0;
	_scoreMax = 0;

	for (int i = 0; i < static_cast<int>(Skill::MAX); ++i)
	{
		// 出せない手は考えない
		if (myData.skillCount[i] < 1)
		{
			continue;
		}

		for (int j = 0; j < static_cast<int>(Skill::MAX); ++j)
		{
			// 出さない手は考えない
			if (enemyData.skillCount[j] < 1)
			{
				continue;
			}

			// 結果を確認して重みをつける
			_judge->JudgeResult(i, j);
			auto res = _judge->GetResult();

			if (res == Result::DRAW)
			{
				score = myData.power[i] - enemyData.power[j];
			}
			else if (res == Result::PLAYER1WIN)
			{
				// 自分が勝った
				score = myData.power[i];
				skill = static_cast<Skill>(i);
			}
			else if (res == Result::PLAYER2WIN)
			{
				// 相手が勝った
				score = -enemyData.power[j];
			}
			Check(score, static_cast<Skill>(i));
		}
	}
}

Skill AI::GetAISkill() const
{
	return _skill;
}
