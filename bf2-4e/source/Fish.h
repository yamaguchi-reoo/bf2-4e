#pragma once
#include"BoxCollision.h"
class Fish:public BoxCollision
{
private:
	float fish_x;
	float fish_y;

	int fish_image [10] ;
	int fish_animation_count;//�t���[�����[�g�J�E���g
	int fish_eat_animation_count;
	int fish_flg;//0..�E�ړ� 1..���ړ� 2..���� 3..�v���C���[��炤
	int eat_image;

	int now_image;							// ������\�������摜
	//int next_image;

public:
	Fish();
	~Fish();

	void Update();
	void Draw()const;

	void FishReversalFlg();
	void FishReset();
	void PlayerEat();

	int GetCount();
	int GetFlg();
	int FishSpawn();
};

