#pragma once
#include"BoxCollision.h"

//�I�u�W�F�N�g�z�u
struct STAGE {
	int x;
	int y;
	int w;
	int h;
	int image;
};
class Stage :public BoxCollision
{
private:
	int stage_number;//�X�e�[�W���p�ϐ�
	struct STAGE stage_location[8]{ 0,0,0,0,0,0,0,0,0 };
	struct STAGE floor_number[12];//�\���̗p�z��
	int stage_object;//�I�u�W�F�N�g��

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

	int floor_image[8];
	int floor_image_left[2];
	int floor_image_right[2];
public:
	//�R���X�g���N�^
	Stage();
	//�f�X�g���N�^
	~Stage();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

	// �I�u�W�F�N�g�̈ʒu�ݒ肷��֐�
	void SetPosition(int position_x, int position_y, int number, int image);

	//�I�u�W�F�N�g�̈ʒu���󂯎��֐�
	void GetObjectErea(int _width, int _height, int _x, int _y,int _number);
};
