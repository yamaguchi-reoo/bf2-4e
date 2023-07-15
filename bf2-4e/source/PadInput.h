#pragma once
#include"DxLib.h"

#define BUTTONS 16
#define STICKL_X 1		
#define STICKL_Y 2		
#define MAXL_X 32767.f  //���X�e�B�b�NX���̍ő�l(float�^)
#define MAXL_Y 32767.f  //���X�e�B�b�NY���̍ő�l(float�^)
//�X�e�B�b�N
struct Stick
{
	short ThumbX;	//�����l
	short ThumbY;	//�c���l
};

class PadInput
{
private:
	static char NowKey[BUTTONS]; //����̓��̓L�[
	static char OldKey[BUTTONS]; //�O��̓��̓L�[
	static XINPUT_STATE Input; //�p�b�h
	static Stick Rstick; //�E�X�e�B�b�N
	static Stick Lstick; //���X�e�B�b�N
public:
	//�p�b�h���̍X�V
	static void UpdateKey()
	{
		// ���̓L�[�擾
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &Input);
		for (int i = 0; i < BUTTONS; i++)
		{
			OldKey[i] = NowKey[i];
			NowKey[i] = Input.Buttons[i];
		}

		//���X�e�B�b�N
		Lstick.ThumbX = Input.ThumbLX;
		Lstick.ThumbY = Input.ThumbLY;
	}

	//�{�^���������ꂽ�u��
	static bool OnButton(int button)
	{
		bool ret = (NowKey[button] == 1 && OldKey[button] == 0);
		return ret;
	}

	//�{�^���������Ă��
	static bool OnPressed(int button)
	{
		bool ret = (NowKey[button] == 1);
		return ret;
	}

	//�{�^���𗣂����u��
	static bool OnRelease(int button)
	{
		bool ret = (NowKey[button] == 0 && OldKey[button] == 1);
		return ret;
	}

	//�X�e�B�b�N�̌X������
	static float TipLeftLStick(short StickL)
	{
		if (StickL == STICKL_X)
		{
			float ratioL_X = Input.ThumbLX / MAXL_X;

			//���X�e�B�b�N�̉������ő�l���P�Ƃ�������
			return ratioL_X;
		}
		else if (StickL == STICKL_Y)
		{
			float ratioL_Y = Input.ThumbLY / MAXL_Y;

			//���X�e�B�b�N�̏c���l�̍ő�l���P�Ƃ�������
			return ratioL_Y;
		}

		return 0;
	}
};

