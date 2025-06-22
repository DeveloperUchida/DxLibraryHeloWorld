#include "DxLib.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//ウインドウモードを有効
	ChangeWindowMode(TRUE);

	//DXライブラリの初期化
	if (DxLib_Init() < 0) {
		//errorCount1 Cloce
		return -1;
	}
	//描画先を裏画面へ
	SetDrawScreen(DX_SCREEN_BACK);

	//画面モードの変更
	SetGraphMode(800, 600, 32);


	//裏画面を表の画面に逆転反映、メッセージ処理、画面クリア
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "Escの入力があると終了します");


		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
			break;
		}
	}

	DxLib_End();
	return 0;
}