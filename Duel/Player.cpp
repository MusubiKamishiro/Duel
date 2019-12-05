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
}

Player::~Player()
{
}

void Player::Check(const Hand& hand)
{
	if (_handCount[static_cast<int>(hand)] > 0)
	{
		_hand = hand;
		--_handCount[static_cast<int>(hand)];
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

void Player::HandDraw()
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
			DxLib::DrawString(_pos.x, _pos.y + 50 + (i*30), hand.c_str(), 0x00ff00);
		}
	}
}

const int Player::GetHand() const
{
	return static_cast<int>(_hand);
}

void Player::SetHand()
{
	_hand = Hand::MAX;
}

void Player::ResetCount()
{
	_handCount = _initHandCount;
}
