#pragma once
#include <map>
#include <string>

class ImageLoader
{
private:
	ImageLoader();						// ¶¬‹Ö~
	ImageLoader(const ImageLoader&);	// ƒRƒs[‹Ö~
	void operator=(const ImageLoader&);	// ‘ã“ü‹Ö~

	std::map<std::string, int> _table;

public:
	static ImageLoader& Instance()
	{
		static ImageLoader instance;
		return instance;
	}
	~ImageLoader();

	// ‰æ‘œ‚Ì“Ç‚İ‚İ
	//@return -1...“Ç‚İ‚İ¸”s
	//@return -1ˆÈŠO...“Ç‚İ‚ñ‚¾‰æ‘œ‚Ìƒnƒ“ƒhƒ‹
	int Load(std::string path);
};

