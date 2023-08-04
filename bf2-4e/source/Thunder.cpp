#include "Thunder.h"
#include "StageItem.h"
#include "DxLib.h"
#include "math.h"

Thunder::Thunder()
{
	//���̉摜�Ǎ�
	LoadDivGraph("Source/Resource/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, thunder_cloud_image);
	LoadDivGraph("Source/Resource/images/Stage/Stage_ThunderAnimation.png", 6, 6, 1, 64, 64, thunder_image);
	//�����h�L
	LoadDivGraph("Source/Resource/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, thunder_effect_image);

	/*�_�ł̏�����*/
	cloud_anime_num = 0;			//���_
	thunder_anime_num = 0;			//��
	thunder_effect_anime_num = 0;	//�����h�L

	thunder_cloud_anime_frame = 0;

	is_thunder_shoot_ready = false;
	thunder_shoot_flg = false;

	//�{�[��
	BallX = 320;
	BallY = 440 - 5;

	//�p�x����
	BallAngle = 0;
	MoveX = 0;
	MoveY = 0;

	//�{�[���̃X�s�[�h
	//Speed = 3;
}

Thunder::~Thunder()
{
}

void Thunder::Update()
{
	/*�@�_�Ł@�A�j���[�V�����@*/
	//���_
	if (--thunder_cloud_frame < 0)
	{
		is_thunder_shoot_ready = true;

		if (thunder_shoot_flg == false)
		{
			if (++thunder_cloud_anime_frame % 3 == 0)
			{
				if (cloud_anime_num < 2)		//���F�_�ƗΉ_�̃��[�v
				{
					cloud_anime_num++;
				}
				else
				{
					cloud_anime_num = 1;	//���F�_�ɖ߂�
				}
			}
		}
		else
		{
			cloud_anime_num = 0;
		}
		
		// 30�b��̎��Ԃ����Z�b�g
		//if(cloud_anime_frame = 0)
		//{
		//}
	}

	//���
	if (is_thunder_shoot_ready == true)
	{
		if (--thunder_frame < 0)
		{
			thunder_shoot_flg = true;
		}
	}

	if (thunder_shoot_flg == true)
	{
		if (++thunder_time_anime % 5 == 0)
		{
			if (thunder_anime_num < 5)		//����̃A�j���[�V����
			{
				thunder_anime_num++;

				thunder_shoot_flg = true;
			}
			else
			{
				thunder_shoot_flg = false;

				is_thunder_shoot_ready = false;
			}
		}
	}

	//�����h�L
	/*if (is_thunder_shoot_ready == true)
	{
		if (--thunder_frame < 0)
		{
			thunder_effect_shoot_flg = true;
		}
	}*/

	if (thunder_shoot_flg == true)
	{
		if (++thunder_effect_time_anime % 5 == 0)
		{
			if (thunder_effect_anime_num < 5)		//�����h�L�̃A�j���[�V����
			{
				thunder_effect_anime_num++;

				thunder_effect_shoot_flg = true;
			}
			else
			{
				thunder_effect_shoot_flg = false;

				is_thunder_effect_shoot_ready = false;
			}
		}
	}

}
void Thunder::ChangeAngle()
{
	//�p�x�̕ύX����
	float rad = BallAngle * (float)M_PI * 2;
	MoveX = (int)(Speed * cosf(rad));
	MoveY = (int)(Speed * sinf(rad));
}

void Thunder::MoveBall()
{
	// �{�[���̈ړ�
	if (BallFlg != 2)
	{
		BallX += MoveX;
		BallY += MoveY;
	}
	else
	{
		/*BallX = BarX + 30;
		BallY = BarY - 6;*/
	}

	// �ǁE�V��ł̔���
	if (BallX < 4 || BallX > 640 - 4)
	{ // ���̕�
		if (BallX < 4)
		{
			BallX = 4;
		}
		else
		{
			BallX = 640 - 4;
		}
		BallAngle = (1 - BallAngle) + 0.5f;
		if (BallAngle > 1) BallAngle -= 1.0f;
		ChangeAngle();
	}

	if (BallY < 8)
	{ // ��̕�
		BallAngle = (1 - BallAngle);
		ChangeAngle();
	}
	if (BallY > 480 + 4)
	{
		//�{�[�����X�^�[�g��Ԃɂ���
		BallFlg = 2;
	}
}

void Thunder::Draw() const
{
	//���̕`��
	DrawRotaGraph(480, 100, 1.0f, 0, thunder_cloud_image[cloud_anime_num], TRUE, TRUE);				//�_

	//����̕`��
	if (thunder_shoot_flg == true)
	{
		DrawRotaGraph(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//���
	}
	
	//�����h�L�̕`��
	if (thunder_effect_shoot_flg == true)
	{
		DrawRotaGraph(480, 180, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//�����h�L
	}
}
