#pragma once
#include <array>
#include "Geometry.h"

class Peripheral;

// プレイヤーの使える技
enum class Hand
{
	ROCK,		// グー
	SCISSORS,	// チョキ
	PAPER,		// パー
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
