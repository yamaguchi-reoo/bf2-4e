#include "Enemy.h"
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

// �ÓI�����o�ϐ��̒�`
float Enemy::get_location_x;
float Enemy::get_location_y;

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
	location.x = set_x;							// ���S���WX
	location.y = set_y;							// ���S���WY
	erea.width = 45.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;

	enemy_speed = 0.0f;							// �����x
	acceleration = 30.0f;						// �����x
	bounce_coefficient = 0.8f;					// �����W��
	enemy_type = set_type;						// �G�̎�ށi0�F���F�@1�F�ΐF�@2�F�ԐF�j
	power_up_flg = FALSE;						// �p���[�A�b�v�̃t���O�iTRUE:�p���[�A�b�v����@FALSE:�p���[�A�b�v���Ȃ��j
	enemy_death = FALSE;						// �G�̐�����ԁiTRUE:���S�@FALSE:�����j
	enemy_delete = FALSE;						// �G�̍폜�iTRUE:�폜�j
	bound_flg = FALSE;							// �G�̒��˕Ԃ��ԁiTRUE:���˕Ԃ�@FALSE:���˕Ԃ�Ȃ��j
	levitation_flg = FALSE;						// �G�̕���iTRUE:���シ��j

	// �ړ�����Ƃ��̌v�Z�p�ϐ�
	abs_x = 0.0f;								// X���W�̐�Βl
	abs_y = 0.0f;								// Y���W�̐�Βl
	distance_x = 0.0f;							// X���W�̋���
	distance_y = 0.0f;							// Y���W�̋���

	// �A�j���[�V�����p�J�E���g
	inflat_bealloon_count = 0;					// ���D��c��܂�����܂ł̃J�E���g
	animation_count = 0;						// �A�j���[�V�����p�J�E���g
	levitation_count = 0;						// ���シ��J�E���g

	// �A�j���[�V�����p�ϐ�
	now_image = 0;								// ������\�������摜
	next_image = 0;								// ���ɕ\�������摜

	// �ǂ�������Ώۂ̍��W
	player_x = 0.0f;							// �v���C���[��X���W
	player_y = 0.0f;							// �v���C���[��Y���W

	// �ړ��ʕϐ�
	move_x = 1.0f;								// �G�̍��WX�̈ړ���
	move_y = 1.0f;								// �G�̍��WY�̈ړ���

	// �摜���]�p
	turn_flg = FALSE;							// �摜�̍��E���]��ԁiTRUE:���]�@FALSE:���]���Ȃ��j
	old_turn_flg = turn_flg;					// �O��̉摜�̏�Ԃ�ێ�

	// �p���V���[�g�p
	angle = 0.0f;								// �p���V���[�g��Ԃ̍��E�ړ��p
	angle2 = 0.0f;								// �p���V���[�g��Ԃ̍��E�ړ��p
	amplitude = 50.0f;							// �p���V���[�g��Ԃŉ��~����Ƃ��̐U�ꕝ
	enemy_start_x = -100.0f;					// �p���V���[�g��ԂɂȂ���x���W

	// ����s���p�ϐ�
	avoidance_count = 0;						// �������
	avoidance_flg = FALSE;						// ����s���̃t���O�iTRUE:����s���J�n�j
	difference_y = 0.0f;						// ����s���̏����p�̃v���C���[�ƓG�̍��W�̍�

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
	switch (enemy_state)
	{
		case EnemyState::kInflatBealloon:
			// ���D��c��܂���A�j���[�V��������
			InflatBealloon();
			break;
		case EnemyState::kFlight:
			if (bound_flg == TRUE)
			{
				// �󒆗����A�j���[�V��������
				AirFall();
				// �G�̒��˕Ԃ�i���j
				BoundDown();
			}
			else
			{
				// �󒆂ŉH�΂����A�j���[�V��������
				Flight();
				if (levitation_flg == TRUE)
				{
					// �G�̕���
					Levitation();
				}

				else if (avoidance_flg == TRUE)
				{
					Avoidance();
				}
				else
				{
					// �G�̏㉺���E�ړ�����
					EnemyMove();
					//CkeckPlayerLocation();
				}
			}
			break;
		case EnemyState::kParachute:
			avoidance_flg = FALSE;
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

	// �V��ɓ��������璵�˕Ԃ�
	if (location.y - (erea.width / 2 * erea.height_rate) <= 0)
	{
		move_y = 1.0f;
		bound_flg = TRUE;
	}

	get_location_x = location.x;
	get_location_y = location.y;
}

// �`��Ɋւ��邱�Ƃ�����
void Enemy::Draw() const
{
#if _DEBUG
	//DrawFormatString(0, 130, 0xffffff, "E location.x = %f, location.y = %f", location.x, location.y);
	//DrawFormatString(0, 110, 0xffffff, "E move_x = %f, move_y = %f", move_x, move_y);
	//DrawFormatString(0, 130, 0xffffff, "E ���� distance_x = %f, distance_y = %f", distance_x, distance_y);
	//DrawFormatString(0, 150, 0xffffff, "E ���� abs_x = %f, abs_y = %f", abs_x, abs_y);
	//DrawFormatString(0, 190, 0xff0000, "E now_image = %d", now_image);
	//DrawFormatString(200, 250, 0xff0000, "E state = %d", enemy_state);
	//DrawFormatString(0, 150, 0xffffff, "E enemy_speed = %f", enemy_speed);
	//DrawFormatString(20, 250, 0xff0000, "E difference_y = %f", difference_y);
	//DrawFormatString(20, 150, 0xff0000, "E levitation_flg = %d", levitation_flg);
	//DrawFormatString(20, 200, 0xff0000, "E avoidance_flg = %d", avoidance_flg);
	//DrawFormatString(20, 200, 0xff0000, "E turn_flg = %d", turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E old_turn_flg = %d", old_turn_flg);
	//DrawFormatString(20, 250, 0xff0000, "E enemy_death = %d", enemy_death);
	//DrawFormatString(0, 200, 0xff0000, "E bound_flg = %d", bound_flg);
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
}

// �G�̏㉺���E�ړ�����
void Enemy::EnemyMove()
{
	// �v���C���[�̍��W�Q��
	player_x = Player::get_location_x;
	player_y = Player::get_location_y;

	// �v���C���[�ƓG�̍��W�̍������߂�
	distance_x = player_x - location.x;
	distance_y = player_y - location.y;

	// �v���C���[�ƓG�̍��W�̐�Βl�����߂�
	abs_x = fabsf(distance_x);
	abs_y = fabsf(distance_y);

	if (abs_x != 0 && abs_y != 0)
	{
		// �i�ޕ���
		move_x = distance_x / abs_x;
		move_y = distance_y / abs_y;
	}

	if (move_x >= 0)
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
	Inertia();

	// �G�̈ړ�
	location.x += move_x * enemy_speed;
	location.y += move_y * enemy_speed / 2;

	// ����s���̏����p
	difference_y = location.y - player_y;

	// ����s���̏���
	if (avoidance_flg == FALSE && location.y > player_y && difference_y <= 70 && player_x >= location.x - 20 && player_x <= location.x + 20)
	{
		avoidance_flg = TRUE;
	}
}

// �G�̉���s������
void Enemy::Avoidance()
{
	avoidance_count++;
	if (avoidance_count <= 120)
	{
		// �����̏���
		Inertia();

		// �G�̈ړ�
		location.x += move_x * enemy_speed;
	}
	else
	{
		avoidance_count = 0;
		avoidance_flg = FALSE;
	}	
}

// �����̏���
void Enemy::Inertia()
{
	// �����̏���
	if (old_turn_flg == turn_flg)
	{
		// �����x�̉e���𑬓x�ɗ^����
		enemy_speed += acceleration / 3600;

		// �G�̃^�C�v�ɂ���čō����x���ς��
		if (enemy_type == 0 && enemy_speed >= 0.5f)
		{
			// �s���N
			enemy_speed = 0.5f;
		}
		else if (enemy_type == 1 && enemy_speed >= 0.8f)
		{
			// ��
			enemy_speed = 0.8f;
		}
		else if (enemy_type == 2 && enemy_speed >= 1.0f)
		{
			// ��
			enemy_speed = 1.0f;
		}
	}

	// �����̏���
	if (old_turn_flg != turn_flg)
	{
		if (levitation_flg == TRUE)
		{
			// ����t���O�̐ݒ�
			levitation_flg = FALSE;
		}

		move_x *= -1.0f;
		// �����x�̉e���𑬓x�ɗ^����
		enemy_speed -= acceleration / 3600;

		if (enemy_speed <= 0.0f)
		{
			enemy_speed = 0.0f;
			old_turn_flg = turn_flg;
		}
	}
}

// ���D��c��܂��鏈��
void Enemy::InflatBealloon()
{
	inflat_bealloon_count++;

	// 22�t���[�����Ƃɉ摜��؂�ւ���i0 �` 7��8���j
	next_image = inflat_bealloon_count / 22;

	if (inflat_bealloon_count <= 180 && now_image < 7)
	{
		// ���D��c��܂���A�j���[�V����
		if (now_image != next_image)
		{
			now_image = next_image;
		}
	}
	else
	{
		inflat_bealloon_count = 0;

		// �G�̏�ԑJ��
		enemy_state = EnemyState::kFlight;
	}
}

// �󒆂ŉH�΂����A�j���[�V��������
void Enemy::Flight()
{
	animation_count++;

	// �摜�ԍ���8, 9�i2���j
	next_image = (animation_count / 6) + 8;

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
	animation_count++;
	
	// �摜��10, 11, 12�i���D���h��Ă���3���j
	next_image = (animation_count / 11) + 10;

	if (now_image != next_image)
	{
		now_image = next_image;
	}

	if (animation_count >= 30)
	{
		animation_count = 0;
	}
}

// �p���V���[�g��Ԃ̏���
void Enemy::Parachute()
{
	if (enemy_start_x == -100.0f)
	{
		// �p���V���[�g��ԂɂȂ���x���W�̕ێ�
		enemy_start_x = location.x;
		// �������x�̐ݒ�
		enemy_speed = 0.5f;
	}

	animation_count++;

	// �摜��15, 16, 17
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

	// enemu_start_x�𒆐S�ɍ��E�ɗh��鏈��
	location.x = (sinf(angle2) * amplitude) + enemy_start_x;

	// ��������
	location.y += enemy_speed;

	// �����ɒ��񂾂玀�S
	if (location.y >= 480)
	{
		enemy_death = TRUE;
		enemy_delete = TRUE;
	}
}

// ������Ԃ̏���
void Enemy::Upright()
{
	if (enemy_start_x != -100.0f)
	{
		// �p���V���[�g��ԗp�̕ϐ��̏����l���
		angle = 0;
		enemy_start_x = -100.0f;
		animation_count = 0;
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
		animation_count = 0;
		// �G�̏�ԑJ��
		enemy_state = EnemyState::kInflatBealloon;
	}
}

// ���S���̏���
void Enemy::Death()
{
	// �摜��13, 14�i2���j
	animation_count++;

	// ���S���̃A�j���[�V����
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
	if (move_y <= 10)
	{
		move_y++;
		// ������ɏオ��
		location.y--;
	}
	else
	{
		location.y++;
	}

	// �����ɒ��񂾂�Q�[�����C���ō폜
	if (location.y >= 480)
	{
		 enemy_delete = TRUE;
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

// �������ɒ��˕Ԃ�
void Enemy::BoundDown()
{
	// ����
	// �����x�̉e���𑬓x�ɗ^����
	enemy_speed -= acceleration / 3600;
	
	// �G�̈ړ�
	location.x += move_x * enemy_speed * bounce_coefficient;
	location.y += move_y * enemy_speed * bounce_coefficient;

	if (enemy_speed <= 0.0f)
	{
		enemy_speed = 0.0f;
		bound_flg = FALSE;
	}
}

// �t���O�̐ݒ�
void Enemy::SetBoundFlg(int set_flg)
{
	bound_flg = set_flg;
}

// �G�̕��㏈��
void Enemy::Levitation(void)
{
	// �p���[�A�b�v����
	if (power_up_flg == TRUE)
	{
		// �^�C�v�̕ύX
		enemy_type++;

		// �����x�̐ݒ�
		enemy_speed = 0.0f;

		power_up_flg = FALSE;
	}

	levitation_count++;

	if (levitation_count <= 180)
	{
		// �V��ɓ��������璵�˕Ԃ�
		if (location.y - (erea.width / 2 * erea.height_rate) <= 0)
		{
			move_y = 1.0f;
			bound_flg = TRUE;
			levitation_flg = FALSE;
		}

		// �����̏���
		Inertia();

		// �G�̈ړ�
		location.x += move_x * enemy_speed;
		location.y -= move_y * enemy_speed / 2;
	}
	else
	{
		levitation_flg = FALSE;
		levitation_count = 0;
	}
}

// �G�̕���t���O�̐ݒ�
void Enemy::SetLevitationFlg(int set_flg)
{
	levitation_flg = set_flg;
}

// �G�̎��S�t���O�̎擾
int Enemy::GetEnemyDeathFlg()
{
	return enemy_death;
}

// �G�̎��S�t���O�̐ݒ�
void Enemy::SetEnemyDeathFlg(int flg)
{
	enemy_death = flg;
}

// �G�̍폜�t���O�̎擾
int Enemy::GetEnemyDeleteFlg()
{
	return enemy_delete;
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
