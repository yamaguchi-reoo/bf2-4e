#include "Fish.h"
#include"DxLib.h"

Fish::Fish()
{
	for (int i = 0; i < 10; i++) {
		fish_image[i];
	}
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, fish_image);

	//location.x = 160;
	//location.y = 390;

	location.x = 240;
	location.y = 460;

	erea.width = 64;
	erea.height = 64;
	erea.width_rate = 0.0;
	erea.height_rate = 0.0;

	fish_animation_count = 0;

	fish_x = 160;
	fish_y = 390;
	fish_flg = 0;

	time = 0;
}

Fish::~Fish()
{

}

void Fish::Update()
{
	//if (location.x >= 160)
	//{
	//	location.x++;
	//}
	//if (location.x >= 416)
	//{
	//	location.x--;
	//}
	//
	if (fish_flg == 1) {
		fish_animation_count++;

		if (fish_animation_count <= 0)
		{
			now_image = fish_image[0];
		}
		else if (fish_animation_count <= 20)
		{
			now_image = fish_image[1];
		}
		else if (fish_animation_count <= 70)
		{
			now_image = fish_image[2];
			location.y -= 1.5;
		}
		else if (fish_animation_count <= 120)
		{
			location.y += 1.5;

		}
		else if (fish_animation_count <= 140)
		{
			fish_animation_count = 0;
			fish_flg = 0;
		}
	}
	
}

void Fish::Draw() const
{
	DrawGraph(location.x, location.y,now_image, TRUE);
	//DrawFormatString(10, 10, 0xffffff, "%d", fish_animation_count, TRUE);
	DrawFormatString(20, 20, 0xffffff, "%4d", time, TRUE);
	DrawFormatString(100, 20, 0xffffff, "%f",fish_animation_count, TRUE);
	DrawFormatString(200, 20, 0xffffff, "%f", location.y, TRUE);
	//DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, FALSE);
	DrawBox(location.x - (erea.width * erea.width_rate), location.y - (erea.height * erea.height_rate), location.x - (erea.width * erea.width_rate) + erea.width, location.y - (erea.height * erea.height_rate) + erea.height, 0xffffff, FALSE);

}

void Fish::PlayerEat()
{
	fish_flg = 1;
}
void Fish::FishReset()
{
}
