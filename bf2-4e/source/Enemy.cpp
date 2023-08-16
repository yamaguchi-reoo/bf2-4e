#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "PadInput.h"		// �f�o�b�O�p

// �ÓI�����o�ϐ��̒�`
float Enemy::get_location_x;
float Enemy::get_location_y;


// �ÓI�����o�ϐ�
//int Enemy::animation_count;
//EnemyState Enemy::enemy_state;

//float sinangle2 = 0;		// �f�o�b�O�p

// �R���X�g���N�^
Enemy::Enemy(float set_x, float set_y, int set_type)
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
	erea.width = 45.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;

	enemy_speed = 0.1f;
	acceleration = 30.0f;						// �����x
	enemy_type = set_type;
	power_up_flg = FALSE;
	enemy_death = FALSE;
	bound_flg = 0;							// ���͒��˕Ԃ�Ȃ����
	levitation_flg = 0;						// ���サ�Ȃ�

	// �ړ�����Ƃ��̌v�Z�Ɏg���ϐ�
	xc = 0.0f;
	yc = 0.0f;
	x = 0.0f;
	y = 0.0f;

	// �A�j���[�V�����p�J�E���g
	inflat_bealloon_count = 0;
	//flight_count = 0;
	animation_count = 0;
	levitation_count = 0;

	// �A�j���[�V�����p�ϐ�
	now_image = 0;
	next_image = 0;

	// �ǂ�������Ώۂ̍��W
	player_x = 0.0f;
	player_y = 0.0f;

	// �ړ�����Ƃ��Ɏg���ϐ�
	move_x = 0.0f;
	move_y = 0.0f;

	// �摜���]�p
	turn_flg = FALSE;				// ���]�͂��Ȃ�
	old_turn_flg = turn_flg;

	// �G�̋����ύX�p
	ckeck_flg = TRUE;				// ���W�̍����擾����
	ckeck_count = 0;

	// �p���V���[�g�p
	angle = 0.0f;
	angle2 = 0.0f;
	amplitude = 50.0f;
	enemy_start_x = -100.0f;

	// ����s���p�ϐ�
	avoidance_count = 0;
	avoidance_flg = FALSE;						// ����s���̃t���O
	difference_y = 0.0f;

	enemy_state = EnemyState::kInflatBealloon;			// �G�̏��

	get_location_x = 0.0f;
	get_location_y = 0.0f;
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

	// LB�{�^��
	// X�{�^��
	if (PadInput::OnButton(XINPUT_BUTTON_X) == 1)
	{
		enemy_state = EnemyState::kParachute;
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
			// �󒆂ŉH�΂����A�j���[�V��������
			Flight();
			//AirFall();
			if (levitation_flg == 1)
			{
				// �G�̕���
				Levitation();
			}
			else
			{
				// �G�̏㉺���E�ړ�����
				EnemyMove();
				//Avoidance();
				//CkeckPlayerLocation();
				//AirFall();
			}
			if (bound_flg == 1)
			{
				// �G�̒��˕Ԃ�i���j
				Bound();
			}
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

	get_location_x = location.x;
	get_location_y = location.y;
}

// �`��Ɋւ��邱�Ƃ�����
void Enemy::Draw() const
{
#if _DEBUG
	DrawFormatString(0, 130, 0xffffff, "E location.x = %3f, location.y = %3f", location.x, location.y);
	//DrawFormatString(0, 80, 0xffffff, "E move_x = %3f, move_y = %3f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E x = %3f, y = %3f", x, y);
	//DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "E state = %d", enemy_state);
	//DrawFormatString(20, 150, 0xffffff, "E enemy_speed = %f", enemy_speed);
	//DrawFormatString(20, 250, 0xff0000, "E enemy_state = %d", enemy_state);
	//DrawFormatString(20, 150, 0xff0000, "E bound_flg = %d", bound_flg);
	//DrawFormatString(20, 200, 0xff0000, "E avoidance_flg = %d", avoidance_flg);
	//DrawFormatString(20, 200, 0xff0000, "E turn_flg = %d", turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E old_turn_flg = %d", old_turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E enemy_life = %d", enemy_life);
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
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_green_image[now_image], TRUE, turn_flg);
		}
	}
	else
	{
		// �ԐF�̓G�摜�̕`��
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		// ��ʂ̒[�ɍs�����甽�Α��ɂ��`��
		if (location.x <= 32)
		{
			DrawRotaGraph((int)location.x + 640, (int)location.y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		}
		if (location.x >= 608)
		{
			DrawRotaGraph((int)location.x - 640, (int)location.y, 1, 0, enemy_red_image[now_image], TRUE, turn_flg);
		}
	}

	// �G�̓����蔻��͈�
	//DrawBox(location.x - (erea.width * erea.width_rate), location.y - (erea.height * erea.height_rate), location.x - (erea.height * erea.height_rate) + erea.width, location.y - (erea.height * erea.height_rate) + erea.height, 0xffff00, FALSE);
	
	//DrawBox(location.x - (erea.width / 2 * erea.width_rate), location.y - (erea.height / 2 * erea.height_rate), location.x - (erea.width / 2 * erea.width_rate) + erea.width, location.y - (erea.height / 2 * erea.height_rate) + erea.height, 0xffff00, FALSE);
	//
	//// ���D����
	//DrawBox(location.x - (erea.width / 2 * erea.width_rate), location.y - (erea.width / 2 * erea.height_rate), location.x - (erea.width / 2 * erea.height_rate) + erea.width, location.y, 0xff0000, FALSE);
	//// �̕���
	//DrawBox(location.x - (erea.width / 2 * erea.width_rate), location.y, location.x - (erea.width / 2 * erea.height_rate) + erea.width, location.y - (erea.height / 2 * erea.height_rate) + erea.height, 0x00ffff, FALSE);
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
		//avoidance_flg = TRUE;
	}

	//else
	//{
	//	avoidance_flg = FALSE;
	//}

	if (avoidance_flg == TRUE)
	{
		// �G�̉���s������
		Avoidance();
	}
	else
	{
		// �v���C���[�ƓG�̍��W�̍������߂�
		x = player_x - location.x;
		y = player_y - location.y;

		xc = sqrtf(powf(x, 2));
		yc = sqrtf(powf(y, 2));

		// x,y���W����������1�s�N�Z�����ǂ������Ă���
		if (xc != 0 && yc != 0)
		{
			// �ǂ̌����ɐi�߂΂����̂���-1�`1�̊Ԃŋ��߂Ă���i�����j
			move_x = x / xc;
			move_y = y / yc;
		}

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

		// �����̏���
		if (old_turn_flg == turn_flg)
		{
			// �����x�̉e���𑬓x�ɗ^����
			enemy_speed += acceleration / 3600;

			// �G�̃^�C�v�ɂ���čō����x���ς��
			if (enemy_type == 0 && enemy_speed >= 0.5f)
			{
				enemy_speed = 0.5f;
			}
			else if (enemy_type == 1 && enemy_speed >= 0.8f)
			{
				enemy_speed = 0.8f;
			}
			else if (enemy_type == 2 && enemy_speed >= 1.0f)
			{
				enemy_speed = 1.0f;
			}
			else if(enemy_speed <= 0.0f)
			{
				enemy_speed = 0.0f;
			}
		}

		// �����̏���
		if (old_turn_flg != turn_flg/*&& enemy_speed >= 0.0f*/)
		{
			move_x *= -1.0f;
			// �����x�̉e���𑬓x�ɗ^����
			enemy_speed -= acceleration / 3600;

			if (enemy_speed <= 0.0f)
			{
				enemy_speed = 0.0f;
				old_turn_flg = turn_flg;
			}
		}

		// �G�̈ړ�
		location.x += move_x * enemy_speed;
		location.y += move_y * enemy_speed / 2;
	}	
}

// �G�̉���s������
void Enemy::Avoidance()
{
	avoidance_count++;
	if (avoidance_count <= 120)
	{
		location.x += move_x * enemy_speed;
	}
	else
	{
		avoidance_count = 0;
		avoidance_flg = FALSE;
	}
	
	//avoidance_count++;
	////if (avoidance_count <= 120)
	////{
	//	//if (turn_flg == TRUE)
	//	//{
	//		// �G���E�������Ă���Ƃ�
	//		// enemy_x += move_x * speed�@�ɂ���K�v������
	//		location.x += move_x * enemy_speed;
	////	}
	//	//else if (turn_flg == FALSE)
	//	//{
	//	//	// �G�����������Ă���Ƃ�
	//	//	// enemy_x -= move_x * speed�@�ɂ���K�v������
	//	//	location.x -= enemy_speed;
	//	//}
	////}
	////else
	////{
	////	avoidance_count = 0;
	////	avoidance_flg = FALSE;
	////}
}

// ���D��c��܂���A�j���[�V��������
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22�t���[�����Ƃɉ摜��؂�ւ���i0 �` 7��8���j
	next_image = inflat_bealloon_count / 22;

	if (inflat_bealloon_count <= 180 && now_image < 7)
	{
		// 3�b�ԕ��D��c��܂���A�j���[�V����
		if (now_image != next_image)
		{
			now_image = next_image;
		}
	}
	else
	{
		levitation_flg = 1;
		inflat_bealloon_count = 0;

		// �G�̏�ԑJ��
		// �f�o�b�O�p
		//enemy_state = EnemyState::kDeath;

		enemy_state = EnemyState::kFlight;
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
}

// ������Ԃ̏���
void Enemy::Upright()
{
	if (enemy_start_x != -100.0f)
	{
		angle = 0;
		animation_count = 0;
		enemy_start_x = -100.0f;
	}

	// ������Ԃ̉摜
	now_image = 0;

	// �G���ԐF�ł͂Ȃ��Ƃ�
	if (enemy_type <= 3)
	{
		// �p���[�A�b�v�̃t���O�𗧂Ă�
		power_up_flg = TRUE;
	}

	// ��3�b�\��
	if (++animation_count >= 180)
	{
		// �c��܂���������p���[�A�b�v
		enemy_state = EnemyState::kInflatBealloon;
		animation_count = 0;
	}
}

// ���S���̃A�j���[�V��������
void Enemy::Death()
{
	// �摜��13, 14�i2���j
	animation_count++;

	if (animation_count <= 4)
	{
		now_image = 13;
		//enemy_life = FALSE;
		//enemy_delete = TRUE;
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
	if (location.y >= 480)
	{
		 enemy_death = FALSE;
	}
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

// �G�̒��˕Ԃ�
void Enemy::Bound()
{
	//location.x += move_x * -1.0f;
	//location.y += move_y * -1.0f;

	location.x += move_x * enemy_speed;

	//move_x *= -1.0f;
	// �����x�̉e���𑬓x�ɗ^����
	//enemy_speed -= acceleration / 3600;

	//if (enemy_speed <= 0.0f)
	//{
	//	enemy_speed = 0.0f;
	//	//old_turn_flg = turn_flg;
	//	bound_flg = 0;
	//}

	////location.x += move_x * enemy_speed * -1.0f;
	//location.x += move_x * enemy_speed;
}

// �t���O�̐ݒ�
void Enemy::SetBoundFlg(int set_flg)
{
	bound_flg = set_flg;
}

// �G�̕���
void Enemy::Levitation(void)
{
	// �p���[�A�b�v����
	if (power_up_flg == TRUE)
	{
		// �^�C�v�̕ύX
		enemy_type++;

		// �����x�̐ݒ�
		enemy_speed = 0.1f;

		power_up_flg = FALSE;
	}

	levitation_count++;

	if (levitation_count <= 30)
	{
		location.y -= enemy_speed;
	}
	else
	{
		levitation_flg = 0;
		levitation_count = 0;
	}
}

// �G�̕���t���O�̐ݒ�
void Enemy::SetLevitationFlg(int set_flg)
{
	levitation_flg = set_flg;
}

int Enemy::GetEnemyDeathFlg()
{
	return enemy_death;
}


//�V���{���ʃX�|�[�����̓G�̏�Ԃ���̔��f���邽�߂̏���
bool Enemy::EnemyStateJudgment(void)
{
	int ret = false;

	//���S���ƃp���V���[�g���̂�true
	if ((enemy_state == EnemyState::kDeath) || (enemy_state == EnemyState::kParachute)) 
	{
		if (location.y > 450) 
		{
			ret = true;
		}
		
	}

	return ret;
}
