#pragma once
#include <array>
#include "Geometry.h"

class Peripheral;

// �v���C���[�̎g����Z
enum class Hand
{
	ROCK,		// �O�[
	SCISSORS,	// �`���L
	PAPER,		// �p�[
	MAX
};



class Player
{
	Hand _hand;

	Vector2<int> _pos;
public:
	Player(const Vector2<int>& pos);
	~Player();

	void Update(const int& pno, const Peripheral& p);

	void Draw();

	const int GetHand()const;
	void SetHand();
};
