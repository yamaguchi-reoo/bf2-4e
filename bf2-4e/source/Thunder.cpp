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
	thunder_anime_num = 0;			//���
	thunder_effect_anime_num = 0;	//�����h�L

	thunder_cloud_anime_frame = 0;

	is_thunder_shoot_ready = false;
	thunder_shoot_flg = false;

	//�_�̍��W�̏����ʒu
	cloud_X = 300;
	cloud_Y = 70;

	//�{�[��
	location.x = (float)cloud_X;
	location.y = (float)cloud_Y;

	erea.height = 21;
	erea.width = 21;

	//�p�x����
	BallAngle = 0;
	MoveX = 0;
	MoveY = 0;

	//�{�[���t���O
	BallFlg = 0;

	//�{�[���̃X�s�[�h
	//Speed = 3;

	//�p�x�̏�����
	thunder_angle = 1;
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

				//thunder_shoot_flg = true;
			}
			else
			{

				thunder_effect_shoot_flg = true;

				is_thunder_shoot_ready = false;

				thunder_shoot_flg = false;

				thunder_cloud_frame = 60;
			}
		}
	}
	//�����h�L
	if (thunder_effect_shoot_flg == true)
	{
		if (++thunder_effect_time_anime % 10 == 0)
		{
			if (thunder_effect_anime_num < 2)		//�����h�L�̃A�j���[�V����
			{
				thunder_effect_anime_num++;
			}
			else
			{
				thunder_effect_anime_num = 1;
			}
		}	
		Speed = 3;
		BallFlg = 0;
		

		switch (thunder_angle)
		{
		case 1:
			BallAngle = 0.625f;
			ChangeAngle();
			break;

		default:
			break;
		}
	}

	// �{�[���̈ړ�
	if (BallFlg != 2)
	{
		location.x += MoveX;
		location.y += MoveY;
	}

	// �ǁE�V��ł̔���
	if (location.x < 4 || location.x > 640 - erea.width)
	{
		// ���̕�
		if (location.x < 4)
		{
			location.x = 4;
		}
		else
		{
			location.x = 640 - erea.width;
		}
		BallAngle = (1 - BallAngle) + 0.5f;
		if (BallAngle > 1) BallAngle -= 1.0f;
		/*ChangeAngle();*/
	}

	if (location.y < 0)
	{
		location.y = 0;
		// ��̕�
		BallAngle = (1 - BallAngle);
		ChangeAngle();
	}
	//if (location.y > 480 + 4)
	//{
	//	//�{�[�����X�^�[�g��Ԃɂ���
	//	BallFlg = 2;
	//}
}

Thunder::~Thunder()
{

}

void Thunder::ChangeAngle()
{
	//�p�x�̕ύX����
	float rad = BallAngle * (float) M_PI * 2;
	MoveX = Speed*(float) cos(rad);
	MoveY = Speed*(float) sin(rad);
}

void Thunder::StartBall()
{
	BallFlg = 0;

	//�ړ��ʌv�Z
	Speed = 3;
	BallAngle = 0.625f;
	ChangeAngle();
}

int Thunder::R_BallFlg()
{
	//�{�[���t���O
	return BallFlg;
}

void Thunder::MoveBall()
{
	
	
}

void Thunder::Draw() const
{
	//���_�̕`��
	DrawRotaGraph(cloud_X, cloud_Y, 1.0f, 0, thunder_cloud_image[cloud_anime_num], TRUE, TRUE);				//�_

	//����̕`��
	if (thunder_shoot_flg == true)
	{
		DrawRotaGraphF(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//���
	}
	
	//�����h�L�̕`��
	if (thunder_effect_shoot_flg == true)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//�����h�L
	}
}
