#pragma once
#include <array>
#include <memory>
#include "Geometry.h"

class Peripheral;
class AI;

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
	int maxHp;		// �����̗�(�ő�̗�)
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// �Z��
	std::array<int, static_cast<int>(Skill::MAX)> power;	// �U����
	int goodSkill;	// ���ӋZ
};

// �v���C���[�̊�{�f�[�^
struct PlayerData
{
	int img;	// �L�����摜
	int maxHp;	// �ő�̗�
	float hp;	// �̗�
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// �Z��
	std::array<int, static_cast<int>(Skill::MAX)> power;	// �U����
	int goodSkill;		// ���ӋZ

	std::array<int, static_cast<int>(Skill::MAX)> initSkillCount;	// �g�p�񐔂̏����l
	std::array<int, static_cast<int>(Skill::MAX)> skillCount;		// �c��g�p��
	bool decideFlag;	// ������߂Ă��邩
	Skill skill;		// ���݂̎�
};


class Player
{
	PlayerData _playerData;
	int _frameImg;

	Vector2<int> _pos;
	bool _aiFlag;
	std::shared_ptr<AI> _ai;
	
	// �Z���g�p�\��
	void Check(const Skill& skill);

	// ���֌W
	int _decideSound;
	int _damageSound;

	// �h��֌W
	Vector2<float> _swing;
	bool _damageFlag;

	int _damage;
	void DrawDamage();

	// �G�t�F�N�g���\�[�X
	int _damageEffect;
	int _playingEffect;

public:
	Player(const Vector2<int>& pos, const InitStatus& initStatus, const bool& aiFlag);
	~Player();

	void Update(const int& pno, const PlayerData& enemyData, const Peripheral& p);

	void Draw();

	void Damage(const int& power);
	void DamageUpdate(const int& count);


	const int& GetPower()const;
	const PlayerData& GetPlayerData()const;
	const Vector2<int>& GetPos()const;

	void SetSkill();
	// Skill�̎g�p�񐔂����Z�b�g����
	// ���E���h���ڍs����ۂɎg�p����
	void ResetCount();
};
