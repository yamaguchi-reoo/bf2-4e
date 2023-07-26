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
	location.y = 386.0;
	erea.width = 64.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;
	player_gravity = 0.03f;

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
	MoveLocation();
	HitCeiling();
	PlayerFalling();
	move_y += player_gravity;
	location.x += move_x;
	location.y += move_y;
	get_location_x = location.x;
	get_location_y = location.y;
	move_x = 0;
}

void Player::Draw()const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[0], TRUE, direction);
	DrawBoxAA(location.x - ((erea.width / 2.f) * erea.width_rate), 
			location.y - ((erea.height / 2.f) * erea.height_rate), 
			location.x - ((erea.width / 2.f) * erea.width_rate) + erea.width,
			location.y - ((erea.height / 2.f) * erea.height_rate) + erea.height,
			0xff00ff, FALSE);
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
		move_x += 2.0f;
	}

	//��
	if (PadInput::TipLeftLStick(STICKL_X) < -0.4f)
	{
		//�v���C���[�̌���(��)
		direction = DIRECTION_LEFT;
		//�v���C���[�̈ړ�(��)
		move_x -= 2.0f;
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
	player_flg = 0;
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
	if (PadInput::OnButton(XINPUT_BUTTON_X) == 1|| PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
	{
		ground_flg = 1;
		player_images[17];
	}
}

void Player::HitCeiling()
{
	if (location.y < 16)
	{
		location.y = 24;
		if(move_y < 0)
		{
			move_y = move_y * -0.8;
		}
	}
}

void Player::PlayerFalling()
{
	if (PadInput::OnButton(XINPUT_BUTTON_X) == 1)
	{
		ground_flg = 1;
		move_y += -1.5f;
	}
	if (ground_flg == 1 && PadInput::OnPressed(XINPUT_BUTTON_B) == 1)	//B�{�^���������Ă���Ԃ��v���C���[�������Ԃ̎�
	{
		ground_flg = 1;
		move_y += -0.2f;
	}
}
bool Player::PlayerBackLash() {
	

	if (ground_flg == 0) {
		return true;
	}
	
	return  false;
}
void Player::PlayerBack() {
	ground_flg = !ground_flg;
	//player_flg = !player_flg;
}

int  Player::adsfg()
{
	return  gravity_A;
}