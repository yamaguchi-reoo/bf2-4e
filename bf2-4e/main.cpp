#include"DxLib.h"

/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	SetMainWindowText("bf");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	//SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);	//��ʃT�C�Y�̐ݒ�

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	// �Q�[�����[�v
	while ((ProcessMessage() == 0)) {

		ClearDrawScreen();		// ��ʂ̏�����

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}
	return 0;
}