#include "Hud.h"
#include <DxLib.h>
#include <string>
#include "Game.h"
#include "TrimString.h"

#include "Loader/FileSystem.h"
#include "Loader/ImageLoader.h"


Hud::Hud()
{
	_roundCount = 1;
	_turnCount = 1;
	_maxHpLenght = Vector2<int>(550, 15);
	_topHudHeight = 75;
	_topHudEdge = 5;

	_ssize = Game::Instance().GetScreenSize();
	_center = Vector2<int>(_ssize.x / 2, _ssize.y / 2);

	_trimString = std::make_unique<TrimString>();

	_typeImg = Game::Instance().GetFileSystem()->Load("img/type.png");
	_frameImg = Game::Instance().GetFileSystem()->Load("img/statusFrame.png");

	_typeColor[0] = Game::Instance().GetFileSystem()->Load("img/ki.png");
	_typeColor[1] = Game::Instance().GetFileSystem()->Load("img/ao.png");
	_typeColor[2] = Game::Instance().GetFileSystem()->Load("img/aka.png");
}

Hud::~Hud()
{
}

void Hud::Init()
{
	_roundCount = 1;
	_turnCount = 1;
}

void Hud::DrawRoundAndTurn()const
{
	DxLib::DrawBox(_center.x - 100, 0, _center.x + 100, _topHudHeight - _topHudEdge, 0x0000ff, true);
	DxLib::DrawBox(_center.x - 100, (_topHudHeight - _topHudEdge) / 2 - 2, _center.x + 100, (_topHudHeight - _topHudEdge) / 2 + 2, 0xffffff, true);

	_trimString->ChangeFontSize(25);
	std::string roundStr = "ラウンド";
	std::string turnStr = "ターン";
	roundStr += std::to_string(_roundCount);
	turnStr += std::to_string(_turnCount);
	DxLib::DrawString(_trimString->GetStringCenterPosx(roundStr.c_str()), 5, roundStr.c_str(), 0x00ff00);
	DxLib::DrawString(_trimString->GetStringCenterPosx(turnStr.c_str()), 40, turnStr.c_str(), 0x00ff00);
}

void Hud::DrawHp(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const
{
	_trimString->ChangeFontSize(35);
	int hurfHudLenght = 100;

	DxLib::DrawBox(0, 0, _ssize.x, _topHudHeight,  0x000000, true);
	DxLib::DrawBox(_topHudEdge, 0, _ssize.x - _topHudEdge, _topHudHeight - _topHudEdge,  0xffffff, true);

	DxLib::DrawBox((_center.x - hurfHudLenght) - (_maxHpLenght.x * (static_cast<float>(rPlayerData.hp) / static_cast<float>(rPlayerData.maxHp))), 10, (_center.x - hurfHudLenght), _maxHpLenght.y + 10, 0x00ff00, true);
	DxLib::DrawFormatString(_trimString->GetStringRightPosx("HP:" + std::to_string(rPlayerData.hp), (_center.x - hurfHudLenght - 10)), _maxHpLenght.y + 10, 0xff0000, "HP:%.0f", rPlayerData.hp);

	DxLib::DrawBox((_center.x + hurfHudLenght), 10, (_center.x + hurfHudLenght) + (_maxHpLenght.x * (static_cast<float>(lPlayerData.hp) / static_cast<float>(lPlayerData.maxHp))), _maxHpLenght.y + 10, 0x00ff00, true);
	DxLib::DrawFormatString((_center.x + hurfHudLenght)+ 10, _maxHpLenght.y + 10, 0xff0000, "HP:%.0f", lPlayerData.hp);


	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
	DxLib::DrawBox((_center.x - hurfHudLenght) - (_maxHpLenght.x * (static_cast<float>(rPlayerData.hp) / static_cast<float>(rPlayerData.maxHp))), 10, (_center.x - hurfHudLenght), _maxHpLenght.y + 10, 0xffffff, true);
	DxLib::DrawBox((_center.x + hurfHudLenght), 10, (_center.x + hurfHudLenght) + (_maxHpLenght.x * (static_cast<float>(lPlayerData.hp) / static_cast<float>(lPlayerData.maxHp))), _maxHpLenght.y + 10, 0xffffff, true);
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}

void Hud::DrawType()
{
	DxLib::DrawGraph(_center.x - 100, _ssize.y - 200, _typeImg, true);
}

void Hud::DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData) const
{
	DxLib::DrawExtendGraph(0, _ssize.y - 200, (_ssize.x / 2 - 100), _ssize.y, _frameImg, true);
	DxLib::DrawExtendGraph(_ssize.x, _ssize.y - 200, (_ssize.x / 2 + 100), _ssize.y, _frameImg, true);

	static int t = 0;
	++t;

	_trimString->ChangeFontSize(40);
	for (int i = 0; i < static_cast<int>(Skill::MAX); ++i)
	{
		int fontSize = _trimString->GetFontSize();

		if (rPlayerData.skillCount[i] > 0)
		{
			if (rPlayerData.decideFlag)
			{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			}
			DxLib::DrawString(_trimString->GetStringRightPosx(rPlayerData.skillName[i].c_str(), _center.x - 180), _ssize.y - 175 + (i * (fontSize + 15)), rPlayerData.skillName[i].c_str(), 0x000000);
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DxLib::DrawExtendGraph(_center.x - 175, _ssize.y - 175 + (i * (fontSize + 15)), _center.x - 135, _ssize.y - 135 + (i * (fontSize + 15)), _typeColor[i], true);
			if (i == rPlayerData.goodSkill)
			{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (std::abs(t % 256 / 2 - 64) * 2));
				DxLib::DrawExtendGraph(_center.x - 185, _ssize.y - 185 + (i * (fontSize + 15)), _center.x - 125, _ssize.y - 125 + (i * (fontSize + 15)), _typeColor[i], true);
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
		}
		if (lPlayerData.skillCount[i] > 0)
		{
			if (lPlayerData.decideFlag)
			{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 64);
			}
			DxLib::DrawString(_center.x + 180, _ssize.y - 175 + (i * (fontSize + 15)), lPlayerData.skillName[i].c_str(), 0x000000);
			DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			DxLib::DrawExtendGraph(_center.x + 135, _ssize.y - 175 + (i * (fontSize + 15)), _center.x + 175, _ssize.y - 135 + (i * (fontSize + 15)), _typeColor[i], true);
			if (i == lPlayerData.goodSkill)
			{
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (std::abs(t % 256 / 2 - 64) * 2));
				DxLib::DrawExtendGraph(_center.x + 125, _ssize.y - 185 + (i * (fontSize + 15)), _center.x + 185, _ssize.y - 125 + (i * (fontSize + 15)), _typeColor[i], true);
				DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
			}
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
	DxLib::DrawBox(0, _ssize.y - 200, _ssize.x, _ssize.y, 0xffffff, true);

	DrawHp(rPlayerData, lPlayerData);
	DrawRoundAndTurn();
	DrawPlayerSkill(rPlayerData, lPlayerData);
	DrawType();
}

const int& Hud::GetNowTurn() const
{
	return _turnCount;
}
