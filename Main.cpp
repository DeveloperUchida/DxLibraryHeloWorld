#include "DxLib.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//�E�C���h�E���[�h��L��
	ChangeWindowMode(TRUE);

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