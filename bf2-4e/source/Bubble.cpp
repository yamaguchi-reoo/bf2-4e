#include "DxLib.h"
#include "Bubble.h"
#include <math.h>

Bubble::Bubble()
{
	for (int i = 0; i < 4; i++)
	{
		BubbleImage[i] = 0;
	}
	LoadDivGraph("Source/Resource/images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, BubbleImage);

	animation_count = 0;					// �A�j���[�V�����p�J�E���g

	now_image = 0;							// ������\�������摜
	next_image = 0;							// ���ɕ\�������摜

	location.x = 50;
	location.y = 70;
	erea.height = 64;
	erea.width = 64;
	erea.width_rate = 0;
	erea.height_rate = 0;


	PosX = 0;		// �`����WX
	PosY = 0;		// �`����WY
	Radius = 0;		// ���a(�`��p)
	CenterX = 100;	// ���S���WX
	CenterY = 400;	// ���S���WY
	Angle = 0;		// �p�x
	Length = 30;		// ���a�̒���
}

Bubble::~Bubble()
{

}

void Bubble::Update()
{
	BubbleAnimation();
	MoveBubble();
}

void Bubble::Draw() const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, BubbleImage[now_image], TRUE);
}

void Bubble::BubbleAnimation(void) 
{
	animation_count++;

	// �摜�ԍ���8, 9�i2���j
	next_image = animation_count / 25 ;

	if (now_image != next_image && next_image < 3)
	{
		now_image = next_image;
	}

	if (animation_count >= 75)
	{
		// �J�E���g��0�ɖ߂�
		animation_count = 0;
	}
}

void Bubble::MoveBubble(void)
{
	// ���S���W�Ɋp�x�ƒ������g�p�����~�̈ʒu�����Z����
		// �x���@�̊p�x���ʓx�@�ɕϊ�
	float radius = Angle * 3.14f / 180.0f;

	// �O�p�֐����g�p���A�~�̈ʒu������o���B
	float add_x = cos(radius) * Length;
	float add_y = sin(radius) * Length;

	// ���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
	location.x = CenterX + add_x;
	//location.y = CenterY + add_y;

	// �p�x��ς���
	Angle += 2.0f;

	//���シ��
	CenterY -= 0.5f;
	location.y = CenterY;
}
