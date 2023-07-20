#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"
#include "math.h"

#define DIRECTION_LEFT		(0)
#define DIRECTION_RIGHT		(1)

float Player::GetPlayerX()
{
	return location.x;
}

float Player::GetPlayerY()
{
	return location.y;
}

Player::Player()
{
	direction = DIRECTION_LEFT;		// �����̌����i���j
	for (int i = 0; i < 30; i++)
	{
		player_images[i] = NULL;
	}
	LoadDivGraph("Source/Resource/images/Player/Player_Animation.png",30,8,4,64,64, player_images);
	
	player_flg = 1;
	location.x = 180.0;
	location.y = 284.0;
	erea.width = 64.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;
	speed_x = -20.0f;
	speed_y = -1.5f;
	flying_diameter = 0.04f;
	gravity_A = 0.7f;

}
Player::~Player()
{

}
void Player::Update()
{
	PlayerGroundWalk();
	PlayerFlight();
	Move();
	MoveLocation();
	PlayerGravity();
	player_flg = 1;
}

void Player::Draw()const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[0], TRUE, direction);
	DrawFormatString(0, 30, 0xffffff,"flying_diameter �h%f�h", flying_diameter);
}

//�v���C���[�̈ړ�
void Player::Move()
{
	//�E
	if (0.4f < PadInput::TipLeftLStick(STICKL_X))
	{
		//�v���C���[�̌���(�E)
		direction = DIRECTION_RIGHT;
		//�v���C���[�̈ړ�(��)
		location.x += 1.0f;
	}

	//��
	if (PadInput::TipLeftLStick(STICKL_X) < -0.4f)
	{
		//�v���C���[�̌���(��)
		direction = DIRECTION_LEFT;
		//�v���C���[�̈ړ�(��)
		location.x -= 1.0f;
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
	if(PadInput::OnButton(XINPUT_BUTTON_X) == 0 && player_flg == 0)
	{
		player_images[1];
	}
}

//�v���C���[�̋󒆏��
void Player::PlayerFlight()
{
	if (PadInput::OnButton(XINPUT_BUTTON_X) == 1|| PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
	{
		player_flg = 1;
		player_images[17];
		location.y += speed_y;
	}
}

void Player::MoveLocation()
{
	if (location.y < 16)
	{
		location.y += speed_y * -10;
	}
}

void Player::PlayerGravity()
{

	if (player_flg == 1 && PadInput::OnButton(XINPUT_BUTTON_X) == 1)
	{
		location.y += gravity_A;
		gravity_A -= 0.35f;
	}
	if (player_flg == 1 && PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
	{
		location.y += gravity_A;
		gravity_A -= 0.03f;
	}
	if (player_flg == 1 && PadInput::OnButton(XINPUT_BUTTON_X) == 0)
	{
		gravity_A += 0.02f;
		location.y += gravity_A;
	}
}