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
	std::array<int, static_cast<int>(Hand::MAX)> _initHandCount;
	std::array<int, static_cast<int>(Hand::MAX)> _handCount;
	Hand _hand;

	int _hp;	// 体力
	std::array<int, static_cast<int>(Hand::MAX)> _power;	// 攻撃力


	Vector2<int> _pos;
	bool _decideFlag;

	void Check(const Hand& hand);

public:
	Player(const Vector2<int>& pos);
	~Player();

	void Update(const int& pno, const Peripheral& p);

	void Draw();

	void Damage(const int& power);

	// 
	void HandDraw();

	const int GetHand()const;
	const int GetPower()const;
	void SetHand();
	// Handの使用回数をリセットする
	// ラウンドが移行する際に使用する
	void ResetCount();
};
