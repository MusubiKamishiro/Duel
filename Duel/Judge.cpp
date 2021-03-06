#include "Judge.h"
#include <DxLib.h>
#include "TrimString.h"

Judge::Judge()
{
	_result = Result::MAX;

	_trimString = (std::make_unique<TrimString>());
}

Judge::~Judge()
{
}

void Judge::JudgeResult(const int& rSkill, const int& lSkill)
{
	_result = static_cast<Result>((lSkill - rSkill + 3) % 3);
}

void Judge::Draw()
{
	if (_result == Result::DRAW)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("引き分け"), 350, "引き分け", 0xff0000);
	}
	else if (_result == Result::PLAYER1WIN)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("左の勝ち"), 350, "左の勝ち", 0xff0000);
	}
	else if (_result == Result::PLAYER2WIN)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("右の勝ち"), 350, "右の勝ち", 0xff0000);
	}
}

Result Judge::GetResult() const
{
	return _result;
}
