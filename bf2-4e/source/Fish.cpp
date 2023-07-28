#include "Fish.h"
#include"DxLib.h"

Fish::Fish()
{
	//for (int i; i < 10; i++) {
	//	fish_image[i];
	//}
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_FishAnimation.png", 10, 5, 2, 64, 64, fish_image);

	location.x = 100;
	location.y = 450;

	erea.width = 45.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;

	fish_animation_count = 0;
	fish_time = 0;
}

Fish::~Fish()
{
}

void Fish::Update()
{
	fish_animation_count++;

	if (fish_animation_count <= 10)
	{
		now_image=fish_image[0];
	}
	else if (fish_animation_count <= 20)
	{
		now_image = fish_image[1];
	}
	else if (fish_animation_count <= 30)
	{
		now_image = fish_image[2];
		location.y -=3.4 ;
	}
	else if(fish_animation_count<=80)
	{
		location.y+=2;
	}
}

void Fish::Draw() const
{
	DrawRotaGraph(240, location.y, 1, 0,now_image, TRUE);
	DrawFormatString(10, 10, 0xffffff, "%d", fish_animation_count, TRUE);
	DrawFormatString(20, 20, 0xffffff, "%4f", location.y , TRUE);
}
