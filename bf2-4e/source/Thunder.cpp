#include "Thunder.h"
#include "StageItem.h"
#include "DxLib.h"
#include "Fps.h"

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
	++thunder_effect_time;
	if (thunder_effect_time % 2 == 0)
	{
		thunder_effect_anime_num = thunder_effect_anime_num + 1;
	}
	if (thunder_effect_anime_num == 3)
	{
		thunder_effect_anime_num = 0;
	}

}

void Thunder::Draw() const
{
	//���̕`��
	DrawRotaGraph(480, 100, 1.0f, 0, thunder_cloud_image[cloud_anime_num], TRUE, TRUE);				//�_
	if (thunder_shoot_flg == true)
	{
		DrawRotaGraph(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//���
	}
	DrawRotaGraph(480, 180, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//�����h�L

}
