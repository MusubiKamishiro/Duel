#pragma once
#include <array>
#include "Geometry.h"

class Peripheral;

// プレイヤーの使える技
enum class Skill
{
	ROCK,		// グー
	SCISSORS,	// チョキ
	PAPER,		// パー
	MAX
};

// プレイヤーの初期ステータス
// セレクトシーンから持ってくるもの
struct InitStatus
{
	int charNum;	// キャラ番号
	int hp;			// 体力
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// 技名
	std::array<int, static_cast<int>(Skill::MAX)> power;	// 攻撃力
	int goodSkill;	// 得意技
};

// プレイヤーの基本データ
struct PlayerData
{
	int img;	// キャラ画像
	int maxHp;	// 最大体力
	int hp;		// 体力
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// 技名
	std::array<int, static_cast<int>(Skill::MAX)> power;	// 攻撃力
	int goodSkill;	// 得意技

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
	
	// 技が使用可能か
	void Check(const Skill& skill);

	// 音関係
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
	// Skillの使用回数をリセットする
	// ラウンドが移行する際に使用する
	void ResetCount();
};
