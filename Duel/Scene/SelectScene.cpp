#include <DxLib.h>
#include "SelectScene.h"
#include "GamePlayingScene.h"
#include "SceneManager.h"
#include "../Peripheral.h"
#include "../TrimString.h"

#include "../Game.h"
#include "../Loader/FileSystem.h"
#include "../Loader/ImageLoader.h"
#include "../CharData.h"


void SelectScene::FadeinUpdate(const Peripheral& p)
{
	if (_pal >= 255)
	{
		_pal = 255;
		updater = &SelectScene::WaitUpdate;
	}
	else
	{
		_pal += 20;
	}
}

void SelectScene::FadeoutUpdate(const Peripheral& p)
{
	if (_pal <= 0)
	{
		SceneManager::Instance().ChangeScene(std::make_unique <GamePlayingScene>(_initStatus));
	}
	else
	{
		_pal -= 20;
	}
}

void SelectScene::WaitUpdate(const Peripheral& p)
{
	for (int i = 0; i < _initStatus.size(); ++i)
	{
		if (_isDecide[i])
		{
			if (i == _initStatus.size() - 1)
			{
				_pal = 255;
				updater = &SelectScene::FadeoutUpdate;
			}
		}
		else
		{
			break;
		}
	}

	for (int i = 0; i < _initStatus.size(); ++i)
	{
		ChangeCharacter(p, i);
	}
}

void SelectScene::ChangeCharacter(const Peripheral& p, const int& num)
{
	if (_isDecide[num])
	{
		return;
	}

	/// キャラクターのIDを変更している
	if (p.IsTrigger(num, "RIGHT"))
	{
		_initStatus[num].charNum += (_initStatus[num].charNum < _charID ? 1 : 0);
	}
	else if (p.IsTrigger(num, "LEFT"))
	{
		_initStatus[num].charNum -= (_initStatus[num].charNum > 1 ? 1 : 0);
	}
	else if (p.IsTrigger(num, "UP"))
	{
		_initStatus[num].charNum -= ((_initStatus[num].charNum - 1) / (_charID / 2) >= 1 ? _charID / 2 : 0);
	}
	else if (p.IsTrigger(num, "DOWN"))
	{
		_initStatus[num].charNum += ((_initStatus[num].charNum - 1) / (_charID / 2) <= 0 ? _charID / 2 : 0);
	}

	if (p.IsTrigger(num, "DECIDE"))
	{
		_isDecide[num] = true;
		_initStatus[num].charNum -= 1;
		_initStatus[num].hp = _charData[_initStatus[num].charNum][static_cast<int>(charData::HP)];
		_initStatus[num].power[0]	  = _charData[_initStatus[num].charNum][static_cast<int>(charData::ATK1)];
		_initStatus[num].power[1]	  = _charData[_initStatus[num].charNum][static_cast<int>(charData::ATK2)];
		_initStatus[num].power[2]	  = _charData[_initStatus[num].charNum][static_cast<int>(charData::ATK3)];
		_initStatus[num].skillName[0] = _skName[_initStatus[num].charNum][static_cast<int>(Skill::ROCK)];
		_initStatus[num].skillName[1] = _skName[_initStatus[num].charNum][static_cast<int>(Skill::SCISSORS)];
		_initStatus[num].skillName[2] = _skName[_initStatus[num].charNum][static_cast<int>(Skill::PAPER)];
		_initStatus[num].goodSkill	  = _goodSk[_initStatus[num].charNum];
		_initStatus[num].charNum += 1;
	}

}

SelectScene::SelectScene() : _charID(10), _boxSize(150, 150)
{
	_pal = 0;
	_trimString = std::make_unique<TrimString>();

	/// キャラクターのID指定(とりあえず直値)　◆
	_initStatus[0].charNum = 1;
	_initStatus[1].charNum = 5;

	/// キャラクター決定用判定の初期化
	_isDecide = {false, false};

	updater = &SelectScene::FadeinUpdate;
}

SelectScene::~SelectScene()
{
}

void SelectScene::Update(const Peripheral& p)
{
	(this->*updater)(p);
}

void SelectScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);

	_trimString->ChangeFontSize(50);
	DxLib::DrawString(_trimString->GetStringCenterPosx("キャラクターを選んでね！"), _scrSize.y / 10, "キャラクターを選んでね！", 0xffffff);

	/// 画像読み込み用ID
	int imageID = 0;

	/// 位置調整用
	int boxHalfWidth = (_charID / 2) * (_boxSize.x / 2);
	Vector2<int> points[2];

	/// キャラクターセレクトのボックス描画
	for (int i = 0; i < _charID; ++i)
	{
		/// アイコンイメージの読み込み
		imageID = Game::Instance().GetFileSystem()->Load("img/icon" + std::to_string(i + 1) + ".png");
		/// キャラセレクトのボックス描画

		points[0] = Vector2<int>(_scrSize.x / 2 - boxHalfWidth + _boxSize.x * (i % (_charID / 2)),
								 _scrSize.y * 3 / 5 + _boxSize.y * (i / (_charID / 2)));

		points[1] = Vector2<int>(_scrSize.x / 2 - boxHalfWidth + _boxSize.x * (i % (_charID / 2) + 1),
								 _scrSize.y * 3 / 5 + _boxSize.y * (i / (_charID / 2) + 1));

		DxLib::DrawGraph(points[0].x, points[0].y, imageID, true);
		DxLib::DrawBox(points[0].x, points[0].y, points[1].x, points[1].y, 0x22cc00, false);
	}
	/// プレイヤー枠の色
	int color;	
		/// キャラクターアイコンの描画
	for (int i = 0; i < _initStatus.size(); ++i)
	{
		/// アイコンイメージの読み込み
		imageID = Game::Instance().GetFileSystem()->Load("img/icon" + std::to_string(_initStatus[i].charNum) + ".png");

		/// 選択したキャラクターアイコンの描画
		points[0] = Vector2<int>(_scrSize.x / 2 + (i == 0 ? -_scrSize.x / 3 : _scrSize.x / 3),
								 _scrSize.y / 6 - _boxSize.y / 2 - (_boxSize.y / 5));

		points[1] = Vector2<int>(_scrSize.x / 2 + (i == 0 ? -_scrSize.x / 3 : _scrSize.x / 3) + _boxSize.x,
								 _scrSize.y / 6 + _boxSize.y - (_boxSize.y / 5));
		DxLib::DrawRotaGraph(points[0].x , points[0].y + _boxSize.x * 3 / 4, 
							 1.5, 0, imageID, true);

		// DxLib::DrawString(points[0].x, points[0].y)

		color = (i == 0 ? 0xff2055 : 0x3388ff);
		DxLib::DrawBoxAA(points[0].x - _boxSize.x * 3 / 4, points[0].y, points[1].x - _boxSize.x / 4, points[1].y, color, false, 10.f);

		/// 選択しているキャラクターの枠の描画 
		points[0] = Vector2<int>(_scrSize.x / 2 - boxHalfWidth + _boxSize.x * ((_initStatus[i].charNum - 1) % (_charID / 2)) + (i * 6),
								 _scrSize.y * 3 / 5 + _boxSize.y * ((_initStatus[i].charNum - 1) / (_charID / 2)) + (i * 6));

		points[1] = Vector2<int>(_scrSize.x / 2 - boxHalfWidth + _boxSize.x * ((_initStatus[i].charNum - 1) % (_charID / 2) + 1) - (i * 6),
								 _scrSize.y * 3 / 5 + _boxSize.y * ((_initStatus[i].charNum - 1) / (_charID / 2) + 1) - (i * 6));
		DxLib::DrawBoxAA(points[0].x, points[0].y, points[1].x, points[1].y, color, false, 8.f);
	}

	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, std::abs(_pal - 255));
	
	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0x000000, true);
}
