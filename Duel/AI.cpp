#include "AI.h"
#include "Judge.h"
#include <array>
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

void AI::ScoreCheck(const int& score, const Skill& skill)
{
	if (_scoreMax < score)
	{
		_scoreMax = score;
		_skill = skill;
	}
}

int AI::SkillThink(PlayerData myData, PlayerData enemyData, int& score, int count)
{
	if (count == 0)
	{
		return 0;
	}

	std::array<int, 3> mySkillCount = myData.skillCount;
	std::array<int, 3> enemySkillCount = enemyData.skillCount;
	
	for (int i = 0; i < static_cast<int>(Skill::MAX); ++i)
	{
		// �o���Ȃ���͍l���Ȃ�
		if (myData.skillCount[i] < 1)
		{
			continue;
		}

		for (int j = 0; j < static_cast<int>(Skill::MAX); ++j)
		{
			// �o���Ȃ���͍l���Ȃ�
			if (enemyData.skillCount[j] < 1)
			{
				continue;
			}

			// ���ʂ��m�F���ďd�݂�����
			_judge->JudgeResult(i, j);
			auto res = _judge->GetResult();

			if (res == Result::DRAW)
			{
				score += myData.power[i] - enemyData.power[j];
			}
			else if (res == Result::PLAYER1WIN)
			{
				// ������������
				score += myData.power[i];
			}
			else if (res == Result::PLAYER2WIN)
			{
				// ���肪������
				score += -enemyData.power[j];
			}

			// ������Ď��s
			--myData.skillCount[i];
			--enemyData.skillCount[j];
			score += SkillThink(myData, enemyData, score, (count - 1));
			ScoreCheck(score, static_cast<Skill>(i));

			// ���������Ăق��̎�����s
			score = 0;
			myData.skillCount = mySkillCount;
			enemyData.skillCount = enemySkillCount;
		}
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

	SkillThink(myData, enemyData, score, 2);
}

Skill AI::GetAISkill() const
{
	return _skill;
}
