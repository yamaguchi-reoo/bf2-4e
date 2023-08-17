#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"
#include "math.h"

#define DIRECTION_LEFT		(0)
#define DIRECTION_RIGHT		(1)
#define MAX_MOVE_X			(3.0f)

// �ÓI�����o�ϐ��̒�`
float Player::get_location_x;
float Player::get_location_y;

Player::Player()
{
	direction = DIRECTION_RIGHT;		// �����̌����i���j
	for (int i = 0; i < 30; i++)
	{
		player_images[i] = NULL;
	}
	LoadDivGraph("Source/Resource/images/Player/Player_Animation.png",30,8,4,64,64, player_images);

	ground_flg = 1;
	location.x = 40.0;
	location.y = 384.8f;
	erea.width = 32.0f;
	erea.height = 62.0f;
	erea.width_rate = 1.0f;
	erea.height_rate = 1.0f;
	player_gravity = 0.08f;

	get_location_x = 0.0f;
	get_location_y = 0.0f;

	move_x = 0.0f;
	move_y = 0.0f;

	a_button_flg = 0;
	fly_cnt = 0;
	inertia = 0.05f;
	x_count = 12;

	now_image = 0;
	next_image = 1;
	animation_interval = 1;

	player_state = PlayerState::kStandBalloon2;
	state_image = 0;
	anim_count = 10;
	//player_state_image = player_images[0];
	anim_flg = 0;

	flying_images = player_images[16];
}

Player::~Player()
{

}

void Player::Update()
{
	/**************�A�j���[�V�����p�J�E���^�[����************/
	if (anim_count <= -1)
	{
		anim_count = 10;
	}
	/******************* �{�^�����쏈�� *********************/

	//A�{�^���������ꂽ���𔻒肷�鏈��
	AButtonFlg();
	if (a_button_flg == 1)		// A�{�^���������ꂽ��
	{
		fly_cnt = 15;			//����p�J�E���g���P�O�ɂ���
		ground_flg = 1;			//�v���C���[�𗎉���Ԃɂ���
	}
	if (fly_cnt > 0)			//����p�J�E���g���O���傫���ꍇ
	{
		move_y = -2.f;			//�v���C���[��1�����コ����

		player_state = PlayerState::kFlyingBalloon2;	//�v���C���[�̉摜��Ԃ𕂏��Ԃɂ���

		fly_cnt -= 1;			//����p�J�E���g��1�����炷
	}
	/*********************************************************/
	/**					�v���C���[�̍��E�ړ�				**/
	/*********************************************************/

	//���X�e�B�b�N�̌X���̊������E������4���ȏ�̏ꍇ
	if (0.2f < PadInput::TipLeftLStick(STICKL_X))
	{
		//�󒆂ɂ���ꍇ
		if ((move_x < MAX_MOVE_X) && ground_flg == 1)
		{
			//�v���C���[�̈ړ��ʂ�1.0�����Z����
			move_x += 0.1f;

			//���㏈�����s���Ă����ꍇ
			if (0 < fly_cnt)
			{
				move_x += 0.9f;
			}
		}
		//�n�ʂɂ���ꍇ
		else if ((move_x < MAX_MOVE_X) && ground_flg == 0)
		{
			//�v���C���[�̈ړ��ʂ�3.0�����Z����
			move_x += 1.0f;
		}

		//�v���C���[�̌������E�����ɕύX����
		direction = DIRECTION_RIGHT;
	}

	//���X�e�B�b�N�̌X���̊������������ɂS���ȏ�̏ꍇ
	if (PadInput::TipLeftLStick(STICKL_X) < -0.2)
	{
		if (-MAX_MOVE_X < move_x && ground_flg == 1)
		{
			//�v���C���[�̂w���W����1.0�����Z����
			move_x -= 0.f;

			//���㏈�����s���Ă����ꍇ
			if (0 < fly_cnt)
			{
				move_x += -0.5f;
			}
		}
		if (-MAX_MOVE_X < move_x && ground_flg == 0)
		{
			//�v���C���[�̂w���W����1.0�����Z����
			move_x += -1.0f;
		}
		//�v���C���[�̌������������ɕύX����
		direction = DIRECTION_LEFT;
	}
	if ((PadInput::TipLeftLStick(STICKL_X) < 0.1f)
		&& (-0.1 < PadInput::TipLeftLStick(STICKL_X))
		&& ground_flg == 0)
	{
		move_x = 0.0f;
	}
	//�v���C���[����ʉE�[���z�����ꍇ�A��ʔ��΂̒[�Ƀ��[�v����
	if (640 < (location.x - (erea.width / 2)))
	{
		location.x = -15;
	}
	//�v���C���[����ʍ��[���z�����ꍇ�A��ʔ��΂̒[�Ƀ��[�v����
	if ((location.x + (erea.width / 2)) < 0)
	{
		location.x = 655;
	}

	/***************** �V��ł̔��� ********************/
	//�V��ł̔���
	HitCeiling();

	if (ground_flg == 1)			//�v���C���[���󒆏�Ԃ̎�
	{
		move_y += player_gravity;	//�v���C���[�ɏd�͂�������
		inertia = 0.05f;			//�����͂�^����B
	}

	if (ground_flg == 0)
	{
		player_state = PlayerState::kStandBalloon2;
	}

	Animation();
	PlayerGroundState();

	location.y += move_y;
	location.x += move_x;
	get_location_x = location.x;
	get_location_y = location.y;
}

void Player::Draw()const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[state_image], TRUE, direction);
	DrawBoxAA(location.x - ((erea.width / 2.f) * erea.width_rate), 
	location.y - ((erea.height / 2.f) * erea.height_rate), 
	location.x - ((erea.width / 2.f) * erea.width_rate) + erea.width,
	location.y - ((erea.height / 2.f) * erea.height_rate) + erea.height,
	0xff00ff, FALSE);
	DrawFormatString(0, 400, 0xffffff, "move_x = %3f, move_y = %3f", move_x, move_y);
	DrawFormatString(300, 400, 0xffffff, "fly_cnt %d", fly_cnt);
	DrawFormatString(300, 100, 0xffffff, "anim_count %d", anim_count);
	DrawFormatString(300, 120, 0xffffff, "anim_flg %d", anim_flg);
	DrawFormatString(300, 140, 0xffffff, "state_image %d", state_image);
}

//A�{�^���������ꂽ���̃t���O�̐؂�ւ�
int Player::AButtonFlg()
{
	if (PadInput::OnButton(XINPUT_BUTTON_A) == 1)
	{
		a_button_flg = 1;
	}
	else
	{
		a_button_flg = 0;
	}

	return a_button_flg;
}

//�v���C���[�̈ړ�
//void Player::Move()
//{
//	if (0.4f < PadInput::TipLeftLStick(STICKL_X))
//	{
//		//�v���C���[�̌���(�E)
//		direction = DIRECTION_RIGHT;
//
//		//�v���C���[�̈ړ�(�E(�n�ʂɂ�����))
//		if (ground_flg == 0)
//		{
//			move_x += 2.0f;
//		}
//
//		//B�{�^���������{���X�e�B�b�N�̉E���͎��̃v���C���[�ړ�
//		if (ground_flg == 1 && PadInput::OnButton(XINPUT_BUTTON_A) == 1)
//		{
//			move_y -= 12.0f;
//			move_x += 12.0f;
//		}
//	}
//	if (PadInput::OnButton(XINPUT_BUTTON_A) == 1)
//	{
//		ground_flg = 1;
//		move_y -= 2.0f;
//	}
//	//��
//	if (PadInput::TipLeftLStick(STICKL_X) < -0.4f)
//	{
//		//�v���C���[�̌���(��)
//		direction = DIRECTION_LEFT;
//		//�v���C���[�̈ړ�(��(�n�ʂɂ�����))
//		if (ground_flg == 0)
//		{
//			move_x -= 2.0f;
//		}
//		//B�{�^���������{���X�e�B�b�N�̉E���͎��̃v���C���[�ړ�
//		if (ground_flg == 1 && PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
//		{
//			move_x -= 2.0f;
//		}
//	}
//	//�v���C���[����ʉE�[���z�����ꍇ�A��ʔ��΂̒[�Ƀ��[�v����
//	if (640 < (location.x - (erea.width / 2)))
//	{
//		location.x = -15;
//	}
//	//�v���C���[����ʍ��[���z�����ꍇ�A��ʔ��΂̒[�Ƀ��[�v����
//	if ((location.x + (erea.width / 2)) < 0)
//	{
//		location.x = 655;
//	}
//}

//�v���C���[�̋󒆏��
void Player::PlayerFlight()
{
	if (PadInput::OnButton(XINPUT_BUTTON_A) == 1 || PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
	{
		ground_flg = 1;
	}
}

//�V��ɂԂ������ꍇ�̔�������
void Player::HitCeiling()
{
	if (location.y < 16.f)
	{
		location.y = 24.f;
		if (move_y < 0)
		{
			move_y = move_y * -2.0f;
		}
	}
}

//�v���C���[�̒n�ʏ�ԗp�֐�
void Player::PlayerGroundState()
{
	if (ground_flg = 0)
	{
		player_state = PlayerState::kStandBalloon2;
		state_image = 0;
	}
}

bool Player::PlayerFlg() 
{
	if (ground_flg == 0) 
	{
		return true;
	}
	
	return  false;
}

void Player::PlayerReversalFlg() {
	ground_flg = !ground_flg;
}

void  Player::Bounce()
{
	if (move_y < 0)
	{
		move_y = move_y * -0.8f;
	}
}
float Player::GetLocationX()
{
	return location.x;
}
float Player::GetLocationY()
{
	return location.y;
}

void Player::PlayerReset()
{
	ground_flg = 1;
	location.x = 40.0f;
	location.y = 384.8f;
	erea.width = 32.0f;
	erea.height = 62.0f;
}

/******************** �A�j���[�V�������� ***********************/
void Player::Animation()
{
	/************ �n�ʂɗ����Ă��鎞�̃A�j���[�V���� *************/
	if ((player_state == PlayerState::kStandBalloon2) && (anim_flg == 0)
		&& (ground_flg == 0))
	{
		//�A�j���[�V�����J�E���g���O���傫���ꍇ
		if (0 < anim_count)
		{
			//���t���[�����Z����
			anim_count -= 1;
		}
		else if (anim_count <= 0)
		{
			//�A�j���[�V�����J�E���g���O�ɂȂ����ꍇ�A�摜�p�ϐ��ɂP���Z����
			state_image = (++state_image % 3);
			//player_state_image = player_images[state_image];
			anim_count -= 1;
		}
		if (state_image >= 2)
		{
			anim_flg = 1;
		}
	}
	else if ((player_state == PlayerState::kStandBalloon2) && (anim_flg == 1))
	{
		if (0 < anim_count)
		{
			anim_count -= 1;
		}
		else if (anim_count <= 0)
		{
			state_image -= 1;
			//player_state_image = player_images[state_image];
			anim_count -= 1;
		}
		if (state_image <= 0)
		{
			anim_flg = 0;
		}
	}
	/*************** ������Ԃ̎��̃A�j���[�V���� ****************/
	if ((player_state == PlayerState::kFlyingBalloon2) && (anim_flg == 0)
		&& (state_image <= 21) && (ground_flg == 1))
	{
		if (0 < anim_count)
		{
			anim_count -= 1;
		}
		else if (anim_count <= 0)
		{
			state_image = (++state_image % 5) + 16;
			//player_state_image = player_images[state_image];
			anim_count -= 1;
		}
		if (state_image >= 21)
		{
			anim_flg = 1;
		}
	}
	else if ((player_state == PlayerState::kFlyingBalloon2) && (anim_flg == 1) 
		&& (state_image <= 16) && (ground_flg == 1))
	{
		if (0 < anim_count)
		{
			anim_count -= 1;
		}
		else if (anim_count <= 0)
		{
			state_image = (--state_image % 5) + 16;
			//player_state_image = player_images[state_image];
			anim_count -= 1;
		}
		if (state_image <= 16)
		{
			anim_flg = 0;
		}
	}
}