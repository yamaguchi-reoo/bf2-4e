#include "DxLib.h"
#include "Bubble.h"
#include <math.h>

Bubble::Bubble(float posX, float posY, bool drawflg, bool getflg)
{
	for (int i = 0; i < 4; i++)
	{
		BubbleImage[i] = 0;
	}
	LoadDivGraph("Source/Resource/images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, BubbleImage);

	animation_count = 0;					// �A�j���[�V�����p�J�E���g

	delete_count = 0;						//�����p�J�E���g

	now_image = 0;							// ������\�������摜
	next_image = 0;							// ���ɕ\�������摜

	location.x = 0;
	location.y = 0;
	erea.height = 40;
	erea.width = 40;
	erea.width_rate = 0;
	erea.height_rate = 0;


	PosX = 0;		// �`����WX
	PosY = 0;		// �`����WY
	Radius = 0;		// ���a(�`��p)
	CenterX = posX;	// ���S���WX
	CenterY = posY;	// ���S���WY
	Angle = 0;		// �p�x
	Length = 30;		// ���a�̒���

	GetFlg = getflg;//false;		//�Q�b�g�t���O(true:Get false:NotGet)

	DrawFlg = drawflg;		//�摜�̕`��t���O(true:�`�悷�� false:�`�悵�Ȃ�)

	scoreimage = LoadGraph("Source/Resource/images/Score/GetScore_500.png");
}

Bubble::~Bubble()
{

}

void Bubble::Update()
{

	location.x = PosX - erea.width / 2;
	location.y = PosY - erea.height / 2;

	//�Q�b�g����
	if (GetFlg == true) 
	{
		if(now_image!=3){
			now_image = 3;
		}
		if (++delete_count >= 60) 
		{
			DrawFlg = false;
		}
	}
	else
	{
		BubbleAnimation();
		MoveBubble();
	}
	
}

void Bubble::Draw() const
{
	if (DrawFlg == true) 
	{
		DrawRotaGraph((int)PosX, (int)PosY, 1, 0, BubbleImage[now_image], TRUE);
		//DrawBox((int)location.x, (int)location.y, (int)location.x + (int)erea.width, (int)location.y + (int)erea.height, 0xffffff, false);

		if (now_image == 3)
		{
			DrawGraph((int)PosX - 15, (int)PosY - 30, scoreimage, TRUE);
		}
	}
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
	float add_x = (float)cos(radius) * Length;
	float add_y = (float)sin(radius) * Length;

	// ���ʂłł��ʒu�𒆐S�ʒu�ɉ��Z���A�����`��ʒu�Ƃ���
	PosX = CenterX + add_x;
	//location.y = CenterY + add_y;

	// �p�x��ς���
	Angle += 2.0f;

	//���シ��
	CenterY -= 0.5f;
	PosY = CenterY;
}

//�Q�b�g�t���O�ύX
void Bubble::ChangeGetFlg(void)
{
	GetFlg = true;
}

int Bubble::GetDrawFlg(void)
{
	return DrawFlg;
}

int Bubble::GetGetFlg(void)
{
	return GetFlg;
}

