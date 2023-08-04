#include "Fish.h"
#include"DxLib.h"
#include"Player.h"

Fish::Fish()
{
	for (int i = 0; i < 10; i++) {
		fish_image[i];
	}
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, fish_image);

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
}

Fish::~Fish()
{

}

void Fish::Update()
{
	int rand = GetRand(10);
	//âEà⁄ìÆ
	if (fish_flg == 0)
	{
		location.x++;
		if (location.x >= 420)
		{
			fish_flg = 1;
		}
	}
	//ç∂à⁄ìÆ
	if (fish_flg == 1)
	{
		location.x--;
		if (location.x <= 160)
		{
			fish_flg = 0;
		}
	}

	if (fish_flg == 2) 
	{
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
			if (location.x <= 320) {
				location.x -= 0.5;
			}
			if (location.x >= 320) {
				location.x += 0.5;
			}
		}
		else if (fish_animation_count <= 120)
		{
			location.y += 1.5;

		}
		else if (fish_animation_count <= 140)
		{
			FishReset();
		}
	}
	if (fish_flg == 3)
	{
		fish_animation_count++;
		if (fish_animation_count <= 75)
		{
			now_image = fish_image[6];
			location.y -= 1.0;
		}
		else if (fish_animation_count <= 80)
		{
			now_image = fish_image[3];
			location.y += 0.5;

		}
		else if (fish_animation_count <= 85)
		{
			now_image = fish_image[4];
			location.y += 0.5;
		}
		else if (fish_animation_count <= 90)
		{
			now_image = fish_image[5];
			location.y += 0.5;
		}
		else if (fish_animation_count <= 95)
		{
			FishReset();
		}
	}
}

void Fish::Draw() const
{
	DrawGraph(location.x, location.y,now_image, TRUE);
	//DrawFormatString(10, 10, 0xffffff, "%d", fish_animation_count, TRUE);
	DrawFormatString(100, 20, 0xffffff, "%f",fish_animation_count, TRUE);
	DrawFormatString(200, 20, 0xffffff, "%f", location.y, TRUE);
	//DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, FALSE);
	DrawBox(location.x - (erea.width * erea.width_rate), location.y - (erea.height * erea.height_rate), location.x - (erea.width * erea.width_rate) + erea.width, location.y - (erea.height * erea.height_rate) + erea.height, 0xffffff, FALSE);

}

void Fish::FishReversalFlg()
{
	fish_flg = 2;
}
void Fish::FishReset()
{
	fish_animation_count = 0;
	fish_flg = 0;
	now_image = fish_image[0];
	location.y = 460;
}
void Fish::PlayerEat()
{
	fish_flg = 3;
	
}

int Fish::FishSpwn()
{
	int rand = GetRand(10);
	if (rand >= 0 && rand <= 3)
	{
		return 0;
	}
}
