#include "StageItem.h"
#include "DxLib.h"

StageItem::StageItem()
{
	//���̉摜�Ǎ�
	LoadDivGraph("Source/Resource/images/Stage/Stage_CloudAnimation.png", 3, 2, 1, 128, 64, thunder_cloud_image);
	LoadDivGraph("Source/Resource/images/Stage/Stage_ThunderAnimation.png", 6, 5, 1, 64, 64, thunder_image);

	//���̓_�ł̏�����	
	anime_num = 0;
}

StageItem::~StageItem()
{
}

void StageItem::Update()
{
	//���̓_��
	++time;
	if (time % 3 == 0) 
	{
		anime_num = anime_num + 1;
	}
	if (anime_num == 3)
	{
		anime_num = 0;
	}

}

void StageItem::Draw() const
{
	//���_�̕`��
	DrawRotaGraph(150, 180, 1.0f, 0, thunder_cloud_image[anime_num], TRUE, 0);
	DrawRotaGraph(150, 150, 1.0f, 0, thunder_image[anime_num], TRUE, TRUE);

}
