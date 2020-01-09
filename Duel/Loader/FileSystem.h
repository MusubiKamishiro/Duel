#pragma once
#include <memory>
#include <map>
#include <string>

class Loader;
class Data;

class FileSystem
{
private:
	std::unique_ptr<Loader> imageLoader;
	std::unique_ptr<Loader> soundLoader;

	std::map<std::string, std::shared_ptr<Loader>> loaders;

	///拡張子の抽出
	///これを利用して,どのLoadを使用するかを決定する
	std::string GetExtension(const std::string& path);

public:
	FileSystem();
	~FileSystem();

	int Load(const std::string& filePath);
};

