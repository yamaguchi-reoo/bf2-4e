#pragma once

class Stage 
{
private:
	int stage_number;//�X�e�[�W���p�ϐ�

	//�摜�p�ϐ�
	int floor_image01;
	int floor_image02;
	int floor_image03;
	int floor_image04;
	int floor_image05;
	int floor_image06;
	int floor_image07;
	int floor_image08;

	int floor_left_image01;
	int floor_left_image02;
	int floor_right_image01;
	int floor_right_image02;
	int sea_image;
public:
	//�R���X�g���N�^
	Stage();
	//�f�X�g���N�^
	~Stage();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;
};
