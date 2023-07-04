#pragma once

class Enemy
{
private:
	// 画像変数
	int enemy_pink_image[19];				// 桃色の敵の画像
	int enemy_green_image[19];				// 緑色の敵の画像
	int enemy_red_image[19];				// 赤色の敵の画像

public:
	Enemy();					// コンストラクタ
	~Enemy();					// デストラクタ
};

