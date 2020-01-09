#include "Game.h"
#include <DxLib.h>
#include "Peripheral.h"
#include "Scene/SceneManager.h"
#include "FrameFixity.h"
//#include "resource.h"


Game::Game() : ScreenSize(1440, 810)
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

	DxLib::SetGraphMode(ScreenSize.x, ScreenSize.y, 32);

	if (DxLib::DxLib_Init() == -1)
	{
		return;
	}

	DxLib::SetMainWindowText("Duel");		// タイトル
	//DxLib::SetWindowIconID(IDI_ICON1);	// アイコン
	DxLib::SetDrawScreen(DX_SCREEN_BACK);	// 裏画面に描画

	// フォントの変更
	AddFontResourceEx("fonts/PixelMplus10-Regular.ttf", FR_PRIVATE, nullptr);
	DxLib::ChangeFont("PixelMplus10", DX_CHARSET_DEFAULT);

	peripheral.reset(new Peripheral());
}

void Game::InitPeripheral()
{
	// キーボード
	peripheral->AddCommand(0, "ROCK",		0, KEY_INPUT_A);
	peripheral->AddCommand(0, "SCISSORS",	0, KEY_INPUT_S);
	peripheral->AddCommand(0, "PAPER",		0, KEY_INPUT_D);
	peripheral->AddCommand(0, "DECIDE",		0, KEY_INPUT_Z);
	peripheral->AddCommand(0, "PAUSE",		0, KEY_INPUT_W);
	
	peripheral->AddCommand(1, "ROCK",		0, KEY_INPUT_J);
	peripheral->AddCommand(1, "SCISSORS",	0, KEY_INPUT_K);
	peripheral->AddCommand(1, "PAPER",		0, KEY_INPUT_L);
	peripheral->AddCommand(1, "DECIDE",		0, KEY_INPUT_Z);
	peripheral->AddCommand(1, "PAUSE",		0, KEY_INPUT_W);
	
	// パッド
	for (int i = 0; i < 2; ++i)
	{
		peripheral->AddCommand(i, "ROCK",		i + 1, PAD_INPUT_2);
		peripheral->AddCommand(i, "SCISSORS",	i + 1, PAD_INPUT_3);
		peripheral->AddCommand(i, "PAPER",		i + 1, PAD_INPUT_4);
		peripheral->AddCommand(i, "DECIDE",		i + 1, PAD_INPUT_1);
		peripheral->AddCommand(i, "PAUSE",		i + 1, PAD_INPUT_8);
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

			peripheral->Update();
			scenes.Update(*peripheral);
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

const Vector2<int>& Game::GetScreenSize()const
{
	return ScreenSize;
}
