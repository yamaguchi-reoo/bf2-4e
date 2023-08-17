#include "Fish.h"
#include"DxLib.h"
#include"Player.h"

Fish::Fish()
{
	for (int i = 0; i < 10; i++) {
		fish_image[i];
	}
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, fish_image);

	now_image = 0;
	location.x = 100;
	location.y = 383;

	erea.width = 64;
	erea.height = 40;
	erea.width_rate = 0.0;
	erea.height_rate = 0.0;

	fish_animation_count = 0;
	fish_eat_animation_count = 0;

	fish_x = 240;
	fish_y = 383;
	fish_flg = 0;

	eat_image = 0;

}

Fish::~Fish()
{

}

void Fish::Update()
{
	location.x = Player::get_location_x - 30;

	if (fish_flg == 2) 
	{	
		fish_animation_count++;
		if (fish_animation_count < 0)
		{
			now_image = 0;
		}
		else if (fish_animation_count < 10)
		{
			now_image = 1;
		}
		else if (fish_animation_count < 20)
		{
			now_image = 2;
			if (location.x <= 320) {
				location.x -= 0.5;
			}
			if (location.x >= 320) {
				location.x += 0.5;
			}
		}
		else if (fish_animation_count <= 30)
		{
			now_image = 1;
		}
		else if (fish_animation_count <= 40)
		{
			now_image = 0;
		}
		else if (fish_animation_count <= 50)
		{
			FishReset();
		}
	}
	if (fish_flg == 3)
	{
		fish_eat_animation_count++;
		if (fish_eat_animation_count < 10)
		{
			eat_image = 6;
		}
		else if (fish_eat_animation_count < 20)
		{
			eat_image = 3;
		}
		else if (fish_eat_animation_count < 30)
		{
			eat_image = 4;
		}
		else if (fish_eat_animation_count < 40)
		{
			eat_image = 5;
		}
		else if (fish_eat_animation_count < 100)
		{
			FishReset();
		}
	}
	
}

void Fish::Draw() const
{
	if (fish_flg == 2) {
		DrawGraph((int)location.x, (int)location.y, fish_image[now_image], TRUE);
		//DrawBox(location.x - (erea.width * erea.width_rate), location.y - (erea.height * erea.height_rate), location.x - (erea.width * erea.width_rate) + erea.width, location.y - (erea.height * erea.height_rate) + erea.height, 0xffffff, FALSE);
	}if (fish_flg == 3) {
		DrawGraph(location.x, location.y, fish_image[eat_image], TRUE);
		//DrawBox(location.x - (erea.width * erea.width_rate), location.y - (erea.height * erea.height_rate), location.x - (erea.width * erea.width_rate) + erea.width, location.y - (erea.height * erea.height_rate) + erea.height, 0xffffff, FALSE);
	}
	//DrawFormatString(10, 10, 0xffffff, "%d", fish_animation_count, TRUE);
	/*DrawFormatString(100, 20, 0xffffff, "%d",fish_animation_count, TRUE);
	DrawFormatString(200, 20, 0xffffff, "%f", location.y, TRUE);*/
	//DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, FALSE);
	

}

void Fish::FishReversalFlg()
{
	fish_flg = 2;
}
void Fish::FishReset()
{
	fish_animation_count = 0;
	fish_eat_animation_count = 0;
	fish_flg = 0;
	now_image = 10;
	eat_image = 0;
	location.y = 383;
}
void Fish::PlayerEat()
{
	fish_flg = 3;
}
int Fish::GetCount()
{
	return fish_animation_count;
}

int Fish::GetFlg()
{
	return fish_flg;
}
