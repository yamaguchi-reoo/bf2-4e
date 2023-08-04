#include "Thunder.h"
#include "StageItem.h"
#include "DxLib.h"
#include "math.h"

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

	thunder_cloud_anime_frame = 0;

	is_thunder_shoot_ready = false;
	thunder_shoot_flg = false;

	//ボール
	BallX = 320;
	BallY = 440 - 5;

	//角度処理
	BallAngle = 0;
	MoveX = 0;
	MoveY = 0;

	//ボールのスピード
	//Speed = 3;
}

Thunder::~Thunder()
{
}

void Thunder::Update()
{
	/*　点滅　アニメーション　*/
	//雷雲
	if (--thunder_cloud_frame < 0)
	{
		is_thunder_shoot_ready = true;

		if (thunder_shoot_flg == false)
		{
			if (++thunder_cloud_anime_frame % 3 == 0)
			{
				if (cloud_anime_num < 2)		//黄色雲と緑雲のループ
				{
					cloud_anime_num++;
				}
				else
				{
					cloud_anime_num = 1;	//黄色雲に戻す
				}
			}
		}
		else
		{
			cloud_anime_num = 0;
		}
		
		// 30秒後の時間をリセット
		//if(cloud_anime_frame = 0)
		//{
		//}
	}

	//稲光
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
			if (thunder_anime_num < 5)		//稲光のアニメーション
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

	//雷モドキ
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
			if (thunder_effect_anime_num < 5)		//雷モドキのアニメーション
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
	//角度の変更処理
	float rad = BallAngle * (float)M_PI * 2;
	MoveX = (int)(Speed * cosf(rad));
	MoveY = (int)(Speed * sinf(rad));
}

void Thunder::MoveBall()
{
	// ボールの移動
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

	// 壁・天井での反射
	if (BallX < 4 || BallX > 640 - 4)
	{ // 横の壁
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
	{ // 上の壁
		BallAngle = (1 - BallAngle);
		ChangeAngle();
	}
	if (BallY > 480 + 4)
	{
		//ボールをスタート状態にする
		BallFlg = 2;
	}
}

void Thunder::Draw() const
{
	//雷の描画
	DrawRotaGraph(480, 100, 1.0f, 0, thunder_cloud_image[cloud_anime_num], TRUE, TRUE);				//雲

	//稲光の描画
	if (thunder_shoot_flg == true)
	{
		DrawRotaGraph(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//稲光
	}
	
	//雷モドキの描画
	if (thunder_effect_shoot_flg == true)
	{
		DrawRotaGraph(480, 180, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//雷モドキ
	}
}
