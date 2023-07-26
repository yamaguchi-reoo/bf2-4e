#include "StageItem.h"
#include "DxLib.h"

StageItem::StageItem()
{
	//雷の画像読込
	LoadDivGraph("Source/Resource/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, thunder_cloud_image);
	LoadDivGraph("Source/Resource/images/Stage/Stage_ThunderAnimation.png", 6, 5, 1, 64, 64, thunder_image);
	//雷モドキ
	LoadDivGraph("Source/Resource/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, thunder_effect_image);

	/*点滅の初期化*/	
	cloud_anime_num = 0;			//雷雲
	thunder_anime_num = 0;			//雷
	thunder_effect_anime_num = 0;	//雷モドキ

}

StageItem::~StageItem()
{
}

void StageItem::Update()
{
	/*　点滅　アニメーション　*/
	//雷雲
	++cloud_time;
	if (cloud_time % 3 == 0)
	{
		cloud_anime_num = cloud_anime_num + 1;
	}
	else if (cloud_anime_num == 3)
	{
		cloud_anime_num = 1;
	}

	//雷
	++thunder_time;
	if (thunder_time % 10 == 0)
	{
		thunder_anime_num = thunder_anime_num + 1;
	}
	if (thunder_anime_num == 6)
	{
		thunder_anime_num = 0;
	}

	//雷モドキ
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

void StageItem::Draw() const
{
	//雷の描画
	DrawRotaGraph(480, 100, 1.0f, 0, thunder_cloud_image[cloud_anime_num], TRUE, TRUE);				//雲
	DrawRotaGraph(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//雷
	DrawRotaGraph(480, 180, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//雷モドキ

}
