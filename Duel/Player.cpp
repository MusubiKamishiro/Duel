#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"


Player::Player(const Vector2<int>& pos)
{
	for (int i = 0; i < static_cast<int>(Hand::MAX); ++i)
	{
		_handCount[i] = 1;
		_initHandCount[i] = 1;
	}
	_hand = Hand::MAX;
	_pos = pos;
	_decideFlag = false;

	_hp = 300;
	_power[0] = 50;
	_power[1] = 20;
	_power[2] = 80;
}

Player::~Player()
{
}

void Player::Check(const Hand& hand)
{
	if ((_handCount[static_cast<int>(hand)] > 0) && (_decideFlag == false))
	{
		_hand = hand;
		--_handCount[static_cast<int>(hand)];
		_decideFlag = true;
	}
}

void Player::Update(const int& pno, const Peripheral& p)
{
	if (p.IsTrigger(pno, "ROCK"))
	{
		Check(Hand::ROCK);
	}
	else if (p.IsTrigger(pno, "SCISSORS"))
	{
		Check(Hand::SCISSORS);
	}
	else if (p.IsTrigger(pno, "PAPER"))
	{
		Check(Hand::PAPER);
	}
}

void Player::Draw()
{
	if (_hand == Hand::ROCK)
	{
		DxLib::DrawString(_pos.x, _pos.y, "グー", 0xff0000);
	}
	else if (_hand == Hand::SCISSORS)
	{
		DxLib::DrawString(_pos.x, _pos.y, "チョキ", 0xff0000);
	}
	else if (_hand == Hand::PAPER)
	{
		DxLib::DrawString(_pos.x, _pos.y, "パー", 0xff0000);
	}
}

void Player::Damage(const int& power)
{
	_hp -= power;
}

void Player::HandDraw()
{
	if (_decideFlag == false)
	{
		for (int i = 0; i < static_cast<int>(Hand::MAX); ++i)
		{
			std::string hand;
			if (i == 0)
			{
				hand = "グー";
			}
			else if (i == 1)
			{
				hand = "チョキ";
			}
			else if (i == 2)
			{
				hand = "パー";
			}

			if (_handCount[i] > 0)
			{
				DxLib::DrawString(_pos.x, _pos.y + 50 + (i * 30), hand.c_str(), 0x00ff00);
			}
		}
	}

	DxLib::DrawFormatString(_pos.x, _pos.y + 150, 0x00ff00, "HP:%d", _hp);
}

const int Player::GetHand() const
{
	return static_cast<int>(_hand);
}

const int Player::GetPower() const
{
	return _power[static_cast<int>(_hand)];
}

void Player::SetHand()
{
	_decideFlag = false;
	_hand = Hand::MAX;
}

void Player::ResetCount()
{
	_handCount = _initHandCount;
}
