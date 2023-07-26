#include "Thunder.h"
#include "StageItem.h"
#include "DxLib.h"


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

	cloud_time = 0;

}

Thunder::~Thunder()
{
}

void Thunder::Update()
{
	/*�@�_�Ł@�A�j���[�V�����@*/
	//���_
	//++cloud_time;
	if (++cloud_time % 3 == 0)
	{
		if (cloud_anime_num < 2)
		{
			cloud_anime_num++;
		}
		else
		{
			cloud_anime_num = 1;
		}
	}


	//��
	++thunder_time;
	if (thunder_time % 10 == 0)
	{
		thunder_anime_num = thunder_anime_num + 1;
	}
	if (thunder_anime_num == 6)
	{
		thunder_anime_num = 0;
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
	DrawRotaGraph(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//��
	DrawRotaGraph(480, 180, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//�����h�L

}
