#pragma once
#include <string>

// ����񂯂�̌���
enum class Result
{
	DRAW,
	PLAYER1WIN,
	PLAYER2WIN,
	MAX
};


class Judge
{
private:
	Result _result;

public:
	Judge();
	~Judge();

	void JudgeResult(const int& rSkill, const int& lSkill);

	void Draw();

	Result GetResult()const;
};
