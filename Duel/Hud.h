#pragma once
#include <memory>
#include <array>
#include "Player.h"
#include "Geometry.h"

class TrimString;

class Hud
{
private:
	Hud();							// 生成禁止
	Hud(const Hud&);				// コピー禁止
	void operator=(const Hud&);	// 代入禁止

	// ラウンドとターンの描画
	void DrawRoundAndTurn()const;
	int _roundCount;
	int _turnCount;

	// HPの描画
	void DrawHp(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;
	Vector2<int> _maxHpLenght;

	// 相性表の描画
	void DrawType();
	int _typeImg;

	// プレイヤーの技の描画
	void DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;

	// ゲーム画面のサイズ
	Vector2<int> _ssize;
	// 画面の中央
	Vector2<int> _center;

	// 技の色(のちに画像で扱いたい)
	std::array<int, 3> _typeColor;

	// 上のHudの縦幅
	int _topHudHeight;
	// 上のHudの縁幅
	int _topHudEdge;

	std::unique_ptr<TrimString> _trimString;

public:
	static Hud& Instance()
	{
		static Hud instance;
		return instance;
	}
	~Hud();

	void Init();

	// ターンを進める際に呼び出す
	//@return ラウンドが進む際にtrueが返ってくる
	bool AdvanceTheTurn();

	// Hudの描画全てが入っている
	void Draw(const PlayerData& rPlayerData, const PlayerData& lPlayerData);

	const int& GetNowTurn()const;
};

