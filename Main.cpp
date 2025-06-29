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
	//画面モードの変更
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//DXライブラリの初期化
	if (DxLib_Init() < 0) {
		//errorCount1 Cloce
		return -1;
	}
	//描画先を裏画面へ
	SetDrawScreen(DX_SCREEN_BACK);

	//プレイヤーの初期位置
	int playerX = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
	int playerY = SCREEN_HEIGHT - 60;

	//弾のコンテナ
	std::vector<Bullet> bullets;

	//弾の連射制御
	int shootCooldown = 0;

	//画面モードの変更
	SetGraphMode(800, 600, 32);


	//裏画面を表の画面に逆転反映、メッセージ処理、画面クリア
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//テキスト表示
		DrawFormatString(0, 0, GetColor(255, 255, 255), "← → で移動 / スペースで弾発射 / Escで終了");

		if (CheckHitKey(KEY_INPUT_LEFT)) playerX -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT))playerX += PLAYER_SPEED;

		//画面外移動防止
		if (playerX < 0) playerX = 0;
		if (playerX > SCREEN_WIDTH - PLAYER_WIDTH) playerX = SCREEN_WIDTH - PLAYER_WIDTH;

		//弾の発射機能(Spacekey)
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			if (shootCooldown == 0)
			{
				Bullet newBullet = { playerX + PLAYER_WIDTH / 2, playerX, true };
				bullets.push_back(newBullet);
				shootCooldown = 10;
			}
		}
		//連射制御のクールダウン
		if (shootCooldown > 0) shootCooldown--;

		//弾丸情報の更新
		for (auto& bullet : bullets)
		{
			if (bullet.isActive)
			{
				bullet.y -= BULLET_SPEED;
				if (bullet.y < 0)
				{
					bullet.isActive = false;
				}
			}
		}


		//弾丸の描画
		for (const auto& bullet : bullets)
		{
			if (bullet.isActive)
			{
				DrawCircle(bullet.x, bullet.y, 5, GetColor(255, 255, 0), TRUE);
			}
		}
		//プレイヤーの描画
		DrawBox(playerX, playerY, playerX + PLAYER_WIDTH, playerY + PLAYER_HEIGHT, GetColor(0, 255, 0), TRUE);

		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
			break;
		}
	}

	DxLib_End();
	return 0;
}