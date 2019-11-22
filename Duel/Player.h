#pragma once
#include <array>

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
private:
	bool flag;
	std::array<Hand, 2> hand;

public:
	Player();
	~Player();

	void Update(const int& pno, const Peripheral& p);

	void Draw();

	const int GetHand(const int& pno)const;
	void SetHand();
};
