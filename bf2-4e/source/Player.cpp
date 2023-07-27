#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"
#include "math.h"

#define DIRECTION_LEFT		(0)
#define DIRECTION_RIGHT		(1)

// �ÓI�����o�ϐ��̒�`
float Player::get_location_x;
float Player::get_location_y;

Player::Player()
{
	direction = DIRECTION_LEFT;		// �����̌����i���j
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
}
Player::~Player()
{

}
void Player::Update()
{
	//PlayerGroundWalk();
	PlayerFlight();
	Move();
	//MoveLocation();
	HitCeiling();
	PlayerFalling();
	move_y += player_gravity;
	location.y += move_y;
	location.x += move_x;
	get_location_x = location.x;
	get_location_y = location.y;
}

void Player::Draw()const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[0], TRUE, direction);
	DrawBoxAA(location.x - ((erea.width / 2.f) * erea.width_rate), 
	location.y - ((erea.height / 2.f) * erea.height_rate), 
	location.x - ((erea.width / 2.f) * erea.width_rate) + erea.width,
	location.y - ((erea.height / 2.f) * erea.height_rate) + erea.height,
	0xff00ff, FALSE);
	DrawFormatString(0, 400, 0xffffff, "move_x = %3f, move_y = %3f", move_x, move_y);
}

//�v���C���[�̈ړ�
void Player::Move()
{
	//�E
	if (0.4f < PadInput::TipLeftLStick(STICKL_X))
	{
		//�v���C���[�̌���(�E)
		direction = DIRECTION_RIGHT;
		//�v���C���[�̈ړ�(�E(�n�ʂɂ�����))
		if (ground_flg == 0)
		{
			move_x += 2.0f;
		}
		else if (ground_flg == 1 && (PadInput::OnButton(XINPUT_BUTTON_X) == 1 || PadInput::OnPressed(XINPUT_BUTTON_B) == 1))
		{
			move_x += 2.0f;
		}
		else
		{
			move_x += 0.04f;
		}
	}

	//��
	if (PadInput::TipLeftLStick(STICKL_X) < -0.4f)
	{
		//�v���C���[�̌���(��)
		direction = DIRECTION_LEFT;
		//�v���C���[�̈ړ�(��(�n�ʂɂ�����))
		if (ground_flg == 0)
		{
			move_x -= 2.0f;
		}
		else if (ground_flg == 1 && (PadInput::OnButton(XINPUT_BUTTON_X) == 1 || PadInput::OnPressed(XINPUT_BUTTON_B) == 1))
		{
			move_x -= 2.0f;
		}
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
}

//�v���C���[�̒n�ʂł̕��s����
void Player::PlayerGroundWalk()
{
	//player_flg = 0;
	ground_flg = 0;
	if((PadInput::OnButton(XINPUT_BUTTON_X) == 0 && ground_flg == 0) || 
		(PadInput::OnButton(XINPUT_BUTTON_B) == 0 && ground_flg == 0))
	{
		move_y = -player_gravity;
	}
}

//�v���C���[�̋󒆏��
void Player::PlayerFlight()
{
	if (PadInput::OnButton(XINPUT_BUTTON_A) == 1|| PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
	{
		ground_flg = 1;
		player_images[17];
	}
}

void Player::HitCeiling()
{
	if (location.y < 16.f)
	{
		location.y = 24.f;
		if(move_y < 0)
		{
			move_y = move_y * -0.8f;
		}
	}
}

void Player::PlayerFalling()
{
	if (PadInput::OnButton(XINPUT_BUTTON_A) == 1)
	{
		ground_flg = 1;
		move_y += -1.5f;
	}
	if (ground_flg == 1 && PadInput::OnPressed(XINPUT_BUTTON_B) == 1)	//B�{�^���������Ă���Ԃ��v���C���[�������Ԃ̎�
	{
		ground_flg = 1;
		move_y += -0.2f;
	}
	if (move_y < -5)
	{
		move_y = -5.f;
		move_y = move_y * 0.8f;
	}
}

bool Player::PlayerFlg() {
	if (ground_flg == 0) {
		return true;
	}
	
	return  false;
}
void Player::PlayerReversalFlg() {
	ground_flg = !ground_flg;
	//player_flg = !player_flg;
}

void  Player::Bounce()
{
	if (move_y < 0)
	{
		move_y = move_y * -0.8f;
	}
}