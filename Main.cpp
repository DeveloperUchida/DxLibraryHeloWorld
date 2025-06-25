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
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	//DX���C�u�����̏�����
	if (DxLib_Init() < 0) {
		//errorCount1 Cloce
		return -1;
	}
	//�`���𗠉�ʂ�
	SetDrawScreen(DX_SCREEN_BACK);

	//��ʃ��[�h�̕ύX
	SetGraphMode(800, 600, 32);


	//����ʂ�\�̉�ʂɋt�]���f�A���b�Z�[�W�����A��ʃN���A
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		DrawFormatString(0, 0, GetColor(255, 255, 255), "Esc�̓��͂�����ƏI�����܂�");


		if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
			break;
		}
	}

	DxLib_End();
	return 0;
}