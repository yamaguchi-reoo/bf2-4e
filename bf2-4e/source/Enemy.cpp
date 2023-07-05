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

	fps_count = 0;
	animation_pattern_number = 0;
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
		// fpsのカウントを0に戻す
		fps_count = 0;
	}

	// 風船を膨らませるアニメーション処理
	InflatBealloon();
}

// 描画に関することを実装
void Enemy::Draw() const
{
	// ステージ１に敵の画像の描画
	DrawRotaGraph(200, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);
	DrawRotaGraph(300, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);
	DrawRotaGraph(400, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);

}

// 風船を膨らませるアニメーション処理
void Enemy::InflatBealloon()
{
	if (fps_count <= 30)
	{
		animation_pattern_number = 1;
	}
	else
	{
		animation_pattern_number = 0;
	}
}
