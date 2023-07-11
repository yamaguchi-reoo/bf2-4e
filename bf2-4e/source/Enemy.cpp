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

	enemy_x = 0;
	enemy_y = 0;
	enemy_speed = 0;

	fps_count = 0;
	//animation_pattern_number = 0;
	second = 0;

	inflat_bealloon_count = 0;

	now_image = 0;
	next_image = 0;

	enemy_state = EnemyState::kInflatBealloon;

	mouse_x = 0;
	mouse_y = 0;
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
	// �X�e�[�W�P�ɓG�̉摜�̕`��
	//DrawRotaGraph(200, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);

	// �b���̕`��
	DrawFormatString(10, 10, 0xFFFFFF, "�b��%5d", second);

	// �}�E�X�̍��W�̕`��
	DrawFormatString(10, 100, 0xffffff, "mouse_x = %3d, mouse_y = %3d", mouse_x, mouse_y);

	// ���F�̓G�摜�̕`��
	//DrawRotaGraph(200 + enemy_x, 252 + enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, FALSE);


	switch (enemy_state)
	{
	case Enemy::EnemyState::kInflatBealloon:
		// ���D��c��܂��؂�ƕ����オ��
		DrawRotaGraph(200, 252 - enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, FALSE);
		break;
	case Enemy::EnemyState::kFlight:
		DrawRotaGraph(200 + enemy_x, 252 + enemy_y, 1, 0, enemy_pink_image[now_image], TRUE, FALSE);
		break;
	case Enemy::EnemyState::kParachute:
		break;
	case Enemy::EnemyState::kUpright:
		break;
	case Enemy::EnemyState::kDeath:
		break;
	default:
		break;
	}

}

// �G�̏㉺���E�ړ�����
void Enemy::EnemyMove()
{
	
	enemy_x = 0;
	enemy_y = 0;
}

// �G�̉���s������
void Enemy::Avoidance()
{
	// �G���E�������Ă���Ƃ�
	enemy_x++;

	// �G�����������Ă���Ƃ�
	enemy_x--;
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
		//animation_pattern_number = next_image;
	}

	if (inflat_bealloon_count >= 180 && enemy_y <= 20)
	{
		// �G�𕂏コ����
		enemy_y++;

		// ���㎞�̉摜�֐؂�ւ�
		now_image = 8;
	}
	else if(inflat_bealloon_count >= 180)
	{
		// �J�E���g��0�ɖ߂�
		inflat_bealloon_count = 0;

		// �G�̏�ԑJ��
		enemy_state = EnemyState::kFlight;
	}

}

// �󒆂ŉH�΂����A�j���[�V��������
void Enemy::Flight()
{

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
	if (enemy_y >= 480)
	{

	}
}
