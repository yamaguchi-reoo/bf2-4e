#pragma once

#pragma once

class Thunder
{
private:
	/* �摜�p�ϐ� */
	//��
	int thunder_cloud_image[3];
	int thunder_image[6];
	int thunder_effect_image[3];

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
	Thunder();

	//�f�X�g���N�^
	~Thunder();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

