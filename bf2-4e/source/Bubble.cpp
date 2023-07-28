#include "DxLib.h"
#include "Bubble.h"

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
}

Bubble::~Bubble()
{

}

void Bubble::Update()
{
	BubbleAnimation();
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