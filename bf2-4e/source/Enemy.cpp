#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "PadInput.h"		// �f�o�b�O�p

// �ÓI�����o�ϐ�
//int Enemy::animation_count;

float angle = 0;
float angle2;
float sinangle2 = 0;		// �f�o�b�O�p

// �R���X�g���N�^
Enemy::Enemy()
{
	player = new Player;

	for (int i = 0; i < 18; i++)
	{
		enemy_pink_image[i];
		enemy_green_image[i];
		enemy_red_image[i];
	}
	// �G�̉摜�̓Ǎ�
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_P_Animation.png", 18, 6, 3, 64, 64, enemy_pink_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_G_Animation.png", 18, 6, 3, 64, 64, enemy_green_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_R_Animation.png", 18, 6, 3, 64, 64, enemy_red_image);
	
	// �G�̏��
	enemy_x = 608.0f;			// �f�o�b�O�p
	//enemy_y = 32.0f;				// �f�o�b�O�p
	//enemy_x = 200.0f;
	enemy_y = 252.0f;
	enemy_speed = 0.5f;
	enemy_angle = 0;
	enemy_type = 0;
	power_up_flg = FALSE;

	// �ړ�����Ƃ��̌v�Z�Ɏg���ϐ�
	xc = 0.0f;
	yc = 0.0f;
	x = 0.0f;
	y = 0.0f;

	fps_count = 0;
	second = 0;

	// �A�j���[�V�����p�J�E���g
	//inflat_bealloon_count = 0;
	//flight_count = 0;
	animation_count = 0;

	avoidance_count = 0;

	// �A�j���[�V�����p�ϐ�
	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;

	// �ǂ�������Ώۂ̍��W
	mouse_x = 0;
	mouse_y = 0;

	// �ړ�����Ƃ��Ɏg���ϐ�
	move_x = 0.0f;
	move_y = 0.0f;

	turn_flg = FALSE;				// ���]�͂��Ȃ�

	ckeck_flg = TRUE;				// ���W�̍����擾����
	ckeck_count = 0;

	amplitude = 50.0f;
	enemy_start_x = -100.0f;

	avoidance_flg = FALSE;						// ����s���̃t���O

	difference_y = 0.0f;
}

// �f�X�g���N�^
Enemy::~Enemy()
{

}

// �`��ȊO�̍X�V������
void Enemy::Update()
{
	// �G�̐F���Ƃ̓���m�F�p�@����ō폜
	// RB�{�^��
	if (PadInput::OnButton(XINPUT_BUTTON_RIGHT_SHOULDER) == 1)
	{
		if (enemy_type < 2)
		{
			enemy_type++;

		}
		else
		{
			enemy_type = 0;
		}
	}

	// �G�̐F���Ƃ̓���m�F�p�@����ō폜
	// LB�{�^��
	if (PadInput::OnButton(XINPUT_BUTTON_LEFT_SHOULDER) == 1)
	{
		// �f�o�b�O�p
		enemy_state = EnemyState::kParachute;
	}

	// �}�E�X�̍��W�̎擾�i�̂��Ƀv���C���[�̍��W�ɕς��j
	GetMousePoint(&mouse_x, &mouse_y);

	// ��ŏ������
	fps_count++;
	if (fps_count >= 60)
	{
		// �b���̃J�E���g�𑝂₷
		second++;
		// fps�̃J�E���g��0�ɖ߂�
		fps_count = 0;
	}

	// ����������G�̏���
	switch (enemy_state)
	{
		case EnemyState::kInflatBealloon:
			// ���D��c��܂���A�j���[�V��������
			InflatBealloon();
			break;
		case EnemyState::kFlight:
			// �G�̏㉺���E�ړ�����
			EnemyMove();
			//Avoidance();
			//CkeckPlayerLocation();
			// �󒆂ŉH�΂����A�j���[�V��������
			Flight();
			//AirFall();
			break;
		case EnemyState::kParachute:
			// �p���V���[�g��Ԃ̃A�j���[�V��������
			Parachute();
			break;
		case EnemyState::kUpright:
			// ������Ԃ̏���
			Upright();
			break;
		case EnemyState::kDeath:
			// ���S���̃A�j���[�V��������
			Death();
			break;
		default:
			break;
	}

	// X���W�̃��[�v��������̍��W�ύX����
	AfterWarp();
}

// �`��Ɋւ��邱�Ƃ�����
void Enemy::Draw() const
{
#if _DEBUG
	// �b���̕`��
	DrawFormatString(10, 10, 0xFFFFFF, "E �b��%5d", second);

	//SetFontSize(15);
	//// �}�E�X�̍��W�̕`��
	DrawFormatString(10, 50, 0xffffff, "mouse_x = %3d, mouse_y = %3d", mouse_x, mouse_y);
	DrawFormatString(0, 30, 0xffffff, "E enemy_x = %3f, enemy_y = %3f", enemy_x, enemy_y);
	DrawFormatString(0, 80, 0xffffff, "E move_x = %3f, move_y = %3f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E x = %3f, y = %3f", x, y);
	//DrawFormatString(0, 160, 0xffffff, "E xc = %3f, yc = %3f", xc, yc);
	//DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "E state = %d", enemy_state);
	//DrawFormatString(200, 250, 0xff0000, "E angle2 = %f", angle2);
	//DrawFormatString(200, 250, 0xff0000, "E enemy_start_x = %f", enemy_start_x);
	//DrawFormatString(200, 250, 0xff0000, "E sinangle2 = %f", sinangle2);
	//DrawFormatString(200, 250, 0xff0000, "E a = %f", difference_y);
	//DrawFormatString(20, 250, 0xff0000, "E avoidance_flg = %d", avoidance_flg);
#endif	//_DEBUG

	if (enemy_type == 0)
	{
		// ���F�̓G�摜�̕`��
		DrawRotaGraph((int)enemy_x, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		// ��ʂ̒[�ɍs�����甽�Α��ɂ��`��
		if (enemy_x <= 32)
		{
			DrawRotaGraph((int)enemy_x + 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (enemy_x >= 608)
		{
			DrawRotaGraph((int)enemy_x - 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
	else if (enemy_type == 1)
	{
		// �ΐF�̓G�摜�̕`��
		DrawRotaGraph((int)enemy_x , (int)enemy_y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		// ��ʂ̒[�ɍs�����甽�Α��ɂ��`��
		if (enemy_x <= 32)
		{
			DrawRotaGraph((int)enemy_x + 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (enemy_x >= 608)
		{
			DrawRotaGraph((int)enemy_x - 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
	//else if (enemy_type == 2)
	else
	{
		// �ԐF�̓G�摜�̕`��
		DrawRotaGraph((int)enemy_x , (int)enemy_y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		// ��ʂ̒[�ɍs�����甽�Α��ɂ��`��
		if (enemy_x <= 32)
		{
			DrawRotaGraph((int)enemy_x + 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (enemy_x >= 608)
		{
			DrawRotaGraph((int)enemy_x - 640, (int)enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
}

// �G�̏㉺���E�ړ�����
void Enemy::EnemyMove()
{
	difference_y = enemy_y - (float)mouse_y;

	// ����s���̏���
	if (avoidance_flg == FALSE && enemy_y > mouse_y && difference_y <= 70 && mouse_x >= enemy_x - 32 && mouse_x <= enemy_x + 32)
	//if(enemy_y > mouse_y && difference_y <= 50)
	{
		avoidance_flg = TRUE;
	}

	if (avoidance_flg == TRUE)
	{
		avoidance_count++;
		if (avoidance_count <= 120)
		{
			// �G�̉���s��
			//if (mouse_x >= enemy_x - 30 && mouse_x <= enemy_x + 30)
			//{
				if (turn_flg == TRUE)
				{
					// �G���E�������Ă���Ƃ�
					// enemy_x += move_x * speed�@�ɂ���K�v������
					enemy_x++;
				}
				else if (turn_flg == FALSE)
				{
					// �G�����������Ă���Ƃ�
					// enemy_x -= move_x * speed�@�ɂ���K�v������
					enemy_x--;
				}
			//}
		}
		else
		{
			avoidance_count = 0;
			avoidance_flg = FALSE;
		}
	}
	else
	{
		//player->location.x

		// �}�E�X�ƓG�̍��W�̍������߂�
		move_x = (float)mouse_x - enemy_x;
		move_y = (float)mouse_y - enemy_y;

		xc = sqrtf(powf(move_x, 2));
		yc = sqrtf(powf(move_y, 2));

		// x,y���W����������1�s�N�Z�����ǂ������Ă���i�c�Ɖ��ɂ����ړ����Ȃ��j���������P����
		// �ŒZ�����ł͂Ȃ�
		if (xc != 0 && yc != 0)
		{
			// �ǂ̌����ɐi�߂΂����̂���-1�`1�̊Ԃŋ��߂Ă���i�����j
			x = move_x / xc;
			y = move_y / yc;
		}

		// �X�s�[�h�������Ĉړ����x��ύX�����Ȃ��Ƃ����Ȃ�
		enemy_x += x * enemy_speed;
		enemy_y += y * enemy_speed / 2;

		// �摜�̔��]�����i�J�[�\���̕����������j
		if (x >= 0)
		{
			turn_flg = TRUE;
		}
		else
		{
			turn_flg = FALSE;
		}
	}	
}

// �G�̉���s������
void Enemy::Avoidance()
{

	//	if (avoidance_count <= 120)
	//	{
	//		if (turn_flg == TRUE)
	//		{
	//			// �G���E�������Ă���Ƃ�
	//			// enemy_x += move_x * speed�@�ɂ���K�v������
	//			move_x++;
	//		}
	//		else if (turn_flg == FALSE)
	//		{
	//			// �G�����������Ă���Ƃ�
	//			// enemy_x -= move_x * speed�@�ɂ���K�v������
	//			move_x--;
	//		}
	//	}
	//	else
	//	{
	//		avoidance_count = 0;
	//	}
	//}
	//avoidance_flg = FALSE;

}

// ���D��c��܂���A�j���[�V��������
void Enemy::InflatBealloon()
{
	animation_count++;

	// 22�t���[�����Ƃɉ摜��؂�ւ���i0 �` 7��8���j
	next_image = animation_count / 22;

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

	if(animation_count >= 180)
	{
		// 3�b�o������
		// �J�E���g��0�ɖ߂�
		animation_count = 0;

		// �G�̏�ԑJ��
		enemy_state = EnemyState::kFlight;
	}

	// if(�p���[�A�b�v�̃t���O�������Ă�����)type++
	// �p���[�A�b�v����
	if (power_up_flg == TRUE)
	{
		// �^�C�v�̕ύX
		enemy_type++;

		// �X�s�[�h�̕ύX
		enemy_speed++;

		// power_up_flg = FALSE;
	}

}

// �󒆂ŉH�΂����A�j���[�V��������
void Enemy::Flight()
{
	animation_count++;

	// �摜�ԍ���8, 9�i2���j
	next_image = animation_count / 6 + 8;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (animation_count >= 10)
	{
		// �J�E���g��0�ɖ߂�
		animation_count = 0;
	}
}

// �󒆗����A�j���[�V��������
void Enemy::AirFall()
{
	// �摜��10, 11, 12�i���D���h��Ă���3���j

	animation_count++;

	next_image = animation_count / 11 + 10;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (animation_count >= 30)
	{
		// �J�E���g��0�ɖ߂�
		animation_count = 0;
	}

}

// �p���V���[�g��Ԃ̃A�j���[�V��������
void Enemy::Parachute()
{
	if (enemy_start_x == -100.0f)
	{
		// enemy_start_x���g���Ă��Ȃ�������
		enemy_start_x = enemy_x;
	}

	animation_count++;

	// �摜��15, 16, 17�i2���j
	// 15, 16�̓p���V���[�g���J���摜
	// 17�͗������̉摜
	if (animation_count <= 5)
	{
		now_image = 15;
	}
	else if (animation_count <= 8)
	{
		now_image = 16;
	}
	else
	{
		now_image = 17;
	}

	//next_image

	angle++;
	angle2 = angle * (float)(M_PI / 180);

	sinangle2 = sinf(angle2);

	// enemu_start_x�𒆐S�ɍ��E�ɗh��鏈��
	enemy_x = (sinf(angle2) * amplitude) + enemy_start_x;
	// ��������
	enemy_y += 0.5f;


	// if(�n�ʂɂ�����)������ԂɕύX
	//power_up_flg = TRUE;
	// enemy_start_x = -100.0f;
	// animation_count = 0;
	//enemy_state = EnemyState::kUpright;
}

// ������Ԃ̏���
void Enemy::Upright()
{
	// ������Ԃ̉摜
	now_image = 0;

	// �G���ԐF�ł͂Ȃ��Ƃ�
	if (enemy_type <= 3)
	{
		// �p���[�A�b�v�̃t���O�𗧂Ă�
		power_up_flg = TRUE;
	}

	// if(��莞�Ԃ�������)���D��c��܂����ԂɕύX
	// �c��܂���������p���[�A�b�v
	enemy_state = EnemyState::kInflatBealloon;

	// �p���[�A�b�v����
	//if (enemy_type <= 3)
	//{
	//	enemy_type++;
	//}
}

// ���S���̃A�j���[�V��������
void Enemy::Death()
{
	// �摜��13, 14�i2���j

	now_image = 13;

	//next_image = 

	// �G�̗���
	enemy_y++;
	// ���݂̍��W + enemy_y >= 480 �ɂ���K�v������
	//if (enemy_y >= 480)
	//{

	//}
}

// �v���C���[�Ƃ̍��W�̍����擾���邩�̔��菈��
void Enemy::CkeckPlayerLocation()
{
	ckeck_count++;

	if (ckeck_flg == FALSE)
	{
		if (enemy_type == 0 && ckeck_count >= 300)
		{
			// ���F�̓G��5�b���Ƃɍ��W�̔�r
			ckeck_flg = TRUE;
			ckeck_count = 0;
		}
		else if (enemy_type == 1 && ckeck_count >= 180)
		{
			// �ΐF�̓G��3�b���Ƃɍ��W�̔�r
			ckeck_flg = TRUE;
			ckeck_count = 0;
		}
		else if(enemy_type == 2 && ckeck_count >= 60)
		{
			// �ԐF�̓G��1�b���Ƃɍ��W�̔�r
			ckeck_flg = TRUE;
			ckeck_count = 0;
		}
	}
}

// X���W�̃��[�v��������̍��W�ύX����
void Enemy::AfterWarp()
{
	if (enemy_x <= -32)
	{
		enemy_x = 608;
	}
	if (enemy_x >= 672)
	{
		enemy_x = 32;
	}
}
