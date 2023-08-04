#pragma once
#include"BoxCollision.h"
class Fish:public BoxCollision
{
private:
	float fish_x;
	float fish_y;

	int fish_image[10];
	float fish_animation_count;//フレームレートカウント
	int fish_flg;		//0..右移動 1..左移動 2..浮上 3..プレイヤー喰らう

	int now_image;							// 今から表示される画像
	//int next_image;

public:
	Fish();
	~Fish();

	void Update();
	void Draw()const;

	void FishReversalFlg();
	void FishReset();
	void PlayerEat();

	int FishSpwn();
};

