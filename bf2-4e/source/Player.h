#pragma once
#include "Collision.h"

class Player :public BoxCollider
{
private:
	int player_images[30];
	int player_flg; //0:�n�ʂɂ����ԁ@�P�F�������
	float player_x1;
	float player_y1;
	float player_x2;
	float player_y2;

public:
	void PlayerFlight();
	void PlayerFall();	//�v���C���[�̗�������
	void PlayerGroundWalk();	//�v���C���[�̒n�ʂł̓���

public:
	Player();			//�R���X�g���N�^
	~Player();			//�f�X�g���N�^	
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;	//�`��Ɋւ��邱�Ƃ���������
};