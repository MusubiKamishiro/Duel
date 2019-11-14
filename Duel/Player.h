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

// じゃんけんの結果
enum class Result
{
	WIN,
	DRAW,
	LOSE,
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

	void Update(int pno, const Peripheral& p);

	void Draw();
};

