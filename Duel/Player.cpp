#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"


Player::Player(const Vector2<int>& pos, const InitStatus initStatus)
{
	for (int i = 0; i < static_cast<int>(Skill::MAX); ++i)
	{
		_playerData.skillCount[i] = 1;
		_playerData.initSkillCount[i] = 1;
	}
	_playerData.skill = Skill::MAX;
	_playerData.decideFlag = false;
	_pos = pos;
	
	_playerData.maxHp = initStatus.hp;
	_playerData.hp = _playerData.maxHp;
	_playerData.power = initStatus.power;
	_playerData.skillName = initStatus.skillName;
}

Player::~Player()
{
}

void Player::Check(const Skill& hand)
{
	if ((_playerData.skillCount[static_cast<int>(hand)] > 0) && (_playerData.decideFlag == false))
	{
		_playerData.skill = hand;
		_playerData.decideFlag = true;
	}
}

void Player::Update(const int& pno, const Peripheral& p)
{
	if (p.IsTrigger(pno, "ROCK"))
	{
		Check(Skill::ROCK);
	}
	else if (p.IsTrigger(pno, "SCISSORS"))
	{
		Check(Skill::SCISSORS);
	}
	else if (p.IsTrigger(pno, "PAPER"))
	{
		Check(Skill::PAPER);
	}
}

void Player::Draw()
{
	if (_playerData.skill == Skill::ROCK)
	{
		DxLib::DrawString(_pos.x, _pos.y, "グー", 0xff0000);
	}
	else if (_playerData.skill == Skill::SCISSORS)
	{
		DxLib::DrawString(_pos.x, _pos.y, "チョキ", 0xff0000);
	}
	else if (_playerData.skill == Skill::PAPER)
	{
		DxLib::DrawString(_pos.x, _pos.y, "パー", 0xff0000);
	}
}

void Player::Damage(const int& power)
{
	_playerData.hp -= power;
}

const int Player::GetPower() const
{
	return _playerData.power[static_cast<int>(_playerData.skill)];
}

const PlayerData& Player::GetPlayerData() const
{
	return _playerData;
}

void Player::SetHand()
{
	_playerData.decideFlag = false;
	--_playerData.skillCount[static_cast<int>(_playerData.skill)];
	_playerData.skill = Skill::MAX;
}

void Player::ResetCount()
{
	_playerData.skillCount = _playerData.initSkillCount;
}
