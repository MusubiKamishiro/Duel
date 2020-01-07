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
		DxLib::DrawString(500, 0, "引き分け", 0x00ff00);
	}
	else if (_result == Result::PLAYER1WIN)
	{
		DxLib::DrawString(500, 0, "player1の勝ち", 0x00ff00);
	}
	else if (_result == Result::PLAYER2WIN)
	{
		DxLib::DrawString(500, 0, "player2の勝ち", 0x00ff00);
	}
}

Result Judge::GetResult() const
{
	return _result;
}
