#include "Judge.h"
#include <DxLib.h>

Judge::Judge()
{
	_result = Result::MAX;
}

Judge::~Judge()
{
}

void Judge::JudgeResult(const int& p1hand, const int& p2hand)
{
	_result = static_cast<Result>((p2hand - p1hand + 3) % 3);
}

void Judge::Draw()
{
	if (_result == Result::DRAW)
	{
		DxLib::DrawString(500, 400, "ˆø‚«•ª‚¯", 0x00ff00);
	}
	else if (_result == Result::PLAYER1WIN)
	{
		DxLib::DrawString(500, 400, "player1‚ÌŸ‚¿", 0x00ff00);
	}
	else if (_result == Result::PLAYER2WIN)
	{
		DxLib::DrawString(500, 400, "player2‚ÌŸ‚¿", 0x00ff00);
	}
}

Result Judge::GetResult() const
{
	return _result;
}
