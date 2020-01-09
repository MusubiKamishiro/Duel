#include <string>

enum class Data
{
     HP,
     ATK1,
     ATK2,
     ATK3,
     MAX
};

extern std::string _skName[10][3];
extern int _charData[10][static_cast<int>(Data::MAX)];
extern int _goodSk[10];
