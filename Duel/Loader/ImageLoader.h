#pragma once
#include <map>
#include <string>

class ImageLoader
{
private:
	ImageLoader();						// 生成禁止
	ImageLoader(const ImageLoader&);	// コピー禁止
	void operator=(const ImageLoader&);	// 代入禁止

	std::map<std::string, int> _table;

public:
	static ImageLoader& Instance()
	{
		static ImageLoader instance;
		return instance;
	}
	~ImageLoader();

	// 画像の読み込み
	//@return -1...読み込み失敗
	//@return -1以外...読み込んだ画像のハンドル
	int Load(std::string path);
};

