#include <DxLib.h>
#include <random>
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
		DxLib::StopSoundMem(_bgm);
		SceneManager::Instance().ChangeScene(std::make_unique <GamePlayingScene>(_initStatus, _aiFlags));
	}
	else
	{
		_pal -= 20;
	}
}

void SelectScene::WaitUpdate(const Peripheral& p)
{
	for (unsigned int i = 0; i < _initStatus.size(); ++i)
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

	for (unsigned int i = 0; i < _initStatus.size(); ++i)
	{
		ChangeCharacter(p, i);
	}
}

void SelectScene::ChangeCharacter(const Peripheral& p, const int& num)
{
	/// キャラクター選択をキャンセル
	if (p.IsTrigger(num, "CANCEL"))
	{
		DxLib::PlaySoundMem(_cancelSE, DX_PLAYTYPE_BACK);
		_isDecide[num] = false;
	}

	if (_isDecide[num])
	{
		return;
	}

	int id = _initStatus[num].charNum;
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
	else{}

	if (id != _initStatus[num].charNum)
	{
		DxLib::PlaySoundMem(_selSE, DX_PLAYTYPE_BACK);
	}

	if (p.IsTrigger(num, "DECIDE"))
	{
		DxLib::PlaySoundMem(_decideSE, DX_PLAYTYPE_BACK);
		_isDecide[num] = true;
		_initStatus[num].charNum -= 1;
		_initStatus[num].maxHp = _charData[_initStatus[num].charNum][static_cast<int>(charData::HP)];
		_initStatus[num].power[0]	  = _charData[_initStatus[num].charNum][static_cast<int>(charData::ATK1)];
		_initStatus[num].power[1]	  = _charData[_initStatus[num].charNum][static_cast<int>(charData::ATK2)];
		_initStatus[num].power[2]	  = _charData[_initStatus[num].charNum][static_cast<int>(charData::ATK3)];
		_initStatus[num].skillName[0] = _skName[_initStatus[num].charNum][static_cast<int>(Skill::ROCK)];
		_initStatus[num].skillName[1] = _skName[_initStatus[num].charNum][static_cast<int>(Skill::SCISSORS)];
		_initStatus[num].skillName[2] = _skName[_initStatus[num].charNum][static_cast<int>(Skill::PAPER)];
		_initStatus[num].goodSkill	  = _goodSk[_initStatus[num].charNum];
		_initStatus[num].charNum += 1;
	}

	if (_aiFlags[1] && (_isDecide[1] == false))
	{
		std::random_device seed_gen;
		std::mt19937 engine(seed_gen());
		int cnum = engine() % 10 + 1;
		
		DxLib::PlaySoundMem(_decideSE, DX_PLAYTYPE_BACK);
		_isDecide[1] = true;
		_initStatus[1].charNum = cnum - 1;
		_initStatus[1].maxHp = _charData[_initStatus[1].charNum][static_cast<int>(charData::HP)];
		_initStatus[1].power[0] = _charData[_initStatus[1].charNum][static_cast<int>(charData::ATK1)];
		_initStatus[1].power[1] = _charData[_initStatus[1].charNum][static_cast<int>(charData::ATK2)];
		_initStatus[1].power[2] = _charData[_initStatus[1].charNum][static_cast<int>(charData::ATK3)];
		_initStatus[1].skillName[0] = _skName[_initStatus[1].charNum][static_cast<int>(Skill::ROCK)];
		_initStatus[1].skillName[1] = _skName[_initStatus[1].charNum][static_cast<int>(Skill::SCISSORS)];
		_initStatus[1].skillName[2] = _skName[_initStatus[1].charNum][static_cast<int>(Skill::PAPER)];
		_initStatus[1].goodSkill = _goodSk[_initStatus[1].charNum];
		_initStatus[1].charNum += 1;
	}
}

SelectScene::SelectScene(const int& mode) : _charID(10), _boxSize(150, 150)
{
	_pal = 0;
	_trimString = std::make_unique<TrimString>();

	_bgm		= Game::Instance().GetFileSystem()->Load("sound/bgm/select.mp3");
	_decideSE	= Game::Instance().GetFileSystem()->Load("sound/se/decide.mp3");
	_cancelSE	= Game::Instance().GetFileSystem()->Load("sound/se/cancel.mp3");
	_selSE		= Game::Instance().GetFileSystem()->Load("sound/se/cursor.mp3");

	_frameImg = Game::Instance().GetFileSystem()->Load("img/statusFrame.png");

	/// キャラクターのID指定(とりあえず直値)　◆
	_initStatus[0].charNum = 1;
	_initStatus[1].charNum = 5;

	/// キャラクター決定用判定の初期化
	_isDecide = {false, false};

	if (mode == 0)
	{
		_aiFlags = { false, true };
	}
	else if (mode == 1)
	{
		_aiFlags = { false, false };
	}

	updater = &SelectScene::FadeinUpdate;
}

SelectScene::~SelectScene()
{
}

void SelectScene::Update(const Peripheral& p)
{
	if (!DxLib::CheckSoundMem(_bgm))
	{
		DxLib::PlaySoundMem(_bgm, DX_PLAYTYPE_LOOP);
	}

	(this->*updater)(p);
}

void SelectScene::Draw()
{
	DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pal);

	DxLib::DrawBox(0, 0, _scrSize.x, _scrSize.y, 0xffffff, true);

	_trimString->ChangeFontSize(50);
	DxLib::DrawString(_trimString->GetStringCenterPosx("キャラクターを選んでね！"), 
					  _scrSize.y / 10, "キャラクターを選んでね！", 0x000000);

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
	/// ステータス文字の保存用
	std::string status;

	int strSpace;
	/// キャラクターアイコンの描画
	for (unsigned int i = 0; i < _initStatus.size(); ++i)
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

		/// 文字の表示を行っている　◆
		_trimString->ChangeFontSize(25);
		strSpace = (_trimString->GetFontSize() + (_trimString->GetFontSize() / 2));
		int strWidth = 150;
		if (i == 0)
		{
			status = "%4d : HP";

			DxLib::DrawFormatString(strWidth,
				points[0].y + _boxSize.y + (_boxSize.y / 2) + strSpace, 0x000000, status.c_str(), _charData[_initStatus[i].charNum - 1][static_cast<int>(charData::HP)]);
		}
		else
		{
			status = "HP : %4d";

			DxLib::DrawFormatString(_trimString->GetStringRightPosx("HP : 0000", _scrSize.x - strWidth),
				points[0].y + _boxSize.y + (_boxSize.y / 2) + strSpace, 0x000000, status.c_str(), _charData[_initStatus[i].charNum - 1][static_cast<int>(charData::HP)]);
		}

		for (int j = 1; j < static_cast<int>(charData::MAX); ++j)
		{
			color = 0x000000;
			if (_goodSk[_initStatus[i].charNum - 1] == (j - 1))
			{
				color = 0xff0000;
			}
			strSpace = (_trimString->GetFontSize() + (_trimString->GetFontSize() / 2)) * (1 + j);

			if (i == 0)
			{
				status = "%4d : " + _skName[_initStatus[i].charNum - 1][j - 1];

				DxLib::DrawFormatString(strWidth,
					points[0].y + _boxSize.y + (_boxSize.y / 2) + strSpace, color, status.c_str(), _charData[_initStatus[i].charNum - 1][j]);
			}
			else
			{
				status = _skName[_initStatus[i].charNum - 1][j - 1] + " : %4d";

				DxLib::DrawFormatString(_trimString->GetStringRightPosx((_skName[_initStatus[i].charNum - 1][j - 1] + " : 0000"), _scrSize.x - strWidth),
					points[0].y + _boxSize.y + (_boxSize.y / 2) + strSpace, color, status.c_str(), _charData[_initStatus[i].charNum - 1][j]);
			}
		}

		DxLib::DrawExtendGraph(120, 260, (_scrSize.x / 2 - 150), 460, _frameImg, true);
		DxLib::DrawExtendGraph((_scrSize.x - 120), 260, (_scrSize.x / 2 + 150), 460, _frameImg, true);

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
