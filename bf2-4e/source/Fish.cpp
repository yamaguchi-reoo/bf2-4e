#include "Fish.h"
#include"DxLib.h"

Fish::Fish()
{
	for (int i = 0; i < 10; i++) {
		fish_image[i];
	}
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, fish_image);

	location.x = 160;
	location.y = 390;

	erea.width = 320;
	erea.height = 52;
	erea.width_rate = 0.0;
	erea.height_rate = 0.0;

	fish_animation_count = 0;
	fish_time = 0;
	second = 0;

	fish_x = 100;
	fish_y = 450;
}

Fish::~Fish()
{
}

void Fish::Update()
{
	if (fish_y > 470)
	{
		fish_y = 470;
	}
}

void Fish::Draw() const
{
	DrawRotaGraph(240, fish_y, 1, 0,now_image, TRUE);
	//DrawFormatString(10, 10, 0xffffff, "%d", fish_animation_count, TRUE);
	DrawFormatString(20, 20, 0xffffff, "%4f", fish_y, TRUE);
	DrawBox(location.x - (erea.width * erea.width_rate), location.y - (erea.height * erea.height_rate), location.x - (erea.width * erea.width_rate) + erea.width, location.y - (erea.height * erea.height_rate) + erea.height, 0xffffff, FALSE);
	DrawFormatString(10, 10, 0xFFFFFF, "E �b��%5d", second);
}

void Fish::PlayerEat()
{

	fish_animation_count++;

	if (fish_animation_count <= 20)
	{
		now_image = fish_image[0];
	}
	else if (fish_animation_count <= 40)
	{
		now_image = fish_image[1];
	}
	else if (fish_animation_count <= 60)
	{
		now_image = fish_image[2];
		fish_y -= 1.7;
	}
	else if (fish_animation_count <= 80)
	{
		fish_y += 1.7;
	}
	else if (fish_animation_count <= 100)
	{
		fish_animation_count = -100;
	}
}
void Fish::FishReset()
{
	//fish_y += 1.7;
}
