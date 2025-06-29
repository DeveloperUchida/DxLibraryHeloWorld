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
const int SCREEN_HEIGHT = 600; //�g��Ȃ��ƃG���[�ɂȂ�H�H ����ɂ���Syntax���āE�E�E
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


	//�E�C���h�E���[�h��L��
	ChangeWindowMode(TRUE);
	//��ʃ��[�h�̕ύX
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() < 0) {
		//errorCount1 Cloce
		return -1;
	}
	//�`���𗠉�ʂ�
	SetDrawScreen(DX_SCREEN_BACK);

	//�v���C���[�̏����ʒu
	int playerX = SCREEN_WIDTH / 2 - PLAYER_WIDTH / 2;
	int playerY = SCREEN_HEIGHT - 60;

	//�e�̃R���e�i
	std::vector<Bullet> bullets;

	//�e�̘A�ː���
	int shootCooldown = 0;

	//��ʃ��[�h�̕ύX
	SetGraphMode(800, 600, 32);


	//����ʂ�\�̉�ʂɋt�]���f�A���b�Z�[�W�����A��ʃN���A
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		//�e�L�X�g�\��
		DrawFormatString(0, 0, GetColor(255, 255, 255), "�� �� �ňړ� / �X�y�[�X�Œe���� / Esc�ŏI��");

		if (CheckHitKey(KEY_INPUT_LEFT)) playerX -= PLAYER_SPEED;
		if (CheckHitKey(KEY_INPUT_RIGHT))playerX += PLAYER_SPEED;

		//��ʊO�ړ��h�~
		if (playerX < 0) playerX = 0;
		if (playerX > SCREEN_WIDTH - PLAYER_WIDTH) playerX = SCREEN_WIDTH - PLAYER_WIDTH;

		//�e�̔��ˋ@�\(Spacekey)
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			if (shootCooldown == 0)
			{
				Bullet newBullet = { playerX + PLAYER_WIDTH / 2, playerX, true };
				bullets.push_back(newBullet);
				shootCooldown = 10;
			}
		}
		//�A�ː���̃N�[���_�E��
		if (shootCooldown > 0) shootCooldown--;

		//�e�ۏ��̍X�V
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


		//�e�ۂ̕`��
		for (const auto& bullet : bullets)
		{
			if (bullet.isActive)
			{
				DrawCircle(bullet.x, bullet.y, 5, GetColor(255, 255, 0), TRUE);
			}
		}
		//�v���C���[�̕`��
		DrawBox(playerX, playerY, playerX + PLAYER_WIDTH, playerY + PLAYER_HEIGHT, GetColor(0, 255, 0), TRUE);

		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
			break;
		}
	}

	DxLib_End();
	return 0;
}