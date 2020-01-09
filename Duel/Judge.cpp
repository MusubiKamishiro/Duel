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
		DxLib::DrawString(_trimString->GetStringCenterPosx("��������"), 350, "��������", 0xff0000);
	}
	else if (_result == Result::PLAYER1WIN)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("player1�̏���"), 350, "player1�̏���", 0xff0000);
	}
	else if (_result == Result::PLAYER2WIN)
	{
		DxLib::DrawString(_trimString->GetStringCenterPosx("player2�̏���"), 350, "player2�̏���", 0xff0000);
	}
}

Result Judge::GetResult() const
{
	return _result;
}
