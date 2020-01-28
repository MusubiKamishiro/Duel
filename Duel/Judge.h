#pragma once
#include <memory>
#include <string>

class TrimString;

// じゃんけんの結果
enum class Result
{
	DRAW,
	PLAYER1WIN,
	PLAYER2WIN,
	MAX
};


class Judge
{
private:
	Result _result;

	std::unique_ptr<TrimString> _trimString;

public:
	Judge();
	~Judge();

	// 試合結果を判断する
	//@param rSkill...右プレイヤーのスキル
	//@param lSkill...左プレイヤーのスキル
	void JudgeResult(const int& rSkill, const int& lSkill);

	void Draw();

	// 試合結果を取得する
	Result GetResult()const;
};
