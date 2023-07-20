#pragma once
#include "BoxCollision.h"

#define MAX_FLYING_DIAMETER (1.20f)

class Player :public BoxCollision
{
private:
	int player_images[30];	//�v���C���[�̃C���[�W�摜
	int player_flg;			//0:�n�ʂɂ����ԁ@�P�F�������
	int direction;			//�v���C���[�̌���
	float speed_x;			//�v���C���[�̑��x(x���W)
	float speed_y;			//�v���C���[�̑��x(y���W)
	float flying_diameter;		//�v���C���[�̏㏸
	float gravity_A = 0.7f;

public:
	void Move();				//�v���C���[�̈ړ�
	void PlayerFlight();		//�v���C���[�̋󒆏��
	void PlayerGroundWalk();	//�v���C���[�̒n�ʕ��s
	void MoveLocation();		//�v���C���[�̈ړ��͈�
	void PlayerGravity();		//�v���C���[�ɂ�����d��

public:
	float GetPlayerX();
	float GetPlayerY();
	Player();			//�R���X�g���N�^
	~Player();			//�f�X�g���N�^	
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;	//�`��Ɋւ��邱�Ƃ���������
};