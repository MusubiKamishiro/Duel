#pragma once
#include <array>
#include "Geometry.h"

class Peripheral;

// �v���C���[�̎g����Z
enum class Skill
{
	ROCK,		// �O�[
	SCISSORS,	// �`���L
	PAPER,		// �p�[
	MAX
};

// �v���C���[�̏����X�e�[�^�X
// �Z���N�g�V�[�����玝���Ă������
struct InitStatus
{
	int charNum;	// �L�����ԍ�
	int hp;			// �̗�
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// �Z��
	std::array<int, static_cast<int>(Skill::MAX)> power;	// �U����
	int goodSkill;	// ���ӋZ
};

// �v���C���[�̊�{�f�[�^
struct PlayerData
{
	int img;	// �L�����摜
	int maxHp;	// �ő�̗�
	int hp;		// �̗�
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// �Z��
	std::array<int, static_cast<int>(Skill::MAX)> power;	// �U����
	int goodSkill;	// ���ӋZ

	std::array<int, static_cast<int>(Skill::MAX)> initSkillCount;
	std::array<int, static_cast<int>(Skill::MAX)> skillCount;
	bool decideFlag;
	Skill skill;
};


class Player
{
	PlayerData _playerData;
	int _frameImg;

	Vector2<int> _pos;
	
	// �Z���g�p�\��
	void Check(const Skill& skill);

	// ���֌W
	int _decideSound;
	int _damageSound;

public:
	Player(const Vector2<int>& pos, const InitStatus initStatus);
	~Player();

	void Update(const int& pno, const Peripheral& p);

	void Draw();

	void Damage(const int& power);

	const int GetPower()const;
	const PlayerData& GetPlayerData()const;

	void SetSkill();
	// Skill�̎g�p�񐔂����Z�b�g����
	// ���E���h���ڍs����ۂɎg�p����
	void ResetCount();
};
