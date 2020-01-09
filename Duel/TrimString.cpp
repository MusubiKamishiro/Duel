#include "TrimString.h"
#include <DxLib.h>
#include "Game.h"

TrimString::TrimString()
{
	ssize = Game::Instance().GetScreenSize();
}

TrimString::~TrimString()
{
}

int TrimString::GetStringCenterPosx(const std::string& name)const
{
	return (ssize.x / 2 - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())) / 2);
}

int TrimString::GetStringRightPosx(const std::string& name, const int& rpos)
{
	return (rpos - DxLib::GetDrawStringWidth(name.c_str(), std::strlen(name.c_str())));
}
