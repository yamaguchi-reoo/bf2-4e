#pragma once
#include"BoxCollision.h"
#include"common.h"

class StageFloor :public BoxCollision
{
private:

	//�摜�p�ϐ�
	int floor_image01;
public:
	//�R���X�g���N�^
	StageFloor(int i);
	//�f�X�g���N�^
	~StageFloor();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

