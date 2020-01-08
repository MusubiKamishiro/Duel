#pragma once
#include <array>
#include "Player.h"
#include "Geometry.h"

class Hud
{
private:
	// ラウンドとターンの描画
	void DrawRoundAndTurn()const;
	int _roundCount;
	int _turnCount;

	// HPの描画
	void DrawHp(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;
	Vector2<int> _maxHpLenght;

	// プレイヤーの技の描画
	void DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;

	// 引数の文字列を画面の中央に揃える座標を返す
	int GetStringCenterPosx(const std::string& name)const;
	
	// ゲーム画面のサイズ
	Vector2<int> ssize;

public:
	Hud();
	~Hud();

	// ターンを進める際に呼び出す
	//@return ラウンドが進む際にtrueが返ってくる
	bool AdvanceTheTurn();

	// Hudの描画全てが入っている
	void Draw(const PlayerData& rPlayerData, const PlayerData& lPlayerData);
};

