#pragma once
#include "BoxCollision.h"

class Bubble :public BoxCollision
{
private:
	int BubbleImage[4];

	int animation_count;					// �A�j���[�V�����p�J�E���g

	int now_image;							// ������\�������摜
	int next_image;							// ���ɕ\�������摜

	float PosX;		// �`����WX
	float PosY;		// �`����WY
	float Radius;		// ���a(�`��p)
	float CenterX;	// ���S���WX
	float CenterY;	// ���S���WY
	float Angle;		// �p�x
	float Length;		// ���a�̒���

public:
	//�R���X�g���N�^
	Bubble();

	//�f�X�g���N�^
	~Bubble();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

	//�V���{���ʂ̃A�j���[�V�����֐�
	void BubbleAnimation(void);

	//�V���{���ʂ̈ړ�
	void MoveBubble(void);

};