#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include "Engine/Engine.h"
#include "Common/Vec.h"

Vec2 g_Position = Vec2(0.0f, 0.0f);
Vec2 g_Scale = Vec2(1.0f, 1.0f);
float g_Angle = 0.0f;
DWORD g_StratTime = 0;
DWORD g_ElapsedTime = 0;

// ゲーム処理
void GameProcessing();
// 描画処理
void DrawProcessing();

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR     lpCmpLine,
	_In_ INT       nCmdShow)
{
	g_StratTime = timeGetTime();
	// エンジンの初期化
	// ゲームループ開始前に1度だけ実行する
	if (Engine::Initialize(640, 480, "Sample") == false)
	{
		return 0;
	}

	while (true)
	{
		bool message_ret = false;
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			g_ElapsedTime = timeGetTime() - g_StratTime;
			// ゲーム処理
			GameProcessing();

			// 描画開始
			DrawProcessing();
		}
	}

	// エンジン終了
	// ゲームループ終了後に1度だけ実行する
	// テクスチャとサウンドファイルも全て解放する
	Engine::Release();

	// メモリリーク検出
	_CrtDumpMemoryLeaks();

	return 0;
}
void GameProcessing()
{
	// 入力データの更新
	Engine::Update();


	//========================================================
	// キーボードの入力取得
	//========================================================

	//if (Engine::IsKeyboardKeyPushed(DIK_SPACE) == true)
	//{
	//	// キーが押された瞬間の処理
	//}

	//if (Engine::IsKeyboardKeyHeld(DIK_LEFT) == true)
	//{
	//	// キーが押されている間の処理
	//}

	//if (Engine::IsKeyboardKeyReleased(DIK_A))
	//{
	//	// キーが離された瞬間の処理
	//}
}

void DrawProcessing()
{
	// 描画開始
	// 描画処理を実行する場合、必ず最初実行する
	Engine::StartDrawing(0);
	char countDownStrings{2};
	int countDownTime = 0;
	if (g_ElapsedTime < 3000)
	{

		sprintf_s(countDownStrings, 2, "%d", countDownTime);
		Engine::DrawFont(300.0f, 400.0f, "countDownStrings", FontSize::Large, FontColor::White);
	}
	

	// フォント描画
	Engine::DrawFont(0.0f, 0.0f, "FontSize:Small", FontSize::Small, FontColor::White);
	


	// 描画終了
	// 描画処理を終了する場合、必ず最後に実行する
	Engine::FinishDrawing();
}
