#pragma once
#include "BoxCollision.h"

#define MAX_FLYING_DIAMETER (1.20f)

class Player :public BoxCollision
{
private:
	int player_images[30];	//�v���C���[�̃C���[�W�摜
	bool player_flg;			//0:�n�ʂɂ����ԁ@�P�F�������
	int direction;			//�v���C���[�̌���
	float speed_x;			//�v���C���[�̑��x(x���W)
	float speed_y;			//�v���C���[�̑��x(y���W)
	float flying_diameter;		//�v���C���[�̏㏸
	float gravity_A = 0.7f;

	int move_x;
	int move_y;
	int player_angle;

public:
	void Move();				//�v���C���[�̈ړ�
	void PlayerFlight();		//�v���C���[�̋󒆏��
	void PlayerGroundWalk();	//�v���C���[�̒n�ʕ��s
	void MoveLocation();		//�v���C���[�̈ړ��͈�
	void PlayerGravity();		//�v���C���[�ɂ�����d��

	bool PlayerBackLash();
	void PlayerBack();

public:
	Player();			//�R���X�g���N�^
	~Player();			//�f�X�g���N�^	
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;	//�`��Ɋւ��邱�Ƃ���������

public:
	static float get_location_x;		// �v���C���[��X���W�Q�Ɨp�̕ϐ�
	static float get_location_y;		// �v���C���[��Y���W�Q�Ɨp�̕ϐ�

};