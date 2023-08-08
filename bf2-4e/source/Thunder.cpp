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
	thunder_anime_num = 0;			//稲光
	thunder_effect_anime_num = 0;	//雷モドキ

	thunder_cloud_anime_frame = 0;

	is_thunder_shoot_ready = false;
	thunder_shoot_flg = false;

	//雲の座標の初期位置
	cloud_X = 300;
	cloud_Y = 70;

	//ボール
	location.x = (float)cloud_X;
	location.y = (float)cloud_Y;

	erea.height = 21;
	erea.width = 21;

	//角度処理
	BallAngle = 0;
	MoveX = 0;
	MoveY = 0;

	//ボールフラグ
	BallFlg = 0;

	//ボールのスピード
	//Speed = 3;

	//角度の初期化
	thunder_angle = 1;
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
	//雷モドキ
	if (thunder_effect_shoot_flg == true)
	{
		if (++thunder_effect_time_anime % 10 == 0)
		{
			if (thunder_effect_anime_num < 2)		//雷モドキのアニメーション
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

	// ボールの移動
	if (BallFlg != 2)
	{
		location.x += MoveX;
		location.y += MoveY;
	}

	// 壁・天井での反射
	if (location.x < 4 || location.x > 640 - erea.width)
	{
		// 横の壁
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
		// 上の壁
		BallAngle = (1 - BallAngle);
		ChangeAngle();
	}
	//if (location.y > 480 + 4)
	//{
	//	//ボールをスタート状態にする
	//	BallFlg = 2;
	//}
}

Thunder::~Thunder()
{

}

void Thunder::ChangeAngle()
{
	//角度の変更処理
	float rad = BallAngle * (float) M_PI * 2;
	MoveX = Speed*(float) cos(rad);
	MoveY = Speed*(float) sin(rad);
}

void Thunder::StartBall()
{
	BallFlg = 0;

	//移動量計算
	Speed = 3;
	BallAngle = 0.625f;
	ChangeAngle();
}

int Thunder::R_BallFlg()
{
	//ボールフラグ
	return BallFlg;
}

void Thunder::MoveBall()
{
	
	
}

void Thunder::Draw() const
{
	//雷雲の描画
	DrawRotaGraph(cloud_X, cloud_Y, 1.0f, 0, thunder_cloud_image[cloud_anime_num], TRUE, TRUE);				//雲

	//稲光の描画
	if (thunder_shoot_flg == true)
	{
		DrawRotaGraphF(480, 150, 1.0f, 0, thunder_image[thunder_anime_num], TRUE, TRUE);					//稲光
	}
	
	//雷モドキの描画
	if (thunder_effect_shoot_flg == true)
	{
		DrawRotaGraphF(location.x, location.y, 1.0f, 0, thunder_effect_image[thunder_effect_anime_num], TRUE, TRUE);	//雷モドキ
	}
}
