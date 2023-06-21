#include "DxLib.h"
#include "DebugDraw.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "Config.h"
#include "player.h"
int WINAPI _stdcall WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) 
{
	// ＤＸライブラリ初期化処理
	SetUseDirect3DVersion(DX_DIRECT3D_11);// 使用するDirectXバージョンを指定.

	// 画面モードセット.
	ChangeWindowMode(TRUE);// ウィンドウモードの変更.
	SetGraphMode(WindowX, WindowY, ColorBitNum);
	SetBackgroundColor(70, 70, 70);

	SetDrawScreen(DX_SCREEN_BACK);// 描画先を裏画面に変更する。

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// 奥行0.01～99999までをカメラの描画範囲とする。特に理由はないッ！.
	SetCameraNearFar(0.01f, 99999.0f);

	// ライトを設定.
	int light = ChangeLightTypeDir(VGet(1.0f, -1.0f, 1.0f));

	// コンフィグ.
	Config::Initialize();
	

	// マネージャー生成.
	ObjectManager::Initialize();
	AssetManager::Initalize();


	Player* player = new Player;
	ObjectManager::Entry(player);

	

	
	//時間計測.
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG prevTime = nowTime;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//フレーム時間計測.
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - prevTime) / 1000000.0f;
		ObjectManager::Update(deltaTime);

		ClearDrawScreen();
		ObjectManager::Draw();
		Debag::DrawGrid(30000, 10);
		ScreenFlip();
		prevTime = nowTime;
	}
	
	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();
	AssetManager::Finalize();
	Config::Finalize();
	DxLib_End();
	return 0;
}