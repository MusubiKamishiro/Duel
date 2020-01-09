#include "Game.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Scene/SceneManager.h"
#include "Loader/FileSystem.h"
#include "FrameFixity.h"
//#include "resource.h"


Game::Game() : _screenSize(1440, 810)
{
}

void Game::operator=(const Game &)
{
}

Game::~Game()
{
}

void Game::Initialize()
{
#ifdef _DEBUG
	DxLib::ChangeWindowMode(true);
#else
	int ans = MessageBox(DxLib::GetMainWindowHandle(), "フルスクリーンで表示しますか？", "画面の大きさどうしようか", MB_YESNO | MB_ICONQUESTION);

	if (ans == IDYES)
	{
		DxLib::ChangeWindowMode(false);
	}
	else
	{
		DxLib::ChangeWindowMode(true);
	}
#endif // DEBUG

	DxLib::SetGraphMode(_screenSize.x, _screenSize.y, 32);

	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}

	DxLib::SetMainWindowText("ButtleFighters");		// タイトル
	//DxLib::SetWindowIconID(IDI_ICON1);	// アイコン
	DxLib::SetDrawScreen(DX_SCREEN_BACK);	// 裏画面に描画

	// フォントの変更
	AddFontResourceEx("fonts/PixelMplus10-Regular.ttf", FR_PRIVATE, nullptr);
	DxLib::ChangeFont("PixelMplus10", DX_CHARSET_DEFAULT);

	_peripheral.reset(new Peripheral());
	_fileSystem.reset(new FileSystem());
}

void Game::InitPeripheral()
{
	// キーボード
	_peripheral->AddCommand(0, "ROCK",		0, KEY_INPUT_A);
	_peripheral->AddCommand(0, "SCISSORS",	0, KEY_INPUT_S);
	_peripheral->AddCommand(0, "PAPER",		0, KEY_INPUT_D);
	_peripheral->AddCommand(0, "DECIDE",	0, KEY_INPUT_Z);
	_peripheral->AddCommand(0, "PAUSE",		0, KEY_INPUT_W);
	_peripheral->AddCommand(0, "UP",		0, KEY_INPUT_UP);
	_peripheral->AddCommand(0, "RIGHT",		0, KEY_INPUT_RIGHT);
	_peripheral->AddCommand(0, "DOWN",		0, KEY_INPUT_DOWN);
	_peripheral->AddCommand(0, "LEFT",		0, KEY_INPUT_LEFT);
	
	_peripheral->AddCommand(1, "ROCK",		0, KEY_INPUT_J);
	_peripheral->AddCommand(1, "SCISSORS",	0, KEY_INPUT_K);
	_peripheral->AddCommand(1, "PAPER",		0, KEY_INPUT_L);
	_peripheral->AddCommand(1, "DECIDE",	0, KEY_INPUT_Z);
	_peripheral->AddCommand(1, "PAUSE",		0, KEY_INPUT_W);
	_peripheral->AddCommand(1, "UP",		0, KEY_INPUT_F);
	_peripheral->AddCommand(1, "RIGHT",		0, KEY_INPUT_X);
	_peripheral->AddCommand(1, "DOWN",		0, KEY_INPUT_C);
	_peripheral->AddCommand(1, "LEFT",		0, KEY_INPUT_V);
	
	// パッド
	for (int i = 0; i < 2; ++i)
	{
		_peripheral->AddCommand(i, "PAPER",		i + 1, PAD_INPUT_2);
		_peripheral->AddCommand(i, "SCISSORS",	i + 1, PAD_INPUT_3);
		_peripheral->AddCommand(i, "ROCK",		i + 1, PAD_INPUT_4);
		_peripheral->AddCommand(i, "DECIDE",	i + 1, PAD_INPUT_1);
		_peripheral->AddCommand(i, "PAUSE",		i + 1, PAD_INPUT_8);
		
		_peripheral->AddCommand(i, "UP",		i + 1, PAD_INPUT_UP);
		_peripheral->AddCommand(i, "RIGHT",		i + 1, PAD_INPUT_RIGHT);
		_peripheral->AddCommand(i, "DOWN",		i + 1, PAD_INPUT_DOWN);
		_peripheral->AddCommand(i, "LEFT",		i + 1, PAD_INPUT_LEFT);
	}
}

void Game::Run()
{
	auto& scenes = SceneManager::Instance();
	FrameFixity& ff = FrameFixity::Instance();
	ff.FFInitialize();

	while (DxLib::ProcessMessage() == 0)
	{
		if (ff.CheckReceiveMessage())
		{
			if (ff.GetReceiveMessage().message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			ff.AdjustmentFrameLate();

			DxLib::ClearDrawScreen();

			// エスケープキーで終了
			if (DxLib::CheckHitKey(KEY_INPUT_ESCAPE))
			{
				break;
			}

			_peripheral->Update();
			scenes.Update(*_peripheral);
			scenes.Draw();

			DxLib::ScreenFlip();
		}
	}

	ff.Terminate();
}

void Game::Terminate()
{
	DxLib::DxLib_End();
}

const std::shared_ptr<FileSystem> Game::GetFileSystem() const
{
	return _fileSystem;
}

const Vector2<int>& Game::GetScreenSize()const
{
	return _screenSize;
}
