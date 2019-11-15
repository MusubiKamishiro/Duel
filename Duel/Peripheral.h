#pragma once
#include <vector>
#include <array>
#include <map>
#include <string>

// 入力情報
struct PeripheralInfo
{
	PeripheralInfo() {};
	PeripheralInfo(int no, int c) : padNo(no), code(c) {};

	unsigned int padNo = 0;	// パッド番号	//@details 0...キーボード 1~4...パッド
	unsigned int code = 0;	// 入力コード
};

// 周辺機器(キーボード&パッド)の入力を制御
class Peripheral
{
private:
	std::array<char, 256> keyState;		// キーボードの入力情報
	std::array<char, 256> oldKeyState;
	std::array<int, 2> padState;		// パッドの入力情報
	std::array<int, 2> oldPadState;

	// 入力対応テーブル
	//@param string			コマンド文字列
	//@param PeripheralInfo	入力情報
	std::vector<std::multimap<std::string, PeripheralInfo>> inputTable;

public:
	Peripheral();
	~Peripheral();

	// 入力情報の更新(毎フレーム)
	void Update();

	// 現在の押下状態の検出
	//@param pno	プレイヤー番号
	//@param cmd	調べたいコマンド文字列
	//@retval true	押してる, false 押してない
	bool IsPressing(const int& pno, const char* cmd)const;

	// 現在のトリガー状態(押した瞬間)の検出
	//@param pno	プレイヤー番号
	//@param cmd	調べたいコマンド文字列
	//@retval true	押した, false 押してない
	bool IsTrigger(const int& pno, const char* cmd)const;

	// コマンド設定
	//@param pno	プレイヤー番号
	//@param cmd	コマンド文字列
	//@param preiNo	パッド番号
	//@param code	入力コード
	void AddCommand(const int& pno, const char* cmd, const unsigned int& padNo, const unsigned int& code);
};

