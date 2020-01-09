#pragma once
#include <map>
#include <string>

class ImageLoader
{
private:
	ImageLoader();						// �����֎~
	ImageLoader(const ImageLoader&);	// �R�s�[�֎~
	void operator=(const ImageLoader&);	// ����֎~

	std::map<std::string, int> _table;

public:
	static ImageLoader& Instance()
	{
		static ImageLoader instance;
		return instance;
	}
	~ImageLoader();

	// �摜�̓ǂݍ���
	//@return -1...�ǂݍ��ݎ��s
	//@return -1�ȊO...�ǂݍ��񂾉摜�̃n���h��
	int Load(std::string path);
};

