#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "PadInput.h"		// デバッグ用

// 静的メンバ変数の定義
float Enemy::get_location_x;
float Enemy::get_location_y;


// 静的メンバ変数
//int Enemy::animation_count;
//EnemyState Enemy::enemy_state;

//float sinangle2 = 0;		// デバッグ用

// コンストラクタ
Enemy::Enemy(float set_x, float set_y, int set_type)
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
	
	// 敵の情報（構造体から）
	location.x = set_x;			// 中心座標X
	location.y = set_y;			// 中心座標Y
	erea.width = 45.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;

	enemy_speed = 0.1f;
	acceleration = 30.0f;						// 加速度
	enemy_type = set_type;
	power_up_flg = FALSE;
	enemy_death = FALSE;
	bound_flg = 0;							// 今は跳ね返らない状態
	levitation_flg = 0;						// 浮上しない

	// 移動するときの計算に使う変数
	xc = 0.0f;
	yc = 0.0f;
	x = 0.0f;
	y = 0.0f;

	// アニメーション用カウント
	inflat_bealloon_count = 0;
	//flight_count = 0;
	animation_count = 0;
	levitation_count = 0;

	// アニメーション用変数
	now_image = 0;
	next_image = 0;

	// 追いかける対象の座標
	player_x = 0.0f;
	player_y = 0.0f;

	// 移動するときに使う変数
	move_x = 0.0f;
	move_y = 0.0f;

	// 画像反転用
	turn_flg = FALSE;				// 反転はしない
	old_turn_flg = turn_flg;

	// 敵の強さ変更用
	ckeck_flg = TRUE;				// 座標の差を取得する
	ckeck_count = 0;

	// パラシュート用
	angle = 0.0f;
	angle2 = 0.0f;
	amplitude = 50.0f;
	enemy_start_x = -100.0f;

	// 回避行動用変数
	avoidance_count = 0;
	avoidance_flg = FALSE;						// 回避行動のフラグ
	difference_y = 0.0f;

	enemy_state = EnemyState::kInflatBealloon;			// 敵の状態

	get_location_x = 0.0f;
	get_location_y = 0.0f;
}

// デストラクタ
Enemy::~Enemy()
{

}

// 描画以外の更新を実装
void Enemy::Update()
{
	/****************************
	* ↓デバッグ用
	*****************************/

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

	// LBボタン
	// Xボタン
	if (PadInput::OnButton(XINPUT_BUTTON_X) == 1)
	{
		enemy_state = EnemyState::kParachute;
	}

	/****************************
	* ↓ここから敵の処理
	*****************************/
	switch (enemy_state)
	{
		case EnemyState::kInflatBealloon:
			// 風船を膨らませるアニメーション処理
			InflatBealloon();
			break;
		case EnemyState::kFlight:
			// 空中で羽ばたくアニメーション処理
			Flight();
			//AirFall();
			if (levitation_flg == 1)
			{
				// 敵の浮上
				Levitation();
			}
			else
			{
				// 敵の上下左右移動処理
				EnemyMove();
				//Avoidance();
				//CkeckPlayerLocation();
				//AirFall();
			}
			if (bound_flg == 1)
			{
				// 敵の跳ね返り（仮）
				Bound();
			}
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

	get_location_x = location.x;
	get_location_y = location.y;
}

// 描画に関することを実装
void Enemy::Draw() const
{
#if _DEBUG
	DrawFormatString(0, 130, 0xffffff, "E location.x = %3f, location.y = %3f", location.x, location.y);
	//DrawFormatString(0, 80, 0xffffff, "E move_x = %3f, move_y = %3f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E x = %3f, y = %3f", x, y);
	//DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "E state = %d", enemy_state);
	//DrawFormatString(20, 150, 0xffffff, "E enemy_speed = %f", enemy_speed);
	//DrawFormatString(20, 250, 0xff0000, "E enemy_state = %d", enemy_state);
	//DrawFormatString(20, 150, 0xff0000, "E bound_flg = %d", bound_flg);
	//DrawFormatString(20, 200, 0xff0000, "E avoidance_flg = %d", avoidance_flg);
	//DrawFormatString(20, 200, 0xff0000, "E turn_flg = %d", turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E old_turn_flg = %d", old_turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E enemy_life = %d", enemy_life);
#endif	//_DEBUG

	if (enemy_type == 0)
	{
		// 桃色の敵画像の描画
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		// 画面の端に行ったら反対側にも描画
		if (location.x <= 32)
		{
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
	else if (enemy_type == 1)
	{
		// 緑色の敵画像の描画
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		// 画面の端に行ったら反対側にも描画
		if (location.x <= 32)
		{
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		}
	}
	else
	{
		// 赤色の敵画像の描画
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		// 画面の端に行ったら反対側にも描画
		if (location.x <= 32)
		{
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		}
	}

	// 敵の当たり判定範囲
	//DrawBox(location.x - (erea.width * erea.width_rate), location.y - (erea.height * erea.height_rate), location.x - (erea.height * erea.height_rate) + erea.width, location.y - (erea.height * erea.height_rate) + erea.height, 0xffff00, FALSE);
	
	//DrawBox(location.x - (erea.width / 2 * erea.width_rate), location.y - (erea.height / 2 * erea.height_rate), location.x - (erea.width / 2 * erea.width_rate) + erea.width, location.y - (erea.height / 2 * erea.height_rate) + erea.height, 0xffff00, FALSE);
	//
	//// 風船部分
	//DrawBox(location.x - (erea.width / 2 * erea.width_rate), location.y - (erea.width / 2 * erea.height_rate), location.x - (erea.width / 2 * erea.height_rate) + erea.width, location.y, 0xff0000, FALSE);
	//// 体部分
	//DrawBox(location.x - (erea.width / 2 * erea.width_rate), location.y, location.x - (erea.width / 2 * erea.height_rate) + erea.width, location.y - (erea.height / 2 * erea.height_rate) + erea.height, 0x00ffff, FALSE);
}

// 敵の上下左右移動処理
void Enemy::EnemyMove()
{
	// プレイヤーの座標参照
	player_x = Player::get_location_x;
	player_y = Player::get_location_y;

	// 回避行動の条件用
	difference_y = location.y - player_y;

	// 回避行動の条件
	if (avoidance_flg == FALSE && location.y > player_y && difference_y <= 70 && player_x >= location.x - 20 && player_x <= location.x + 20)
	{
		//avoidance_flg = TRUE;
	}

	//else
	//{
	//	avoidance_flg = FALSE;
	//}

	if (avoidance_flg == TRUE)
	{
		// 敵の回避行動処理
		Avoidance();
	}
	else
	{
		// プレイヤーと敵の座標の差を求める
		x = player_x - location.x;
		y = player_y - location.y;

		xc = sqrtf(powf(x, 2));
		yc = sqrtf(powf(y, 2));

		// x,y座標が同じだと1ピクセルずつ追いかけてくる
		if (xc != 0 && yc != 0)
		{
			// どの向きに進めばいいのかを-1～1の間で求めている（多分）
			move_x = x / xc;
			move_y = y / yc;
		}

		if (x >= 0)
		{
			// 左を向く
			turn_flg = TRUE;
		}
		else
		{
			// 右を向く
			turn_flg = FALSE;
		}

		// 加速の処理
		if (old_turn_flg == turn_flg)
		{
			// 加速度の影響を速度に与える
			enemy_speed += acceleration / 3600;

			// 敵のタイプによって最高速度が変わる
			if (enemy_type == 0 && enemy_speed >= 0.5f)
			{
				enemy_speed = 0.5f;
			}
			else if (enemy_type == 1 && enemy_speed >= 0.8f)
			{
				enemy_speed = 0.8f;
			}
			else if (enemy_type == 2 && enemy_speed >= 1.0f)
			{
				enemy_speed = 1.0f;
			}
			else if(enemy_speed <= 0.0f)
			{
				enemy_speed = 0.0f;
			}
		}

		// 減速の処理
		if (old_turn_flg != turn_flg/*&& enemy_speed >= 0.0f*/)
		{
			move_x *= -1.0f;
			// 加速度の影響を速度に与える
			enemy_speed -= acceleration / 3600;

			if (enemy_speed <= 0.0f)
			{
				enemy_speed = 0.0f;
				old_turn_flg = turn_flg;
			}
		}

		// 敵の移動
		location.x += move_x * enemy_speed;
		location.y += move_y * enemy_speed / 2;
	}	
}

// 敵の回避行動処理
void Enemy::Avoidance()
{
	avoidance_count++;
	if (avoidance_count <= 120)
	{
		location.x += move_x * enemy_speed;
	}
	else
	{
		avoidance_count = 0;
		avoidance_flg = FALSE;
	}
	
	//avoidance_count++;
	////if (avoidance_count <= 120)
	////{
	//	//if (turn_flg == TRUE)
	//	//{
	//		// 敵が右を向いているとき
	//		// enemy_x += move_x * speed　にする必要がある
	//		location.x += move_x * enemy_speed;
	////	}
	//	//else if (turn_flg == FALSE)
	//	//{
	//	//	// 敵が左を向いているとき
	//	//	// enemy_x -= move_x * speed　にする必要がある
	//	//	location.x -= enemy_speed;
	//	//}
	////}
	////else
	////{
	////	avoidance_count = 0;
	////	avoidance_flg = FALSE;
	////}
}

// 風船を膨らませるアニメーション処理
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22フレームごとに画像を切り替える（0 ～ 7の8枚）
	next_image = inflat_bealloon_count / 22;

	if (inflat_bealloon_count <= 180 && now_image < 7)
	{
		// 3秒間風船を膨らませるアニメーション
		if (now_image != next_image)
		{
			now_image = next_image;
		}
	}
	else
	{
		levitation_flg = 1;
		inflat_bealloon_count = 0;

		// 敵の状態遷移
		// デバッグ用
		//enemy_state = EnemyState::kDeath;

		enemy_state = EnemyState::kFlight;
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
		enemy_start_x = location.x;
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

	angle++;
	angle2 = angle * (float)(M_PI / 180);

	//sinangle2 = sinf(angle2);

	// enemu_start_xを中心に左右に揺れる処理
	location.x = (sinf(angle2) * amplitude) + enemy_start_x;
	// 落下処理
	location.y += 0.5f;
}

// 直立状態の処理
void Enemy::Upright()
{
	if (enemy_start_x != -100.0f)
	{
		angle = 0;
		animation_count = 0;
		enemy_start_x = -100.0f;
	}

	// 直立状態の画像
	now_image = 0;

	// 敵が赤色ではないとき
	if (enemy_type <= 3)
	{
		// パワーアップのフラグを立てる
		power_up_flg = TRUE;
	}

	// 約3秒表示
	if (++animation_count >= 180)
	{
		// 膨らませきったらパワーアップ
		enemy_state = EnemyState::kInflatBealloon;
		animation_count = 0;
	}
}

// 死亡時のアニメーション処理
void Enemy::Death()
{
	// 画像は13, 14（2枚）
	animation_count++;

	if (animation_count <= 4)
	{
		now_image = 13;
		//enemy_life = FALSE;
		//enemy_delete = TRUE;
	}
	else if (animation_count <= 8)
	{
		now_image = 14;
	}
	else
	{
		animation_count = 0;
	}

	// 敵の落下
	if (move_y <= 20)
	{
		move_y++;
		// 少し上に上がる
		location.y--;
	}
	else
	{
		location.y++;
	}

	// 現在の座標 + enemy_y >= 480 にする必要がある
	if (location.y >= 480)
	{
		 enemy_death = FALSE;
	}
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
	if (location.x <= -32)
	{
		location.x = 608;
	}
	else if (location.x >= 672)
	{
		location.x = 32;
	}
}

// 敵の跳ね返り
void Enemy::Bound()
{
	//location.x += move_x * -1.0f;
	//location.y += move_y * -1.0f;

	location.x += move_x * enemy_speed;

	//move_x *= -1.0f;
	// 加速度の影響を速度に与える
	//enemy_speed -= acceleration / 3600;

	//if (enemy_speed <= 0.0f)
	//{
	//	enemy_speed = 0.0f;
	//	//old_turn_flg = turn_flg;
	//	bound_flg = 0;
	//}

	////location.x += move_x * enemy_speed * -1.0f;
	//location.x += move_x * enemy_speed;
}

// フラグの設定
void Enemy::SetBoundFlg(int set_flg)
{
	bound_flg = set_flg;
}

// 敵の浮上
void Enemy::Levitation(void)
{
	// パワーアップ処理
	if (power_up_flg == TRUE)
	{
		// タイプの変更
		enemy_type++;

		// 初速度の設定
		enemy_speed = 0.1f;

		power_up_flg = FALSE;
	}

	levitation_count++;

	if (levitation_count <= 30)
	{
		location.y -= enemy_speed;
	}
	else
	{
		levitation_flg = 0;
		levitation_count = 0;
	}
}

// 敵の浮上フラグの設定
void Enemy::SetLevitationFlg(int set_flg)
{
	levitation_flg = set_flg;
}

int Enemy::GetEnemyDeathFlg()
{
	return enemy_death;
}


//シャボン玉スポーン時の敵の状態からの判断するための処理
bool Enemy::EnemyStateJudgment(void)
{
	int ret = false;

	//死亡時とパラシュート時のみtrue
	if ((enemy_state == EnemyState::kDeath) || (enemy_state == EnemyState::kParachute)) 
	{
		if (location.y > 450) 
		{
			ret = true;
		}
		
	}

	return ret;
}
