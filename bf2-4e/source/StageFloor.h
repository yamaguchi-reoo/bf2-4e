#pragma once
#include"BoxCollision.h"
#include"common.h"

class StageFloor :public BoxCollision
{
private:

	//�摜�p�ϐ�
	int floor_image01;
	int sea_image;
	int stage_number;
public:
	//�R���X�g���N�^
	StageFloor(int i, int _stage);
	//�f�X�g���N�^
	~StageFloor();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

