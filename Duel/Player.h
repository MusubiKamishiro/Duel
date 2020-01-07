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
	std::array<int, static_cast<int>(Hand::MAX)> _initHandCount;
	std::array<int, static_cast<int>(Hand::MAX)> _handCount;
	Hand _hand;

	int _hp;	// �̗�
	std::array<int, static_cast<int>(Hand::MAX)> _power;	// �U����


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
	// Hand�̎g�p�񐔂����Z�b�g����
	// ���E���h���ڍs����ۂɎg�p����
	void ResetCount();
};
