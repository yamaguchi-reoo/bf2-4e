#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "PadInput.h"		// デバッグ用

// 静的メンバ変数
//int Enemy::animation_count;

float angle = 0;
float angle2;
float sinangle2 = 0;		// デバッグ用

// コンストラクタ
Enemy::Enemy()
{
	player = new Player;

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
	enemy_x = 608.0f;			// デバッグ用
	//enemy_y = 32.0f;				// デバッグ用
	//enemy_x = 200.0f;
	enemy_y = 252.0f;
	enemy_speed = 0.5f;
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
	//inflat_bealloon_count = 0;
	//flight_count = 0;
	animation_count = 0;

	avoidance_count = 0;

	// アニメーション用変数
	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;

	// 追いかける対象の座標
	mouse_x = 0;
	mouse_y = 0;

	// 移動するときに使う変数
	move_x = 0.0f;
	move_y = 0.0f;

	turn_flg = FALSE;				// 反転はしない

	ckeck_flg = TRUE;				// 座標の差を取得する
	ckeck_count = 0;

	amplitude = 50.0f;
	enemy_start_x = -100.0f;

	avoidance_flg = FALSE;						// 回避行動のフラグ

	difference_y = 0.0f;
}

// デストラクタ
Enemy::~Enemy()
{

}

// 描画以外の更新を実装
void Enemy::Update()
{
	// 敵の色ごとの動作確認用　※後で削除
	// RBボタン
	if (PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER) == 1)
	{
		if (enemy_type < 2)
		{
			enemy_type++;

		}
		else
		{
			enemy_type = 0;
		}
	}

	// 敵の色ごとの動作確認用　※後で削除
	// LBボタン
	if (PadInput::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) == 1)
	{
		// デバッグ用
		enemy_state = EnemyState::kParachute;
	}

	// マウスの座標の取得（のちにプレイヤーの座標に変わる）
	GetMousePoint(&mouse_x, &mouse_y);

	// 後で消すやつ
	fps_count++;
	if (fps_count >= 60)
	{
		// 秒数のカウントを増やす
		second++;
		// fpsのカウントを0に戻す
		fps_count = 0;
	}

	// ↓ここから敵の処理
	switch (enemy_state)
	{
		case EnemyState::kInflatBealloon:
			// 風船を膨らませるアニメーション処理
			InflatBealloon();
			break;
		case EnemyState::kFlight:
			// 敵の上下左右移動処理
			EnemyMove();
			//Avoidance();
			//CkeckPlayerLocation();
			// 空中で羽ばたくアニメーション処理
			Flight();
			//AirFall();
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

	// X座標のワープをした後の座標変更処理
	AfterWarp();
}

// 描画に関することを実装
void Enemy::Draw() const
{
#if _DEBUG
	// 秒数の描画
	DrawFormatString(10, 10, 0xFFFFFF, "E 秒数%5d", second);

	//SetFontSize(15);
	//// マウスの座標の描画
	DrawFormatString(10, 50, 0xffffff, "mouse_x = %3d, mouse_y = %3d", mouse_x, mouse_y);
	DrawFormatString(0, 30, 0xffffff, "E enemy_x = %3f, enemy_y = %3f", enemy_x, enemy_y);
	DrawFormatString(0, 80, 0xffffff, "E move_x = %3f, move_y = %3f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E x = %3f, y = %3f", x, y);
	//DrawFormatString(0, 160, 0xffffff, "E xc = %3f, yc = %3f", xc, yc);
	//DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "E state = %d", enemy_state);
	//DrawFormatString(200, 250, 0xff0000, "E angle2 = %f", angle2);
	//DrawFormatString(200, 250, 0xff0000, "E enemy_start_x = %f", enemy_start_x);
	//DrawFormatString(200, 250, 0xff0000, "E sinangle2 = %f", sinangle2);
	//DrawFormatString(200, 250, 0xff0000, "E a = %f", difference_y);
	//DrawFormatString(20, 250, 0xff0000, "E avoidance_flg = %d", avoidance_flg);
#endif	//_DEBUG

	if (enemy_type == 0)
	{
		// 桃色の敵画像の描画
		DrawRotaGraph((int)enemy_x, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		// 画面の端に行ったら反対側にも描画
		if (enemy_x <= 32)
		{
			DrawRotaGraph((int)enemy_x + 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (enemy_x >= 608)
		{
			DrawRotaGraph((int)enemy_x - 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
	else if (enemy_type == 1)
	{
		// 緑色の敵画像の描画
		DrawRotaGraph((int)enemy_x , (int)enemy_y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		// 画面の端に行ったら反対側にも描画
		if (enemy_x <= 32)
		{
			DrawRotaGraph((int)enemy_x + 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (enemy_x >= 608)
		{
			DrawRotaGraph((int)enemy_x - 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
	//else if (enemy_type == 2)
	else
	{
		// 赤色の敵画像の描画
		DrawRotaGraph((int)enemy_x , (int)enemy_y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		// 画面の端に行ったら反対側にも描画
		if (enemy_x <= 32)
		{
			DrawRotaGraph((int)enemy_x + 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (enemy_x >= 608)
		{
			DrawRotaGraph((int)enemy_x - 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
}

// 敵の上下左右移動処理
void Enemy::EnemyMove()
{
	difference_y = enemy_y - (float)mouse_y;

	// 回避行動の条件
	if (avoidance_flg == FALSE && enemy_y > mouse_y && difference_y <= 70 && mouse_x >= enemy_x - 32 && mouse_x <= enemy_x + 32)
	//if(enemy_y > mouse_y && difference_y <= 50)
	{
		avoidance_flg = TRUE;
	}

	if (avoidance_flg == TRUE)
	{
		avoidance_count++;
		if (avoidance_count <= 120)
		{
			// 敵の回避行動
			//if (mouse_x >= enemy_x - 30 && mouse_x <= enemy_x + 30)
			//{
				if (turn_flg == TRUE)
				{
					// 敵が右を向いているとき
					// enemy_x += move_x * speed　にする必要がある
					enemy_x++;
				}
				else if (turn_flg == FALSE)
				{
					// 敵が左を向いているとき
					// enemy_x -= move_x * speed　にする必要がある
					enemy_x--;
				}
			//}
		}
		else
		{
			avoidance_count = 0;
			avoidance_flg = FALSE;
		}
	}
	else
	{
		//player->location.x

		// マウスと敵の座標の差を求める
		move_x = (float)mouse_x - enemy_x;
		move_y = (float)mouse_y - enemy_y;

		xc = sqrtf(powf(move_x, 2));
		yc = sqrtf(powf(move_y, 2));

		// x,y座標が同じだと1ピクセルずつ追いかけてくる（縦と横にしか移動しない）※多分改善した
		// 最短距離ではない
		if (xc != 0 && yc != 0)
		{
			// どの向きに進めばいいのかを-1～1の間で求めている（多分）
			x = move_x / xc;
			y = move_y / yc;
		}

		// スピードをかけて移動速度を変更させないといけない
		enemy_x += x * enemy_speed;
		enemy_y += y * enemy_speed / 2;

		// 画像の反転処理（カーソルの方向を向く）
		if (x >= 0)
		{
			turn_flg = TRUE;
		}
		else
		{
			turn_flg = FALSE;
		}
	}	
}

// 敵の回避行動処理
void Enemy::Avoidance()
{

	//	if (avoidance_count <= 120)
	//	{
	//		if (turn_flg == TRUE)
	//		{
	//			// 敵が右を向いているとき
	//			// enemy_x += move_x * speed　にする必要がある
	//			move_x++;
	//		}
	//		else if (turn_flg == FALSE)
	//		{
	//			// 敵が左を向いているとき
	//			// enemy_x -= move_x * speed　にする必要がある
	//			move_x--;
	//		}
	//	}
	//	else
	//	{
	//		avoidance_count = 0;
	//	}
	//}
	//avoidance_flg = FALSE;

}

// 風船を膨らませるアニメーション処理
void Enemy::InflatBealloon()
{
	animation_count++;

	// 22フレームごとに画像を切り替える（0 ～ 7の8枚）
	next_image = animation_count / 22;

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

	if(animation_count >= 180)
	{
		// 3秒経ったら
		// カウントを0に戻す
		animation_count = 0;

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
	animation_count++;

	// 画像番号は8, 9（2枚）
	next_image = animation_count / 6 + 8;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (animation_count >= 10)
	{
		// カウントを0に戻す
		animation_count = 0;
	}
}

// 空中落下アニメーション処理
void Enemy::AirFall()
{
	// 画像は10, 11, 12（風船が揺れている3枚）

	animation_count++;

	next_image = animation_count / 11 + 10;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (animation_count >= 30)
	{
		// カウントを0に戻す
		animation_count = 0;
	}

}

// パラシュート状態のアニメーション処理
void Enemy::Parachute()
{
	if (enemy_start_x == -100.0f)
	{
		// enemy_start_xが使われていなかったら
		enemy_start_x = enemy_x;
	}

	animation_count++;

	// 画像は15, 16, 17（2枚）
	// 15, 16はパラシュートが開く画像
	// 17は落下時の画像
	if (animation_count <= 5)
	{
		now_image = 15;
	}
	else if (animation_count <= 8)
	{
		now_image = 16;
	}
	else
	{
		now_image = 17;
	}

	//next_image

	angle++;
	angle2 = angle * (float)(M_PI / 180);

	sinangle2 = sinf(angle2);

	// enemu_start_xを中心に左右に揺れる処理
	enemy_x = (sinf(angle2) * amplitude) + enemy_start_x;
	// 落下処理
	enemy_y += 0.5f;


	// if(地面についたら)直立状態に変更
	//power_up_flg = TRUE;
	// enemy_start_x = -100.0f;
	// animation_count = 0;
	//enemy_state = EnemyState::kUpright;
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

// プレイヤーとの座標の差を取得するかの判定処理
void Enemy::CkeckPlayerLocation()
{
	ckeck_count++;

	if (ckeck_flg == FALSE)
	{
		if (enemy_type == 0 && ckeck_count >= 300)
		{
			// 桃色の敵は5秒ごとに座標の比較
			ckeck_flg = TRUE;
			ckeck_count = 0;
		}
		else if (enemy_type == 1 && ckeck_count >= 180)
		{
			// 緑色の敵は3秒ごとに座標の比較
			ckeck_flg = TRUE;
			ckeck_count = 0;
		}
		else if(enemy_type == 2 && ckeck_count >= 60)
		{
			// 赤色の敵は1秒ごとに座標の比較
			ckeck_flg = TRUE;
			ckeck_count = 0;
		}
	}
}

// X座標のワープをした後の座標変更処理
void Enemy::AfterWarp()
{
	if (enemy_x <= -32)
	{
		enemy_x = 608;
	}
	if (enemy_x >= 672)
	{
		enemy_x = 32;
	}
}
