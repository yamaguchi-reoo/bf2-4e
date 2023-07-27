#include "Thunder.h"
#include "StageItem.h"
#include "DxLib.h"
#include "Fps.h"

Thunder::Thunder()
{
	//雷の画像読込
	LoadDivGraph("Source/Resource/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, thunder_cloud_image);
	LoadDivGraph("Source/Resource/images/Stage/Stage_ThunderAnimation.png", 6, 6, 1, 64, 64, thunder_image);
	//雷モドキ
	LoadDivGraph("Source/Resource/images/Stage/Stage_ThunderEffectAnimation.png", 3, 3, 1, 32, 32, thunder_effect_image);

	/*点滅の初期化*/
	cloud_anime_num = 0;			//雷雲
	thunder_anime_num = 0;			//雷
	thunder_effect_anime_num = 0;	//雷モドキ

	cloud_time = 0;
	const int thirty_seconds = 30000; // 30秒のミリ秒単位
}

Thunder::~Thunder()
{
}

void Thunder::Update()
{
	/*　点滅　アニメーション　*/
	//雷雲
	cloud_time += GetNowDrawScreenUpdateTime(); // フレーム間の時間を加算
	if (cloud_time >= thirty_seconds)
	{
		++cloud_time;
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
		// 30秒後の時間をリセット
		cloud_time = 0;
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

void Thunder::Draw() const
{
	//雷の描画
	DrawRotaGraph(480, 100, 1.0f, 0, thunder_cloud_image[cloud_anime_num], TRUE, TRUE);				//雲
	DrawRotaGraph(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//雷
	DrawRotaGraph(480, 180, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//雷モドキ

}
