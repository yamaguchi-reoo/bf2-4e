#pragma once

class StageItem
{
private:
	/* �摜�p�ϐ� */
	//��
	int thunder_cloud_image[2];
	int thunder_image[5];
	int thunder_effect_image[2];

	//�T�J�i
	int fish_image;

	/*�A�j���[�V�����̑ҋ@�ϐ�*/
	//���_
	int cloud_time;
	int cloud_anime_num;

	//���݂Ȃ�
	int thunder_time;
	int thunder_anime_num;

	//�����h�L
	int thunder_effect_time;
	int thunder_effect_anime_num;

public:
	//�R���X�g���N�^
	StageItem();

	//�f�X�g���N�^
	~StageItem();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

