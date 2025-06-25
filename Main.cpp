#include "DxLib.h"
#include <Windows.h>
#include <sal.h>
#include <vector>

struct Bullet
{
	int x, y;
	bool isActive;
};

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600; //使わないとエラーになる？？ それにしてSyntaxって・・・
const int PLAYER_WIDTH = 40;
const int PLAYER_HEIGHT = 20;
const int BULLET_SPEED = 10;
const int PLAYER_SPEED = 5;

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{

	//ウインドウモードを有効
	ChangeWindowMode(TRUE);
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

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