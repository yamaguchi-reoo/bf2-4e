#pragma once
#include "BoxCollision.h"

#define MAX_FLYING_DIAMETER (1.2)

class Player :public BoxCollision
{
private:
	int player_images[30];	//�v���C���[�̃C���[�W�摜
	int player_flg;			//0:�n�ʂɂ����ԁ@�P�F�������
	int direction;			//�v���C���[�̌���
	int speed_x;			//�v���C���[�̑��x(x���W)
	float speed_y;			//�v���C���[�̑��x(y���W)
	float flying_diameter;		//�v���C���[�̏㏸

	int move_x;
	int move_y;
	int player_angle;

public:
	void Move();				//�v���C���[�̈ړ�
	void NotTipMove();
	void PlayerFlight();		//�v���C���[�̋󒆏��
	void PlayerGroundWalk();	//�v���C���[�̒n�ʕ��s
	void MaxDiameter();			//�v���C���[�̏㏸�{��
	void MoveLocation();		//�v���C���[�̈ړ��͈�

	void PlayerBackLash();

public:
	Player();			//�R���X�g���N�^
	~Player();			//�f�X�g���N�^	
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;	//�`��Ɋւ��邱�Ƃ���������

public:
	static float get_location_x;		// �v���C���[��X���W�Q�Ɨp�̕ϐ�
	static float get_location_y;		// �v���C���[��Y���W�Q�Ɨp�̕ϐ�

};