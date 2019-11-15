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
	Result result;

public:
	Judge();
	~Judge();

	void JudgeResult(const int& p1hand, const int& p2hand);

	void Draw();
};
