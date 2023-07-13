#include "Enemy.h"
#include "DxLib.h"
#include <math.h>

// �R���X�g���N�^
Enemy::Enemy()
{
	for (int i = 0; i < 19; i++)
	{
		enemy_pink_image[i];
		enemy_green_image[i];
		enemy_red_image[i];
	}
	// �G�̉摜�̓Ǎ�
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_P_Animation.png", 19, 8, 3, 64, 64, enemy_pink_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_G_Animation.png", 19, 8, 3, 64, 64, enemy_green_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_R_Animation.png", 19, 8, 3, 64, 64, enemy_red_image);

	enemy_x = 200.0f;
	enemy_y = 252.0f;
	enemy_speed = 0;
	enemy_angle = 0;

	xc = 0.0f;
	yc = 0.0f;
	x = 0.0f;
	y = 0.0f;

	fps_count = 0;
	second = 0;

	inflat_bealloon_count = 0;
	flight_count = 0;

	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;

	mouse_x = 0;
	mouse_y = 0;

	radian = 0.0f;

	move_x = 0.0f;
	move_y = 0.0f;

	turn_flg = FALSE;
}

// �f�X�g���N�^
Enemy::~Enemy()
{

}

// �`��ȊO�̍X�V������
void Enemy::Update()
{
	// �}�E�X�̍��W�̎擾�i�̂��Ƀv���C���[�̍��W�ɕς��j
	GetMousePoint(&mouse_x, &mouse_y);

	fps_count++;

	if (fps_count >= 60)
	{
		// �b���̃J�E���g�𑝂₷
		second++;

		// fps�̃J�E���g��0�ɖ߂�
		fps_count = 0;
	}

	switch (enemy_state)
	{
		case EnemyState::kInflatBealloon:
			// ���D��c��܂���A�j���[�V��������
			InflatBealloon();
			break;
		case EnemyState::kFlight:
			EnemyMove();
			Flight();
			break;
		case EnemyState::kParachute:
			Parachute();
			break;
		case EnemyState::kUpright:
			Upright();
			break;
		case EnemyState::kDeath:
			Death();
			break;
		default:
			break;
	}

}

// �`��Ɋւ��邱�Ƃ�����
void Enemy::Draw() const
{
#if _DEBUG
	// �b���̕`��
	DrawFormatString(10, 10, 0xFFFFFF, "E �b��%5d", second);

	//SetFontSize(15);
	//// �}�E�X�̍��W�̕`��
	////DrawFormatString(10, 50, 0xffffff, "mouse_x = %3d, mouse_y = %3d", mouse_x, mouse_y);
	//DrawFormatString(0, 30, 0xffffff, "E enemy_x = %3f, enemy_y = %3f", enemy_x, enemy_y);
	//DrawFormatString(0, 80, 0xffffff, "E move_x = %3f, move_y = %3f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E x = %3f, y = %3f", x, y);
	//DrawFormatString(0, 160, 0xffffff, "E xc = %3f, yc = %3f", xc, yc);
	//DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "radian = %f", radian);
#endif	//_DEBUG


	// ���F�̓G�摜�̕`��
	DrawRotaGraph((int)enemy_x, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
}

// �G�̏㉺���E�ړ�����
void Enemy::EnemyMove()
{
	// �}�E�X�ƓG�̊p�x���v�Z����i�ʓx�@�j
	radian = atan2f((float)mouse_y - enemy_y, (float)mouse_x - enemy_x);

	move_x = mouse_x - enemy_x;
	move_y = mouse_y - enemy_y;

	xc = sqrtf(pow(move_x, 2));
	yc = sqrtf(pow(move_y, 2));

	// x,y���W����������1�s�N�Z�����ǂ������Ă���i�c�Ɖ��ɂ����ړ����Ȃ��j���������P����
	// �ŒZ�����ł͂Ȃ�
	if (xc != 0 && yc != 0)
	{
		x = move_x / xc;
		y = move_y / yc;
	}

	enemy_x += x;
	enemy_y += y;

}

// �G�̉���s������
void Enemy::Avoidance()
{
	if (turn_flg == TRUE)
	{
		// �G���E�������Ă���Ƃ�
		move_x++;
	}
	else if (turn_flg == FALSE)
	{
		// �G�����������Ă���Ƃ�
		move_x--;
	}
}

// ���D��c��܂���A�j���[�V��������
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22�t���[�����ɉ摜��؂�ւ���
	next_image = inflat_bealloon_count / 22;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	//// �G�̕��㏈��
	//if (inflat_bealloon_count >= 180 && move_y >= 20)
	//{
	//	// �G�𕂏コ����
	//	move_y++;
	//	enemy_y -= move_y;
	//}

	if(inflat_bealloon_count >= 180)
	{
		// 3�b�o������
		// �J�E���g��0�ɖ߂�
		inflat_bealloon_count = 0;

		// �G�̏�ԑJ��
		enemy_state = EnemyState::kFlight;
	}

}

// �󒆂ŉH�΂����A�j���[�V��������
void Enemy::Flight()
{
	flight_count++;

	// �摜�ԍ���9�C10�C11 or 9�C10�i����9, 10�j
	next_image = flight_count / 5 + 9;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (flight_count >= 10)
	{
		// �J�E���g��0�ɖ߂�
		flight_count = 0;
	}
}

// �p���V���[�g��Ԃ̃A�j���[�V��������
void Enemy::Parachute()
{

}

// ������Ԃ̏���
void Enemy::Upright()
{
	// ������Ԃ̉摜
	now_image = 0;
}

// ���S���̃A�j���[�V��������
void Enemy::Death()
{
	now_image = 13;

	//next_image = 

	// �G�̗���
	enemy_y++;
	// ���݂̍��W + enemy_y >= 480 �ɂ���K�v������
	//if (enemy_y >= 480)
	//{

	//}
}
