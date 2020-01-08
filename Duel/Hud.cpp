#include "Hud.h"
#include <DxLib.h>
#include <string>



Hud::Hud()
{
	_roundCount = 1;
	_turnCount = 1;
}

Hud::~Hud()
{
}

void Hud::DrawRoundAndTurn()const
{
	std::string roundStr = "���E���h";
	std::string turnStr = "�^�[��";
	roundStr += std::to_string(_roundCount);
	turnStr += std::to_string(_turnCount);
	DxLib::DrawString(600, 0, roundStr.c_str(), 0x00ff00);
	DxLib::DrawString(600, 20, turnStr.c_str(), 0x00ff00);
}

void Hud::DrawHp(const int& rightHp, const int& leftHp)const
{
	DxLib::DrawBox((300 - rightHp), 0, 500, 50, 0x00ff00, true);
	DxLib::DrawFormatString(30, 10, 0xff0000, "HP:%d", rightHp);

	DxLib::DrawBox(900, 0, 1400 - (300 - leftHp), 50, 0x00ff00, true);
	DxLib::DrawFormatString(920, 10, 0xff0000, "HP:%d", leftHp);
}

void Hud::DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData) const
{
	for (int i = 0; i < static_cast<int>(Skill::MAX); ++i)
	{
		if (rPlayerData.skillCount[i] > 0)
		{
			if (rPlayerData.decideFlag)
			{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			}
			DxLib::DrawString(50, 500 + (i * 30), rPlayerData.skillName[i].c_str(), 0x00ff00);
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		if (lPlayerData.skillCount[i] > 0)
		{
			if (lPlayerData.decideFlag)
			{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			}
			DxLib::DrawString(800, 500 + (i * 30), lPlayerData.skillName[i].c_str(), 0x00ff00);
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
	}
}

bool Hud::AdvanceTheTurn()
{
	if (_turnCount == 3)
	{
		++_roundCount;
		_turnCount = 1;

		return true;
	}
	else
	{
		++_turnCount;
	}

	return false;
}

void Hud::Draw(const PlayerData& rPlayerData, const PlayerData& lPlayerData)
{
	DrawRoundAndTurn();
	DrawHp(rPlayerData.hp, lPlayerData.hp);
	DrawPlayerSkill(rPlayerData, lPlayerData);
}