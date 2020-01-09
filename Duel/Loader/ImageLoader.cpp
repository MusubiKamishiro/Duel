#include "ImageLoader.h"
#include <DxLib.h>

ImageLoader::ImageLoader()
{
}

ImageLoader::~ImageLoader()
{
}

int ImageLoader::Load(std::string path)
{
	int img = 0;

	// �f�[�^��������Ȃ�������ǂݍ���
	auto it = _table.find(path.c_str());
	if (it == _table.end())
	{
		img = DxLib::LoadGraph(path.c_str());
		if (img != -1)
		{
			_table.emplace(path, img);
		}
		return img;
	}
	else
	{
		// ����������n���h����Ԃ�
		img = _table[path.c_str()];
		return img;
	}
	return false;
}
