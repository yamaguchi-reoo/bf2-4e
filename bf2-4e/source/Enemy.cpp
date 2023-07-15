#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

// コンストラクタ
Enemy::Enemy()
{
	for (int i = 0; i < 18; i++)
	{
		enemy_pink_image[i];
		enemy_green_image[i];
		enemy_red_image[i];
	}
	// 敵の画像の読込
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, enemy_pink_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, enemy_green_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, enemy_red_image);
	
	// 敵の情報
	enemy_x = 200.0f;
	enemy_y = 252.0f;
	enemy_speed = 1.0f;
	enemy_angle = 0;
	enemy_type = 0;
	power_up_flg = FALSE;

	// 移動するときの計算に使う変数
	xc = 0.0f;
	yc = 0.0f;
	x = 0.0f;
	y = 0.0f;

	fps_count = 0;
	second = 0;

	// アニメーション用カウント
	inflat_bealloon_count = 0;
	flight_count = 0;

	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;

	// 追いかける対象の座標
	mouse_x = 0;
	mouse_y = 0;

	radian = 0.0f;
	degree = 0.0f;

	// 移動するときに使う変数
	move_x = 0.0f;
	move_y = 0.0f;

	turn_flg = FALSE;
}

// デストラクタ
Enemy::~Enemy()
{

}

// 描画以外の更新を実装
void Enemy::Update()
{
	// マウスの座標の取得（のちにプレイヤーの座標に変わる）
	GetMousePoint(&mouse_x, &mouse_y);

	fps_count++;

	if (fps_count >= 60)
	{
		// 秒数のカウントを増やす
		second++;

		// fpsのカウントを0に戻す
		fps_count = 0;
	}

	switch (enemy_state)
	{
		case EnemyState::kInflatBealloon:
			// 風船を膨らませるアニメーション処理
			InflatBealloon();
			break;
		case EnemyState::kFlight:
			// 敵の上下左右移動処理
			EnemyMove();
			// 空中で羽ばたくアニメーション処理
			//Flight();
			AirFall();
			break;
		case EnemyState::kParachute:
			// パラシュート状態のアニメーション処理
			Parachute();
			break;
		case EnemyState::kUpright:
			// 直立状態の処理
			Upright();
			break;
		case EnemyState::kDeath:
			// 死亡時のアニメーション処理
			Death();
			break;
		default:
			break;
	}

}

// 描画に関することを実装
void Enemy::Draw() const
{
#if _DEBUG
	// 秒数の描画
	DrawFormatString(10, 10, 0xFFFFFF, "E 秒数%5d", second);

	//SetFontSize(15);
	//// マウスの座標の描画
	////DrawFormatString(10, 50, 0xffffff, "mouse_x = %3d, mouse_y = %3d", mouse_x, mouse_y);
	//DrawFormatString(0, 30, 0xffffff, "E enemy_x = %3f, enemy_y = %3f", enemy_x, enemy_y);
	DrawFormatString(0, 80, 0xffffff, "E move_x = %3f, move_y = %3f", move_x, move_y);
	DrawFormatString(0, 130, 0xffffff, "E x = %3f, y = %3f", x, y);
	DrawFormatString(0, 160, 0xffffff, "E xc = %3f, yc = %3f", xc, yc);
	DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "radian = %f", radian);
	DrawFormatString(200, 250, 0xff0000, "degree = %f", degree);
#endif	//_DEBUG

	if (enemy_type == 0)
	{
		// 桃色の敵画像の描画
		DrawRotaGraph((int)enemy_x, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
	}
	if (enemy_type == 1)
	{
		//// 緑色の敵画像の描画
		//DrawRotaGraph((int)enemy_x , (int)enemy_y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
	}
	if (enemy_type == 2)
	{
		//// 赤色の敵画像の描画
		//DrawRotaGraph((int)enemy_x , (int)enemy_y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
	}
}

// 敵の上下左右移動処理
void Enemy::EnemyMove()
{
	// マウスと敵の角度を計算する（弧度法）
	radian = atan2f((float)mouse_y - enemy_y, (float)mouse_x - enemy_x);
	// デグリーに変換
	degree = radian * (180 / M_PI);

	move_x = mouse_x - enemy_x;
	move_y = mouse_y - enemy_y;

	xc = sqrtf(powf(move_x, 2));
	yc = sqrtf(powf(move_y, 2));

	// x,y座標が同じだと1ピクセルずつ追いかけてくる（縦と横にしか移動しない）※多分改善した
	// 最短距離ではない
	if (xc != 0 && yc != 0)
	{
		// どの向きに進めばいいのかを-1〜1の間で求めている（多分）
		x = move_x / xc;
		y = move_y / yc;
	}

	// スピードをかけて移動速度を変更させないといけない
	enemy_x += x * enemy_speed;
	enemy_y += y;

	// 画像の反転処理（カーソルの方向を向く）
	if (x >= 0)
	{
		turn_flg = TRUE;
	}
	else
	{
		turn_flg = FALSE;
	}

	//if (y == 1)
	//{
	//	// 空中落下アニメーション処理
	//	AirFall();
	//}

}

// 敵の回避行動処理
void Enemy::Avoidance()
{
	// if(敵の真上にプレイヤーがいる場合)
	// (x >= degree && degree <= x) x = 角度の範囲を設定する

	if (turn_flg == TRUE)
	{
		// 敵が右を向いているとき
		// enemy_x += move_x * speed　にする必要がある
		move_x++;
	}
	else if (turn_flg == FALSE)
	{
		// 敵が左を向いているとき
		// enemy_x -= move_x * speed　にする必要がある
		move_x--;
	}
}

// 風船を膨らませるアニメーション処理
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22フレームごとに画像を切り替える（0 〜 7の8枚）
	next_image = inflat_bealloon_count / 22;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	//// 敵の浮上処理
	//if (inflat_bealloon_count >= 180 && move_y >= 20)
	//{
	//	// 敵を浮上させる
	//	move_y++;
	//	enemy_y -= move_y;
	//}

	if(inflat_bealloon_count >= 180)
	{
		// 3秒経ったら
		// カウントを0に戻す
		inflat_bealloon_count = 0;

		// 敵の状態遷移
		enemy_state = EnemyState::kFlight;
	}

	// if(パワーアップのフラグが立っていたら)type++
	// パワーアップ処理
	if (power_up_flg == TRUE)
	{
		// タイプの変更
		enemy_type++;

		// スピードの変更
		enemy_speed++;

		// power_up_flg = FALSE;
	}

}

// 空中で羽ばたくアニメーション処理
void Enemy::Flight()
{
	flight_count++;

	// 画像番号は8, 9（2枚）
	next_image = flight_count / 6 + 8;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (flight_count >= 10)
	{
		// カウントを0に戻す
		flight_count = 0;
	}
}

// 空中落下アニメーション処理
void Enemy::AirFall()
{
	// 画像は10, 11, 12（風船が揺れている3枚）

	flight_count++;

	next_image = flight_count / 11 + 10;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (flight_count >= 30)
	{
		// カウントを0に戻す
		flight_count = 0;
	}

}

// パラシュート状態のアニメーション処理
void Enemy::Parachute()
{
	// 画像は15, 16, 17（2枚）
	// 15, 16はパラシュートが開く画像
	// 17は落下時の画像

	//power_up_flg = TRUE;

	// if(地面についたら)直立状態に変更
	enemy_state = EnemyState::kUpright;
}

// 直立状態の処理
void Enemy::Upright()
{
	// 直立状態の画像
	now_image = 0;

	// 敵が赤色ではないとき
	if (enemy_type <= 3)
	{
		// パワーアップのフラグを立てる
		power_up_flg = TRUE;
	}

	// if(一定時間たったら)風船を膨らませる状態に変更
	// 膨らませきったらパワーアップ
	enemy_state = EnemyState::kInflatBealloon;

	// パワーアップ処理
	//if (enemy_type <= 3)
	//{
	//	enemy_type++;
	//}
}

// 死亡時のアニメーション処理
void Enemy::Death()
{
	// 画像は13, 14（2枚）

	now_image = 13;

	//next_image = 

	// 敵の落下
	enemy_y++;
	// 現在の座標 + enemy_y >= 480 にする必要がある
	//if (enemy_y >= 480)
	//{

	//}
}
