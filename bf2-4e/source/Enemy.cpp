#include "Enemy.h"
#include "DxLib.h"
#include <math.h>

// コンストラクタ
Enemy::Enemy()
{
	for (int i = 0; i < 19; i++)
	{
		enemy_pink_image[i];
		enemy_green_image[i];
		enemy_red_image[i];
	}
	// 敵の画像の読込
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_P_Animation.png", 19, 8, 3, 64, 64, enemy_pink_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_G_Animation.png", 19, 8, 3, 64, 64, enemy_green_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_R_Animation.png", 19, 8, 3, 64, 64, enemy_red_image);

	enemy_x = 200;
	enemy_y = 252;
	enemy_speed = 0;
	enemy_angle = 0;

	xc = 0.0f;
	yc = 0.0f;
	x = 0;
	y = 0;

	fps_count = 0;
	second = 0;

	inflat_bealloon_count = 0;

	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;

	mouse_x = 0;
	mouse_y = 0;

	radian = 0.0f;

	move_x = 0;
	move_y = 0;

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
			EnemyMove();
			Flight();
			break;
		case EnemyState::kParachute:
			Parachute();
			break;
		case EnemyState::kUpright:
			Upright();
			break;
		case EnemyState::kDeath:
			Death();
			break;
		default:
			break;
	}

}

// 描画に関することを実装
void Enemy::Draw() const
{
	// 秒数の描画
	DrawFormatString(10, 10, 0xFFFFFF, "秒数%5d", second);

	SetFontSize(15);
	// マウスの座標の描画
	//DrawFormatString(10, 50, 0xffffff, "mouse_x = %3d, mouse_y = %3d", mouse_x, mouse_y);
	DrawFormatString(10, 150, 0xffffff, "enemy_x = %3d, enemy_y = %3d", enemy_x, enemy_y);
	DrawFormatString(10, 200, 0xffffff, "move_x = %3d, move_y = %3d", move_x, move_y);
	DrawFormatString(10, 250, 0xffffff, "x = %3d, y = %3d", x, y);
	//DrawFormatString(200, 250, 0xff0000, "今c = %f", c);
	DrawFormatString(200, 250, 0xff0000, "radian = %f", radian);



	// 桃色の敵画像の描画
	//DrawRotaGraph(200 + enemy_x, 252 + enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, FALSE);

	// 桃色の敵画像の描画
	//DrawRotaGraph(enemy_x, enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);

	switch (enemy_state)
	{
	case EnemyState::kInflatBealloon:
		// 風船を膨らまし切ると浮き上がる
		DrawRotaGraph(enemy_x, enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		break;
	case EnemyState::kFlight:
		//DrawRotaGraph(200 + move_x, 252 + move_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		DrawRotaGraph(enemy_x, enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		break;
	case EnemyState::kParachute:
		break;
	case EnemyState::kUpright:
		break;
	case EnemyState::kDeath:
		break;
	default:
		break;
	}

}

// 敵の上下左右移動処理
void Enemy::EnemyMove()
{
	// マウスと敵の角度を計算する（弧度法）
	radian = atan2f((float)mouse_y - (float)enemy_y, (float)mouse_x - (float)enemy_x);

	move_x = mouse_x - enemy_x;
	move_y = mouse_y - enemy_y;

	xc = sqrtf(pow((float)move_x, 2));
	yc = sqrtf(pow((float)move_y, 2));

	// x,y座標が同じだと1ピクセルずつ追いかけてくる（縦と横にしか移動しない）
	if (xc != 0 && yc != 0)
	{
		x = move_x / (int)xc;
		y = move_y / (int)yc;
	}

	enemy_x += x;
	enemy_y += y;

}

// 敵の回避行動処理
void Enemy::Avoidance()
{
	if (turn_flg == TRUE)
	{
		// 敵が右を向いているとき
		move_x++;
	}
	else if (turn_flg == FALSE)
	{
		// 敵が左を向いているとき
		move_x--;
	}
}

// 風船を膨らませるアニメーション処理
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22フレーム毎に画像を切り替える
	next_image = inflat_bealloon_count / 22;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	// 敵の浮上処理
	if (inflat_bealloon_count >= 180 && move_y >= 20)
	{
		// 敵を浮上させる
		move_y++;
		enemy_y -= move_y;
	}
	else if(inflat_bealloon_count >= 180)
	{
		// 3秒経ったら
		// カウントを0に戻す
		inflat_bealloon_count = 0;

		// 敵の状態遷移
		enemy_state = EnemyState::kFlight;
	}

}

// 空中で羽ばたくアニメーション処理
void Enemy::Flight()
{

}

// パラシュート状態のアニメーション処理
void Enemy::Parachute()
{

}

// 直立状態の処理
void Enemy::Upright()
{
	// 直立状態の画像
	now_image = 0;
}

// 死亡時のアニメーション処理
void Enemy::Death()
{
	now_image = 13;

	//next_image = 

	// 敵の落下
	enemy_y++;
	// 現在の座標 + enemy_y >= 480 にする必要がある
	//if (enemy_y >= 480)
	//{

	//}
}
