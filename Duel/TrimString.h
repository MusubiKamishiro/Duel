#pragma once
#include <string>
#include "Geometry.h"

///文字列描画のちょうどいい位置を返すクラス
class TrimString
{
private:
	// ゲーム画面のサイズ
	Vector2<int> ssize;
	// フォントサイズ
	int _fontSize;

public:
	TrimString();
	~TrimString();

	// 引数の文字列を画面の中央に揃える座標を返す
	int GetStringCenterPosx(const std::string& name)const;

	// 引数の文字列を右詰めにする座標を返す
	int GetStringRightPosx(const std::string& name, const int& rpos);

	// フォントサイズの変更
	void ChangeFontSize(const int& fontSize);

	// 現在のフォントサイズの獲得
	int GetFontSize()const;
};

