#pragma once
#include "BoxCollision.h"

#define MAX_FLYING_DIAMETER (1.20f)

class Player :public BoxCollision
{
private:
	int player_images[30];	//�v���C���[�̃C���[�W�摜
	bool ground_flg;		//0:�n�ʂɂ����ԁ@�P�F�������
	int direction;			//�v���C���[�̌���
	float player_gravity;	//�v���C���[�ɂ�����d��

	float move_x;			//�v���C���[�̈ړ���(��)
	float move_y;			//�v���C���[�̈ړ���(�c)

public:
	void Move();				//�v���C���[�̈ړ�
	void PlayerFlight();		//�v���C���[�̋󒆏��
	void PlayerGroundWalk();	//�v���C���[�̒n�ʕ��s
	void HitCeiling();			//�v���C���[�̈ړ��͈�
	void PlayerFalling();		//�v���C���[�ɂ�����d��

	bool PlayerFlg();			//�����Ă��邩���f����
	void PlayerReversalFlg();	//�t���O�𔽓]������
	void Bounce();				//�����i���j
	int GetLocationX();
	int GetLocationY();
	void PlayerReset();
public:
	Player();			//�R���X�g���N�^
	~Player();			//�f�X�g���N�^	
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;	//�`��Ɋւ��邱�Ƃ���������

public:
	static float get_location_x;		// �v���C���[��X���W�Q�Ɨp�̕ϐ�
	static float get_location_y;		// �v���C���[��Y���W�Q�Ɨp�̕ϐ�

};