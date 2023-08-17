#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

// 静的メンバ変数の定義
float Enemy::get_location_x;
float Enemy::get_location_y;

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
	location.x = set_x;							// 中心座標X
	location.y = set_y;							// 中心座標Y
	erea.width = 45.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;

	enemy_speed = 0.0f;							// 初速度
	acceleration = 30.0f;						// 加速度
	bounce_coefficient = 0.8f;					// 反発係数
	enemy_type = set_type;						// 敵の種類（0：桃色　1：緑色　2：赤色）
	power_up_flg = FALSE;						// パワーアップのフラグ（TRUE:パワーアップする　FALSE:パワーアップしない）
	enemy_death = FALSE;						// 敵の生死状態（TRUE:死亡　FALSE:生存）
	enemy_delete = FALSE;						// 敵の削除（TRUE:削除）
	bound_flg = FALSE;							// 敵の跳ね返り状態（TRUE:跳ね返る　FALSE:跳ね返らない）
	levitation_flg = FALSE;						// 敵の浮上（TRUE:浮上する）

	// 移動するときの計算用変数
	abs_x = 0.0f;								// X座標の絶対値
	abs_y = 0.0f;								// Y座標の絶対値
	distance_x = 0.0f;							// X座標の距離
	distance_y = 0.0f;							// Y座標の距離

	// アニメーション用カウント
	inflat_bealloon_count = 0;					// 風船を膨らましきるまでのカウント
	animation_count = 0;						// アニメーション用カウント
	levitation_count = 0;						// 浮上するカウント

	// アニメーション用変数
	now_image = 0;								// 今から表示される画像
	next_image = 0;								// 次に表示される画像

	// 追いかける対象の座標
	player_x = 0.0f;							// プレイヤーのX座標
	player_y = 0.0f;							// プレイヤーのY座標

	// 移動量変数
	move_x = 1.0f;								// 敵の座標Xの移動量
	move_y = 1.0f;								// 敵の座標Yの移動量

	// 画像反転用
	turn_flg = FALSE;							// 画像の左右反転状態（TRUE:反転　FALSE:反転しない）
	old_turn_flg = turn_flg;					// 前回の画像の状態を保持

	// パラシュート用
	angle = 0.0f;								// パラシュート状態の左右移動用
	angle2 = 0.0f;								// パラシュート状態の左右移動用
	amplitude = 50.0f;							// パラシュート状態で下降するときの振れ幅
	enemy_start_x = -100.0f;					// パラシュート状態になったx座標

	// 回避行動用変数
	avoidance_count = 0;						// 回避時間
	avoidance_flg = FALSE;						// 回避行動のフラグ（TRUE:回避行動開始）
	difference_y = 0.0f;						// 回避行動の条件用のプレイヤーと敵の座標の差

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
	switch (enemy_state)
	{
		case EnemyState::kInflatBealloon:
			// 風船を膨らませるアニメーション処理
			InflatBealloon();
			break;
		case EnemyState::kFlight:
			if (bound_flg == TRUE)
			{
				// 空中落下アニメーション処理
				AirFall();
				// 敵の跳ね返り（仮）
				BoundDown();
			}
			else
			{
				// 空中で羽ばたくアニメーション処理
				Flight();
				if (levitation_flg == TRUE)
				{
					// 敵の浮上
					Levitation();
				}

				else if (avoidance_flg == TRUE)
				{
					Avoidance();
				}
				else
				{
					// 敵の上下左右移動処理
					EnemyMove();
					//CkeckPlayerLocation();
				}
			}
			break;
		case EnemyState::kParachute:
			avoidance_flg = FALSE;
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

	// 天井に当たったら跳ね返る
	if (location.y - (erea.width / 2 * erea.height_rate) <= 0)
	{
		move_y = 1.0f;
		bound_flg = TRUE;
	}

	get_location_x = location.x;
	get_location_y = location.y;
}

// 描画に関することを実装
void Enemy::Draw() const
{
#if _DEBUG
	//DrawFormatString(0, 130, 0xffffff, "E location.x = %f, location.y = %f", location.x, location.y);
	//DrawFormatString(0, 110, 0xffffff, "E move_x = %f, move_y = %f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E 距離 distance_x = %f, distance_y = %f", distance_x, distance_y);
	//DrawFormatString(0, 150, 0xffffff, "E 向き abs_x = %f, abs_y = %f", abs_x, abs_y);
	//DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "E state = %d", enemy_state);
	//DrawFormatString(0, 150, 0xffffff, "E enemy_speed = %f", enemy_speed);
	//DrawFormatString(20, 250, 0xff0000, "E difference_y = %f", difference_y);
	//DrawFormatString(20, 150, 0xff0000, "E levitation_flg = %d", levitation_flg);
	//DrawFormatString(20, 200, 0xff0000, "E avoidance_flg = %d", avoidance_flg);
	//DrawFormatString(20, 200, 0xff0000, "E turn_flg = %d", turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E old_turn_flg = %d", old_turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E enemy_death = %d", enemy_death);
	//DrawFormatString(0, 200, 0xff0000, "E bound_flg = %d", bound_flg);
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
}

// 敵の上下左右移動処理
void Enemy::EnemyMove()
{
	// プレイヤーの座標参照
	player_x = Player::get_location_x;
	player_y = Player::get_location_y;

	// プレイヤーと敵の座標の差を求める
	distance_x = player_x - location.x;
	distance_y = player_y - location.y;

	// プレイヤーと敵の座標の絶対値を求める
	abs_x = fabsf(distance_x);
	abs_y = fabsf(distance_y);

	if (abs_x != 0 && abs_y != 0)
	{
		// 進む方向
		move_x = distance_x / abs_x;
		move_y = distance_y / abs_y;
	}

	if (move_x >= 0)
	{
		// 左を向く
		turn_flg = TRUE;
	}
	else
	{
		// 右を向く
		turn_flg = FALSE;
	}

	// 慣性の処理
	Inertia();

	// 敵の移動
	location.x += move_x * enemy_speed;
	location.y += move_y * enemy_speed / 2;

	// 回避行動の条件用
	difference_y = location.y - player_y;

	// 回避行動の条件
	if (avoidance_flg == FALSE && location.y > player_y && difference_y <= 70 && player_x >= location.x - 20 && player_x <= location.x + 20)
	{
		avoidance_flg = TRUE;
	}
}

// 敵の回避行動処理
void Enemy::Avoidance()
{
	avoidance_count++;
	if (avoidance_count <= 120)
	{
		// 慣性の処理
		Inertia();

		// 敵の移動
		location.x += move_x * enemy_speed;
	}
	else
	{
		avoidance_count = 0;
		avoidance_flg = FALSE;
	}	
}

// 慣性の処理
void Enemy::Inertia()
{
	// 加速の処理
	if (old_turn_flg == turn_flg)
	{
		// 加速度の影響を速度に与える
		enemy_speed += acceleration / 3600;

		// 敵のタイプによって最高速度が変わる
		if (enemy_type == 0 && enemy_speed >= 0.5f)
		{
			// ピンク
			enemy_speed = 0.5f;
		}
		else if (enemy_type == 1 && enemy_speed >= 0.8f)
		{
			// 緑
			enemy_speed = 0.8f;
		}
		else if (enemy_type == 2 && enemy_speed >= 1.0f)
		{
			// 赤
			enemy_speed = 1.0f;
		}
	}

	// 減速の処理
	if (old_turn_flg != turn_flg)
	{
		if (levitation_flg == TRUE)
		{
			// 浮上フラグの設定
			levitation_flg = FALSE;
		}

		move_x *= -1.0f;
		// 加速度の影響を速度に与える
		enemy_speed -= acceleration / 3600;

		if (enemy_speed <= 0.0f)
		{
			enemy_speed = 0.0f;
			old_turn_flg = turn_flg;
		}
	}
}

// 風船を膨らませる処理
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22フレームごとに画像を切り替える（0 ～ 7の8枚）
	next_image = inflat_bealloon_count / 22;

	if (inflat_bealloon_count <= 180 && now_image < 7)
	{
		// 風船を膨らませるアニメーション
		if (now_image != next_image)
		{
			now_image = next_image;
		}
	}
	else
	{
		inflat_bealloon_count = 0;

		// 敵の状態遷移
		enemy_state = EnemyState::kFlight;
	}
}

// 空中で羽ばたくアニメーション処理
void Enemy::Flight()
{
	animation_count++;

	// 画像番号は8, 9（2枚）
	next_image = (animation_count / 6) + 8;

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
	animation_count++;
	
	// 画像は10, 11, 12（風船が揺れている3枚）
	next_image = (animation_count / 11) + 10;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (animation_count >= 30)
	{
		animation_count = 0;
	}
}

// パラシュート状態の処理
void Enemy::Parachute()
{
	if (enemy_start_x == -100.0f)
	{
		// パラシュート状態になったx座標の保持
		enemy_start_x = location.x;
		// 落下速度の設定
		enemy_speed = 0.5f;
	}

	animation_count++;

	// 画像は15, 16, 17
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

	// enemu_start_xを中心に左右に揺れる処理
	location.x = (sinf(angle2) * amplitude) + enemy_start_x;

	// 落下処理
	location.y += enemy_speed;

	// 水中に沈んだら死亡
	if (location.y >= 480)
	{
		enemy_death = TRUE;
		enemy_delete = TRUE;
	}
}

// 直立状態の処理
void Enemy::Upright()
{
	if (enemy_start_x != -100.0f)
	{
		// パラシュート状態用の変数の初期値代入
		angle = 0;
		enemy_start_x = -100.0f;
		animation_count = 0;
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
		animation_count = 0;
		// 敵の状態遷移
		enemy_state = EnemyState::kInflatBealloon;
	}
}

// 死亡時の処理
void Enemy::Death()
{
	// 画像は13, 14（2枚）
	animation_count++;

	// 死亡時のアニメーション
	if (animation_count <= 4)
	{
		now_image = 13;
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
	if (move_y <= 10)
	{
		move_y++;
		// 少し上に上がる
		location.y--;
	}
	else
	{
		location.y++;
	}

	// 水中に沈んだらゲームメインで削除
	if (location.y >= 480)
	{
		 enemy_delete = TRUE;
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

// 下方向に跳ね返る
void Enemy::BoundDown()
{
	// 減速
	// 加速度の影響を速度に与える
	enemy_speed -= acceleration / 3600;
	
	// 敵の移動
	location.x += move_x * enemy_speed * bounce_coefficient;
	location.y += move_y * enemy_speed * bounce_coefficient;

	if (enemy_speed <= 0.0f)
	{
		enemy_speed = 0.0f;
		bound_flg = FALSE;
	}
}

// フラグの設定
void Enemy::SetBoundFlg(int set_flg)
{
	bound_flg = set_flg;
}

// 敵の浮上処理
void Enemy::Levitation(void)
{
	// パワーアップ処理
	if (power_up_flg == TRUE)
	{
		// タイプの変更
		enemy_type++;

		// 初速度の設定
		enemy_speed = 0.0f;

		power_up_flg = FALSE;
	}

	levitation_count++;

	if (levitation_count <= 180)
	{
		// 天井に当たったら跳ね返る
		if (location.y - (erea.width / 2 * erea.height_rate) <= 0)
		{
			move_y = 1.0f;
			bound_flg = TRUE;
			levitation_flg = FALSE;
		}

		// 慣性の処理
		Inertia();

		// 敵の移動
		location.x += move_x * enemy_speed;
		location.y -= move_y * enemy_speed / 2;
	}
	else
	{
		levitation_flg = FALSE;
		levitation_count = 0;
	}
}

// 敵の浮上フラグの設定
void Enemy::SetLevitationFlg(int set_flg)
{
	levitation_flg = set_flg;
}

// 敵の死亡フラグの取得
int Enemy::GetEnemyDeathFlg()
{
	return enemy_death;
}

// 敵の死亡フラグの設定
void Enemy::SetEnemyDeathFlg(int flg)
{
	enemy_death = flg;
}

// 敵の削除フラグの取得
int Enemy::GetEnemyDeleteFlg()
{
	return enemy_delete;
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
