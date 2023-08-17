#pragma once
#include "BoxCollision.h"

class Player :public BoxCollision
{
	enum class PlayerState
	{
		kStandBalloon2,
		kStandBalloon1,
		kDashBalloon2,
		kDashBalloon1,
		kFlyingBalloon2,
		kFlyingBalloon1,
		kDeath,
		kElectrocution
	};
private:
	/*******************    �ϐ��錾    ********************/

	int player_images[30];		//�v���C���[�̃C���[�W�摜

	bool ground_flg;			//0:�n�ʂɂ����ԁ@�P�F�������
	int a_button_flg;			//0:A�{�^����������Ă��Ȃ� 1:������Ă�
	int a_count;				//B�{�^���̏���
	int fly_cnt;				//���㎞�Ԑ���ϐ�
	int direction;				//�v���C���[�̌���
	float player_gravity;		//�v���C���[�ɂ�����d��

	float move_x;				//�v���C���[�̈ړ���(��)
	float move_y;				//�v���C���[�̈ړ���(�c)
	int x_count;				//X���W�ړ����̃J�E���g�_�E���p�ϐ�

	int now_image;				//���݂̉摜
	int next_image;				//���ɉ�ʂɕ\������摜
	int animation_interval;		//�A�j���[�V�����p�̃C���^�[�o���ϐ�
	int state_image;			//�C���[�W�摜�̔z��p�ϐ�

	PlayerState player_state;	//�v���C���[�̏�ԗp�ϐ�
	int anim_count;				//�A�j���[�V�����p�J�E���^�[
	int anim_flg;				//�A�j���[�V�����p�؂�ւ��t���O	0:�J�E���g�A�b�v�@1:�J�E���g�_�E��

	int flying_images;			//�����Ԏ��̉摜�i�[�p�ϐ�

public:
	/*******************    �֐��錾    ********************/

	void PlayerGroundState();	//�v���C���[�̒n�ʕ��s
	void HitCeiling();			//�v���C���[�̈ړ��͈�

	bool PlayerFlg();			//�����Ă��邩���f����
	void PlayerReversalFlg();	//�t���O�𔽓]������
	void Bounce();				//�����i���j
	float GetLocationX();		//�v���C���[��X���W
	float GetLocationY();		//�v���C���[��Y���W
	void PlayerReset();			//�v���C���[�������ʒu��

	int AButtonFlg();			//A�{�^���������ꂽ�Ƃ��̃t���O����

	void Animation();			//�v���C���[�A�j���[�V����

public:
	Player();					//�R���X�g���N�^
	~Player();					//�f�X�g���N�^	
	void Update();				//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;			//�`��Ɋւ��邱�Ƃ���������

public:
	static float get_location_x;		// �v���C���[��X���W�Q�Ɨp�̕ϐ�
	static float get_location_y;		// �v���C���[��Y���W�Q�Ɨp�̕ϐ�

};