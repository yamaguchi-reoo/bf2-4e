#pragma once
#include"BoxCollision.h"
class Fish:public BoxCollision
{
private:
	float fish_x;
	float fish_y;

	int fish_image[10];
	float fish_animation_count;
	int fish_flg;
	int fish_xmove_flg;
	int time;

	int now_image;							// 今から表示される画像
	//int next_image;

public:
	Fish();
	~Fish();

	void Update();
	void Draw()const;

	void PlayerEat();
	void FishReset();
};

