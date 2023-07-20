#pragma once
#include "BoxCollision.h"

class Player :public BoxCollision
{
private:
	int player_images[30];
	int player_flg; //0:�n�ʂɂ����ԁ@�P�F�������
	int direction;	// �v���C���[�̌���

	int move_x;
	int move_y;
	int player_angle;

public:
	void Move();		//�v���C���[�̈ړ�
	void NotTipMove();
	void PlayerFlight();		//�v���C���[�̋󒆏��
	void PlayerGroundWalk();	//�v���C���[�̒n�ʕ��s

	void PlayerBackLash();

public:
	Player();			//�R���X�g���N�^
	~Player();			//�f�X�g���N�^	
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;	//�`��Ɋւ��邱�Ƃ���������
};