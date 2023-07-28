#pragma once
#include "Fps.h"

class Thunder
{
private:
	/* �摜�p�ϐ� */
	//��
	int thunder_cloud_image[3];
	int thunder_image[6];
	int thunder_effect_image[3];

	/*�A�j���[�V�����̑ҋ@�p�ϐ�*/
	//���_
	int cloud_anime_num;

	int thunder_cloud_frame = 60;	//��������
	int thunder_cloud_anime_frame;	//���_�̃A�j���[�V�����p�̃t���[��

	//���_�̃A�j���[�V����
	int thunder_cloud_time;			
	int thunder_cloud_anime_num;	

	//���
	int thunder_time_anime;		//
	int thunder_anime_num;		//

	int thunder_frame = 60;		//��������
	int thunder_anime_frame;	//����̃A�j���[�V�����p�̃t���[��

	bool is_thunder_shoot_ready;	//������o�����ǂ���
	bool thunder_shoot_flg;			//������o�Ă���ǂ���

	//�����h�L
	int thunder_effect_time;
	int thunder_effect_anime_num;

public:
	//�R���X�g���N�^
	Thunder();

	//�f�X�g���N�^
	~Thunder();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

