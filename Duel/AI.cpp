#include "AI.h"
#include <array>
#include <random>
#include "Judge.h"
#include "Hud.h"


AI::AI()
{
	_skill = Skill::ROCK;
	_judge.reset(new Judge());
	_scoreMax = INT_MIN;
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

				if (((myData.hp - enemyData.power[j]) <= 0) && ((enemyData.hp - myData.power[i]) >= 0))
				{
					score -= enemyData.power[j];
				}
			}
			else if (res == Result::PLAYER1WIN)
			{
				// ������������
				score += myData.power[i];
			}
			else if (res == Result::PLAYER2WIN)
			{
				// ���肪������
				score -= enemyData.power[j];

				if ((myData.hp - enemyData.power[j]) <= 0)
				{
					score -= enemyData.power[j];
				}
			}

			// ���ӑ��������g�p�̏ꍇ�̍l�@
			if ((myData.goodSkill == i) && (myData.skillCount[i] == 2))
			{
				score += myData.power[i] / 2;
			}
			if ((enemyData.goodSkill == j) && (enemyData.skillCount[j] == 2))
			{
				score -= enemyData.power[j] / 2;
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
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	int count = engine() % static_cast<int>(Skill::MAX);
	
	if (Hud::Instance().GetNowTurn() == 3)
	{
		count = 0;
	}

	Skill skill = Skill::MAX;
	int score = 0;
	_scoreMax = INT_MIN;

	SkillThink(myData, enemyData, score, (count+1));
}

Skill AI::GetAISkill() const
{
	return _skill;
}
