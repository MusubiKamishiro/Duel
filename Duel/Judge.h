#pragma once

// ‚¶‚á‚ñ‚¯‚ñ‚ÌŒ‹‰Ê
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

	void JudgeResult(const int& p1hand, const int& p2hand);

	void Draw();

	Result GetResult()const;
};
