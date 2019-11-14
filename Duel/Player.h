#pragma once
#include <array>
class Peripheral;

// �v���C���[�̎g����Z
enum class Hand
{
	ROCK,		// �O�[
	SCISSORS,	// �`���L
	PAPER,		// �p�[
	MAX
};

// ����񂯂�̌���
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

