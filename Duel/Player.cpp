#include "Player.h"
#include <DxLib.h>
#include "Peripheral.h"

Player::Player()
{
	flag = false;
	hand[0] = Hand::MAX;
	hand[1] = Hand::MAX;
}

Player::~Player()
{
}

void Player::Update(const int& pno, const Peripheral& p)
{
	if (p.IsTrigger(pno, "ROCK"))
	{
		hand[pno] = Hand::ROCK;
	}
	else if (p.IsTrigger(pno, "SCISSORS"))
	{
		hand[pno] = Hand::SCISSORS;
	}
	else if (p.IsTrigger(pno, "PAPER"))
	{
		hand[pno] = Hand::PAPER;
	}
}

void Player::Draw()
{
	for (int i = 0; i < 2; ++i)
	{
		if (hand[i] == Hand::ROCK)
		{
			DxLib::DrawString(150 * (i + 1), 150, "グー", 0xff0000);
		}
		else if (hand[i] == Hand::SCISSORS)
		{
			DxLib::DrawString(150 * (i + 1), 150, "チョキ", 0xff0000);
		}
		else if (hand[i] == Hand::PAPER)
		{
			DxLib::DrawString(150 * (i + 1), 150, "パー", 0xff0000);
		}
	}
}

const int Player::GetHand(const int& pno) const
{
	return static_cast<int>(hand[pno]);
}

void Player::SetHand()
{
	for (int i = 0; i < 2; ++i)
	{
		hand[i] = Hand::MAX;
	}
}
