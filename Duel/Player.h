#pragma once
#include <array>
#include <memory>
#include "Geometry.h"

class Peripheral;
class AI;

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
	int maxHp;		// 初期体力(最大体力)
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// 技名
	std::array<int, static_cast<int>(Skill::MAX)> power;	// 攻撃力
	int goodSkill;	// 得意技
};

// プレイヤーの基本データ
struct PlayerData
{
	int img;	// キャラ画像
	int maxHp;	// 最大体力
	float hp;	// 体力
	std::array<std::string, static_cast<int>(Skill::MAX)> skillName;	// 技名
	std::array<int, static_cast<int>(Skill::MAX)> power;	// 攻撃力
	int goodSkill;		// 得意技

	std::array<int, static_cast<int>(Skill::MAX)> initSkillCount;	// 使用回数の初期値
	std::array<int, static_cast<int>(Skill::MAX)> skillCount;		// 残り使用回数
	bool decideFlag;	// 手を決めているか
	Skill skill;		// 現在の手
};


class Player
{
	PlayerData _playerData;
	int _frameImg;

	Vector2<int> _pos;
	bool _aiFlag;
	std::shared_ptr<AI> _ai;
	
	// 技が使用可能か
	void Check(const Skill& skill);

	// 音関係
	int _decideSound;
	int _damageSound;

	// 揺れ関係
	Vector2<float> _swing;
	bool _damageFlag;

	int _damage;
	void DrawDamage();

	// エフェクトリソース
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
	// Skillの使用回数をリセットする
	// ラウンドが移行する際に使用する
	void ResetCount();
};
