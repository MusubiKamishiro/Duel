#include "Judge.h"
#include <DxLib.h>

Judge::Judge()
{
	result = Result::MAX;
}

Judge::~Judge()
{
}

void Judge::JudgeResult(const int& p1hand, const int& p2hand)
{
	result = static_cast<Result>((p2hand - p1hand + 3) % 3);
}

void Judge::Draw()
{
	if (result == Result::DRAW)
	{
		DxLib::DrawString(500, 0, "ˆø‚«•ª‚¯", 0x00ff00);
	}
	else if (result == Result::PLAYER1WIN)
	{
		DxLib::DrawString(500, 0, "player1‚ÌŸ‚¿", 0x00ff00);
	}
	else if (result == Result::PLAYER2WIN)
	{
		DxLib::DrawString(500, 0, "player2‚ÌŸ‚¿", 0x00ff00);
	}
}
