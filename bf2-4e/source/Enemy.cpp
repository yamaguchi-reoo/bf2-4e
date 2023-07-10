#include "Enemy.h"
#include "DxLib.h"

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

	enemy_x = 32;
	enemy_y = 0;
	enemy_speed = 0;

	fps_count = 0;
	animation_pattern_number = 0;
	second = 0;

	inflat_bealloon_count = 0;

	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;
}

// デストラクタ
Enemy::~Enemy()
{

}

// 描画以外の更新を実装
void Enemy::Update()
{
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

// 描画に関することを実装
void Enemy::Draw() const
{
	// ステージ１に敵の画像の描画
	//DrawRotaGraph(200, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);

	switch (enemy_state)
	{
	case Enemy::EnemyState::kInflatBealloon:
		// 風船を膨らまし切ると浮き上がる
		DrawRotaGraph(200, 252 - enemy_y, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);
		break;
	case Enemy::EnemyState::kFlight:
		break;
	case Enemy::EnemyState::kParachute:
		break;
	case Enemy::EnemyState::kUpright:
		break;
	case Enemy::EnemyState::kDeath:
		break;
	default:
		break;
	}

	DrawFormatString(10, 10, 0xFFFFFF, "秒数%5d", second);

}

// 風船を膨らませるアニメーション処理
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	next_image = inflat_bealloon_count / 22;

	if (now_image != next_image)
	{
		now_image = next_image;
		animation_pattern_number = next_image;
	}

	if (inflat_bealloon_count >= 180 && enemy_y <= 20)
	{
		// 敵を浮上させる
		enemy_y++;

		// 浮上時の画像へ切り替え
		animation_pattern_number = 8;
	}
	else if(inflat_bealloon_count >= 180)
	{
		// カウントを0に戻す
		inflat_bealloon_count = 0;

		// 敵の状態遷移
		enemy_state = EnemyState::kFlight;
	}

}
