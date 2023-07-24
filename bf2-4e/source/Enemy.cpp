#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "PadInput.h"		// �f�o�b�O�p

// �ÓI�����o�ϐ�
//int Enemy::animation_count;

//float sinangle2 = 0;		// �f�o�b�O�p

// �R���X�g���N�^
Enemy::Enemy(float set_x, float set_y, int set_type)
//Enemy::Enemy()
{
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
	
	// �G�̏��i�\���̂���j
	location.x = set_x;			// ���S���WX
	location.y = set_y;			// ���S���WY
	//location.x = 200.0f;			// ���S���WX
	//location.y = 252.0f;			// ���S���WY
	erea.width = 64.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;

	//enemy_x = 200.0f;
	//enemy_y = 252.0f;
	enemy_speed = 0.5f;
	acceleration = 0.1f;						// �����x
	enemy_angle = 0;
	enemy_type = set_type;
	//enemy_type = 0;
	power_up_flg = FALSE;
	enemy_life = TRUE;

	inertia_count = 0;
	inertia_flg = FALSE;					// �����������Ȃ�

	// �ړ�����Ƃ��̌v�Z�Ɏg���ϐ�
	xc = 0.0f;
	yc = 0.0f;
	x = 0.0f;
	y = 0.0f;

	fps_count = 0;
	second = 0;

	// �A�j���[�V�����p�J�E���g
	inflat_bealloon_count = 0;
	//flight_count = 0;
	animation_count = 0;

	// �����p�̃J�E���g
	avoidance_count = 0;

	// �A�j���[�V�����p�ϐ�
	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;

	// �ǂ�������Ώۂ̍��W
	player_x = 0.0f;
	player_y = 0.0f;

	// �ړ�����Ƃ��Ɏg���ϐ�
	move_x = 0.0f;
	move_y = 0.0f;

	turn_flg = FALSE;				// ���]�͂��Ȃ�
	old_turn_flg = turn_flg;

	ckeck_flg = TRUE;				// ���W�̍����擾����
	ckeck_count = 0;

	angle = 0.0f;
	angle2 = 0.0f;
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
	/****************************
	* ���f�o�b�O�p
	*****************************/

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
		enemy_state = EnemyState::kParachute;
	}

	// ��ŏ������
	fps_count++;
	if (fps_count >= 60)
	{
		// �b���̃J�E���g�𑝂₷
		second++;
		// fps�̃J�E���g��0�ɖ߂�
		fps_count = 0;
	}

	/****************************
	* ����������G�̏���
	*****************************/
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
	//DrawFormatString(0, 150, 0xffffff, "player_x = %3f, player_y = %3f", player_x, player_y);
	DrawFormatString(0, 130, 0xffffff, "E enemy_x = %3f, enemy_y = %3f", location.x, location.y);
	DrawFormatString(0, 80, 0xffffff, "E move_x = %3f, move_y = %3f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E x = %3f, y = %3f", x, y);
	//DrawFormatString(0, 160, 0xffffff, "E xc = %3f, yc = %3f", xc, yc);
	DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "E state = %d", enemy_state);
	//DrawFormatString(200, 250, 0xff0000, "E angle2 = %f", angle2);
	//DrawFormatString(200, 250, 0xff0000, "E enemy_start_x = %f", enemy_start_x);
	//DrawFormatString(200, 250, 0xff0000, "E sinangle2 = %f", sinangle2);
	//DrawFormatString(200, 250, 0xff0000, "E a = %f", difference_y);
	//DrawFormatString(20, 250, 0xff0000, "E avoidance_flg = %d", avoidance_flg);
	//DrawFormatString(20, 250, 0xff0000, "E enemy_speed = %f", enemy_speed);
	DrawFormatString(20, 250, 0xff0000, "E enemy_state = %d", enemy_state);
#endif	//_DEBUG

	if (enemy_type == 0)
	{
		// ���F�̓G�摜�̕`��
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		// ��ʂ̒[�ɍs�����甽�Α��ɂ��`��
		if (location.x <= 32)
		{
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
	else if (enemy_type == 1)
	{
		// �ΐF�̓G�摜�̕`��
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		// ��ʂ̒[�ɍs�����甽�Α��ɂ��`��
		if (location.x <= 32)
		{
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
	else
	{
		// �ԐF�̓G�摜�̕`��
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		// ��ʂ̒[�ɍs�����甽�Α��ɂ��`��
		if (location.x <= 32)
		{
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_pink_image[now_image], TRUE, turn_flg);
		}
	}
}

// �G�̏㉺���E�ړ�����
void Enemy::EnemyMove()
{
	// �v���C���[�̍��W�Q��
	player_x = Player::get_location_x;
	player_y = Player::get_location_y;

	// ����s���̏����p
	difference_y = location.y - player_y;

	// ����s���̏���
	if (avoidance_flg == FALSE && location.y > player_y && difference_y <= 70 && player_x >= location.x - 20 && player_x <= location.x + 20)
	{
		avoidance_flg = TRUE;
	}

	if (avoidance_flg == TRUE)
	{
		// �G�̉���s������
		Avoidance();
	}
	else
	{
		// �v���C���[�ƓG�̍��W�̍������߂�
		move_x = player_x - location.x;
		move_y = player_y - location.y;

		xc = sqrtf(powf(move_x, 2));
		yc = sqrtf(powf(move_y, 2));

		// x,y���W����������1�s�N�Z�����ǂ������Ă���
		if (xc != 0 && yc != 0)
		{
			// �ǂ̌����ɐi�߂΂����̂���-1�`1�̊Ԃŋ��߂Ă���i�����j
			x = move_x / xc;
			y = move_y / yc;
		}

		//�摜�̔��]�����i�J�[�\���̕����������j
		//if (old_turn_flg == turn_flg)
		//{
		//	if (x >= 0)
		//	{
		//		// ��������
		//		turn_flg = TRUE;
		//	}
		//	else
		//	{
		//		// �E������
		//		turn_flg = FALSE;
		//	}
		//}

			//if (inertia_count <= 120)
			//{
			//	if (turn_flg == TRUE && enemy_speed >= 0)
			//	{
			//		// ������E�Ɍ������Ƃ�
			//		/*enemy_speed -= acceleration * Inertia_count;
			//		location.x += enemy_speed * Inertia_count;*/
			//		acceleration = enemy_speed + 0.1f / 100;
			//		location.x -= acceleration;
			//		enemy_speed -= acceleration;
			//		//location.x -= enemy_speed - 0.01f;
			//		//enemy_speed -= 0.01f;
			//	}
			//	//else if (turn_flg == FALSE && enemy_speed >= 0)
			//	//{
			//	//	// �E���獶�Ɍ������Ƃ�
			//	//	location.x -= enemy_speed - 0.01f;
			//	//}
			//	//else if (enemy_speed <= 0)
			//	//{
			//	//	// �G���摜�̌����Ɉړ����n�߂�Ƃ�
			//	//	if (turn_flg == TRUE && enemy_speed <= 0.5)
			//	//	{
			//	//		// �E�Ɉړ�
			//	//		location.x += enemy_speed + 0.1f;
			//	//		enemy_speed += 0.01f;
			//	//	}
			//	////	else if (turn_flg == FALSE && enemy_speed <= 0.5)
			//	////	{
			//	////		// ���Ɉړ�
			//	////		location.x -= enemy_speed + 0.01f;
			//	////	}
			//	//}
			//}
			//else
			//{
			//	old_turn_flg = turn_flg;
			//	inertia_count = 0;
			//}

		//}
			
		//if (x >= 0)
		//{
		//	if (old_turn_flg == turn_flg)
		//	{
		//		// ��������
		//		turn_flg = TRUE;
		//	}
		//}
		//else
		//{
		//	if (old_turn_flg == turn_flg)
		//	{
		//		// �E������
		//		turn_flg = FALSE;
		//	}
		//}

		// if(�����������ꍇ)
		//if (old_turn_flg != turn_flg)
		//{
		//	inertia_flg = TRUE;
		//	inertia_count++;

		//	if (inertia_count <= 120)
		//	{
		//		if (turn_flg == TRUE && enemy_speed > 0)
		//		{
		//			// ������E�Ɍ������Ƃ�
		//			/*enemy_speed -= acceleration * Inertia_count;
		//			location.x += enemy_speed * Inertia_count;*/
		//			location.x -= enemy_speed - 0.01f;
		//			enemy_speed -= 0.01f;
		//		}
		//		//else if (turn_flg == FALSE && enemy_speed >= 0)
		//		//{
		//		//	// �E���獶�Ɍ������Ƃ�
		//		//	location.x -= enemy_speed - 0.01f;
		//		//}
		//		//else if (enemy_speed <= 0)
		//		//{
		//		//	// �G���摜�̌����Ɉړ����n�߂�Ƃ�
		//		//	if (turn_flg == TRUE && enemy_speed <= 0.5)
		//		//	{
		//		//		// �E�Ɉړ�
		//		//		location.x += enemy_speed + 0.1f;
		//		//		enemy_speed += 0.01f;
		//		//	}
		//		////	else if (turn_flg == FALSE && enemy_speed <= 0.5)
		//		////	{
		//		////		// ���Ɉړ�
		//		////		location.x -= enemy_speed + 0.01f;
		//		////	}
		//		//}
		//	}
		//	else
		//	{
		//		old_turn_flg = turn_flg;
		//		inertia_count = 0;
		//	}
		//}
		
		// �X�s�[�h�������Ĉړ����x��ύX�����Ȃ��Ƃ����Ȃ�
		location.x += x * enemy_speed;
		location.y += y * enemy_speed / 2;

		if (x >= 0)
		{
			// ��������
			turn_flg = TRUE;
		}
		else
		{
			// �E������
			turn_flg = FALSE;
		}
	}	
}

// �G�̉���s������
void Enemy::Avoidance()
{
	avoidance_count++;
	if (avoidance_count <= 120)
	{
		if (turn_flg == TRUE)
		{
			// �G���E�������Ă���Ƃ�
			// enemy_x += move_x * speed�@�ɂ���K�v������
			location.x += enemy_speed;
		}
		else if (turn_flg == FALSE)
		{
			// �G�����������Ă���Ƃ�
			// enemy_x -= move_x * speed�@�ɂ���K�v������
			location.x -= enemy_speed;
		}
	}
	else
	{
		avoidance_count = 0;
		avoidance_flg = FALSE;
	}
}

// ���D��c��܂���A�j���[�V��������
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22�t���[�����Ƃɉ摜��؂�ւ���i0 �` 7��8���j
	next_image = inflat_bealloon_count / 22;

	if (inflat_bealloon_count <= 180)
	{
		// 3�b�ԕ��D��c��܂���A�j���[�V����
		if (now_image != next_image)
		{
			now_image = next_image;
		}
	}
	else if (inflat_bealloon_count >= 180 && inflat_bealloon_count <= 210)
	{
		// �G�𕂏コ����
		location.y -= enemy_speed;
		Flight();
	}
	else
	{
		inflat_bealloon_count = 0;

		// �G�̏�ԑJ��
		// �f�o�b�O�p
		//enemy_state = EnemyState::kDeath;

		enemy_state = EnemyState::kFlight;
	}

	// if(�p���[�A�b�v�̃t���O�������Ă�����)type++
	// �p���[�A�b�v����
	if (power_up_flg == TRUE)
	{
		// �^�C�v�̕ύX
		enemy_type++;

		// �X�s�[�h�̕ύX�i�H�j
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
		enemy_start_x = location.x;
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

	angle++;
	angle2 = angle * (float)(M_PI / 180);

	//sinangle2 = sinf(angle2);

	// enemu_start_x�𒆐S�ɍ��E�ɗh��鏈��
	location.x = (sinf(angle2) * amplitude) + enemy_start_x;
	// ��������
	location.y += 0.5f;

	// if(�n�ʂɂ�����)������ԂɕύX�i�X�e�[�W�Ƃ̓����蔻��j
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
	// ����3�b���炢
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
	animation_count++;

	if (animation_count <= 4)
	{
		now_image = 13;
	}
	else if (animation_count <= 8)
	{
		now_image = 14;
	}
	else
	{
		animation_count = 0;
	}

	// �G�̗���
	if (move_y <= 20)
	{
		move_y++;
		// ������ɏオ��
		location.y--;
	}
	else
	{
		location.y++;
	}

	// ���݂̍��W + enemy_y >= 480 �ɂ���K�v������
	//if (location.y >= 480)
	//{
		// enemy_life = FALSE;
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
	if (location.x <= -32)
	{
		location.x = 608;
	}
	else if (location.x >= 672)
	{
		location.x = 32;
	}
}
