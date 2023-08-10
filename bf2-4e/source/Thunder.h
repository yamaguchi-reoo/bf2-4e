#pragma once
#include "Fps.h"
#include"BoxCollision.h"
#include "math.h"
#define _USE_MATH_DEFINES


class Thunder:public BoxCollision
{
private:
	/* �摜�p�ϐ� */
	//��
	int thunder_cloud_image[3];
	int thunder_image[6];
	int thunder_effect_image[3];

	/*�A�j���[�V�����̑ҋ@�p�ϐ�*/
	//���_
	int cloud_X;				//�_��X���W
	int cloud_Y;				//�_��Y���W
	int cloud_anime_num;

	int thunder_cloud_frame = 60;	//��������
	int thunder_cloud_anime_frame;	//���_�̃A�j���[�V�����p�̃t���[��

	//���_�̃A�j���[�V����
	int thunder_cloud_time;	
	int thunder_cloud_anime_num;	//���_�̉摜�̃��[�v

	//���
	int thunder_time_anime;			//����̃A�j���[�V����
	int thunder_anime_num;			//����̉摜�̃��[�v
	
	int thunder_frame = 60;			//��������
	int thunder_anime_frame;		//����̃A�j���[�V�����p�̃t���[��

	bool is_thunder_shoot_ready;	//������o�����ǂ���
	bool thunder_shoot_flg;			//������o�Ă���ǂ���

	//�����h�L
	int thunder_effect_time_anime;			//�����h�L�̃A�j���[�V����

	int thunder_effect_time = 60;			//��������
	int thunder_effect_anime_num;			//�����h�L�̉摜�̃��[�v

	bool thunder_effect_shoot_flg;			//�����h�L���o�Ă���ǂ���
	bool is_thunder_effect_shoot_ready;		//�����h�L���o�����ǂ���

	float ball_angle;		//�{�[���̊p�x
	int speed;				//�{�[���̃X�s�[�h
	float moveX;				//�{�[����X�ړ���
	float moveY;				//�{�[����Y�ړ���
	//float BallX;				//�{�[����X���W
	//float BallY;				//�{�[����Y���W
	int ball_flg;			//�{�[���̏��(0...�ړ��� 1...�o�[�ڐG 2...�X�^�[�g���)

	int thunder_angle;		//���̊p�x

public:
	void ChangeAngle();		//�p�x�ύX����
	void MoveBall();		//�{�[���̈ړ�
	void StartBall();		//�X�^�[�g�{�[��
	int R_BallFlg();		//�{�[���̖߂�l


	//float GetBallX()
	//{
	//	//�{�[����X���W��Ԃ�
	//	return BallX;
	//}

	//float GetBallY()
	//{
	//	//�{�[����Y���W��Ԃ�
	//	return BallY;
	//}

	float* GetBallAngle()
	{
		//�{�[���̊p�x��Ԃ�
		return &ball_angle;
	}

	void SetBallAngle(float Angle)
	{
		ball_angle = (1 - Angle);
	}

	//�R���X�g���N�^
	Thunder();

	//�f�X�g���N�^
	~Thunder();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

