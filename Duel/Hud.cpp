#include "Hud.h"
#include <DxLib.h>
#include <string>



Hud::Hud()
{
	_roundCount = 1;
	_turnCount = 1;
	_maxHpLenght = Vector2<int>(500, 50);
}

Hud::~Hud()
{
}

void Hud::DrawRoundAndTurn()const
{
	std::string roundStr = "ラウンド";
	std::string turnStr = "ターン";
	roundStr += std::to_string(_roundCount);
	turnStr += std::to_string(_turnCount);
	DxLib::DrawString(600, 0, roundStr.c_str(), 0x00ff00);
	DxLib::DrawString(600, 20, turnStr.c_str(), 0x00ff00);
}

void Hud::DrawHp(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const
{
	DxLib::DrawBox(500 - (_maxHpLenght.x * (static_cast<float>(rPlayerData.hp) / static_cast<float>(rPlayerData.maxHp))), 0, 500, _maxHpLenght.y, 0x00ff00, true);
	DxLib::DrawFormatString(30, 10, 0xff0000, "HP:%d", rPlayerData.hp);

	DxLib::DrawBox(900, 0, 900 + (_maxHpLenght.x * (static_cast<float>(lPlayerData.hp) / static_cast<float>(lPlayerData.maxHp))), _maxHpLenght.y, 0x00ff00, true);
	DxLib::DrawFormatString(920, 10, 0xff0000, "HP:%d", lPlayerData.hp);
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
			DxLib::DrawString(50, 600 + (i * 30), rPlayerData.skillName[i].c_str(), 0x00ff00);
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		if (lPlayerData.skillCount[i] > 0)
		{
			if (lPlayerData.decideFlag)
			{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			}
			DxLib::DrawString(800, 600 + (i * 30), lPlayerData.skillName[i].c_str(), 0x00ff00);
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
	DrawHp(rPlayerData, lPlayerData);
	DrawPlayerSkill(rPlayerData, lPlayerData);
}
