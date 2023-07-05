#include "Enemy.h"
#include "DxLib.h"

// コンストラクタ
Enemy::Enemy()
{
    // 初期化処理
    try
    {
        //画像読込
        LoadDivGraph("source/Resource/images/Enemy/Enemy_G_Animation.png", 19, 8, 3, 32, 32, enemy_pink_image);

        ////LogoImage = LoadGraph("source/Resource/images/Title/Title_Logo.png");
        //if (enemy_pink_image == -1)
        //{
        //    throw "source/Resource/images/Title/Title_Logo.png";
        //}
    }
    catch (int& err)
    {
        printf("エラーコード%d\n", err);
    }

    if (LoadDivGraph("images/block.bmp", 19, 8, 3, 32, 32, enemy_pink_image) == -1);


}

// デストラクタ
Enemy::~Enemy()
{

}

// 描画以外の更新を実装
void Enemy::Update()
{

}

// 描画に関することを実装
void Enemy::Draw() const
{

}
