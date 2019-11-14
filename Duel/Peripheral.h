#pragma once
#include<array>

// 周辺機器(キーボード&パッド)の入力を制御
class Peripheral
{
private:
	std::array<int, 2> padState;		// 現在の入力情報
	std::array<int, 2> lastPadState;	// 直前フレームの入力状態

public:
	Peripheral();
	~Peripheral();

	// 入力情報の更新(毎フレーム)
	void Update();

	// 現在の押下状態の検出
	// @param pno	プレイヤー番号
	// @param keyid	調べたいキー番号
	// @pretval true 押してる, false 押してない
	bool IsPressing(int pno, int keyid)const;

	// 現在のトリガー状態(押した瞬間)の検出
	bool IsTrigger(int pno, int keyid)const;
};

