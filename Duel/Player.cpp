#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"

Player::Player(const Vector2<int>& pos)
{
	_hand = Hand::MAX;
	_pos = pos;
}

Player::~Player()
{
}

void Player::Update(const int& pno, const Peripheral& p)
{
	if (p.IsTrigger(pno, "ROCK"))
	{
		_hand = Hand::ROCK;
	}
	else if (p.IsTrigger(pno, "SCISSORS"))
	{
		_hand = Hand::SCISSORS;
	}
	else if (p.IsTrigger(pno, "PAPER"))
	{
		_hand = Hand::PAPER;
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

const int Player::GetHand() const
{
	return static_cast<int>(_hand);
}

void Player::SetHand()
{
	_hand = Hand::MAX;
}
