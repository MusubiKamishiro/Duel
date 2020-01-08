#include "Hud.h"
#include <DxLib.h>
#include <string>
#include "Game.h"


Hud::Hud()
{
	_roundCount = 1;
	_turnCount = 1;
	_maxHpLenght = Vector2<int>(550, 50);

	ssize = Game::Instance().GetScreenSize();
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
	DxLib::DrawString(GetStringCenterPosx(roundStr.c_str()), 0, roundStr.c_str(), 0x00ff00);
	DxLib::DrawString(GetStringCenterPosx(turnStr.c_str()), 20, turnStr.c_str(), 0x00ff00);
}

void Hud::DrawHp(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const
{
	int center = ssize.x / 2;
	int hurfHudLenght = 100;

	DxLib::DrawBox((center - hurfHudLenght) - (_maxHpLenght.x * (static_cast<float>(rPlayerData.hp) / static_cast<float>(rPlayerData.maxHp))), 0, (center - hurfHudLenght), _maxHpLenght.y, 0x00ff00, true);
	DxLib::DrawFormatString(30, 10, 0xff0000, "HP:%d", rPlayerData.hp);

	DxLib::DrawBox((center + hurfHudLenght), 0, (center + hurfHudLenght) + (_maxHpLenght.x * (static_cast<float>(lPlayerData.hp) / static_cast<float>(lPlayerData.maxHp))), _maxHpLenght.y, 0x00ff00, true);
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

int Hud::GetStringCenterPosx(const std::string& name)const
{
	return (ssize.x / 2 - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())) / 2);
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

	DxLib::DrawLine(ssize.x / 2, 0, ssize.x / 2, ssize.y, 0x0000ff);
}
