#pragma once
#include"DxLib.h"

#define KEY_MAX 256
#define MOUSE_MAX 256

struct CURSOR {
	int x;	//x���W
	int y;	//y���W
};

class KeyInput
{
private:
	static int NowKey[KEY_MAX];		//����̓��̓L�[
	static int OldKey[KEY_MAX];		//�O��̓��̓L�[
	static int NowMouse[MOUSE_MAX]; //����̓��̓L�[
	static int OldMouse[MOUSE_MAX]; //�O��̓��̓L�[
	static CURSOR Cursor;

public:
	//�p�b�h���̍X�V
	static void UpdateKey() {
		// ���̓L�[�擾
		for (int i = 0; i < KEY_MAX; i++) {
			OldKey[i] = NowKey[i];
			NowKey[i] = CheckHitKey(i);
		}
		//����(�}�E�X)�擾
		for (int i = 0; i < MOUSE_MAX; i++) {
			OldMouse[i] = NowMouse[i];
			if (GetMouseInput() == i)
			{
				NowMouse[i] = 1;
			}
			else
			{
				NowMouse[i] = 0;
			}
		}
		//�J�[�\���̎擾
		GetMousePoint(&Cursor.x, &Cursor.y);
	}
	//�{�^�����������u��
	static bool OnKey(int key) {
		return (NowKey[key] == 1 && OldKey[key] == 0);
	}

	//�{�^�����������u��
	static bool OnPresed(int key) {
		return (NowKey[key] == 1);

	}
	//�{�^�����������u��
	static bool OnRelease(int key) {
		return (NowKey[key] == 0 && OldKey[key] == 1);
	}

	//�}�E�X�������u��
	static bool OnMouse(int mouse) {
		return (NowMouse[mouse] == 1 && OldMouse[mouse] == 0);
	}

	//�}�E�X�������u��
	static bool OnPresedMouse(int mouse) {
		return (NowMouse[mouse] == 1);
	}

	//�}�E�X�������u��
	static bool OnReleaseMouse(int mouse) {
		return (NowMouse[mouse] == 0 && OldMouse[mouse] == 1);
	}

	static CURSOR GetMouseCursor()
	{
		return Cursor;
	}
};



