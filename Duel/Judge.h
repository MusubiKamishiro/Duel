#pragma once
#include <memory>
#include <string>

class TrimString;

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

	std::unique_ptr<TrimString> _trimString;

public:
	Judge();
	~Judge();

	void JudgeResult(const int& rSkill, const int& lSkill);

	void Draw();

	Result GetResult()const;
};
