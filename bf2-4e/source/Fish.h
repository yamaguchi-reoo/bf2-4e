#pragma once
#include"BoxCollision.h"
class Fish:public BoxCollision
{
private:
	int fish_image[10];
	int fish_animation_count;
	int fish_time;

	int now_image;							// ������\�������摜
	int next_image;

public:
	Fish();
	~Fish();

	void Update();
	void Draw()const;
};

