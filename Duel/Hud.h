#pragma once
#include <array>
#include "Player.h"

class Hud
{
private:
	// ラウンドとターンの描画
	void DrawRoundAndTurn()const;
	int _roundCount;
	int _turnCount;

	void DrawHp(const int& rightHp, const int& leftHp)const;

	// プレイヤーの技の描画
	void DrawPlayerSkill(const PlayerData& rPlayerData, const PlayerData& lPlayerData)const;

public:
	Hud();
	~Hud();

	// ターンを進める際に呼び出す
	//@return ラウンドが進む際にtrueが返ってくる
	bool AdvanceTheTurn();

	// Hudの描画全てが入っている
	void Draw(const PlayerData& rPlayerData, const PlayerData& lPlayerData);
};

