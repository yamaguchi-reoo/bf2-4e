#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"
#include "math.h"

#define DIRECTION_LEFT		(1)
#define DIRECTION_MIDDLE	(0)
#define DIRECTION_RIGHT		(-1)

Player::Player()
{
	direction = DIRECTION_LEFT;		// 初期の向き（左）
	for (int i = 0; i < 30; i++)
	{
		player_images[i] = NULL;
	}
	LoadDivGraph("Source/Resource/images/Player/Player_Animation.png",30,8,4,64,64, player_images);
	
	player_flg = 1;
	location.x = 40.0;
	location.y = 416.0;
	erea.width = 64.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;
}
Player::~Player()
{

}
void Player::Update()
{
	//PlayerGroundWalk();
	PlayerFlight();
	Move();

	location.y += 0.3;
}

void Player::Draw()const
{
	if (direction > DIRECTION_MIDDLE)
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[0], TRUE, FALSE);
	}
	else
	{
		DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[0], TRUE, TRUE);
	}	
	//DrawBox(location.x - (erea.width / 2), location.y - (erea.height / 2), location.x - (erea.width / 2), location.y + (erea.height / 2), 0xff00ff, FALSE);
	DrawBox(location.x - ((erea.width / 2) * erea.width_rate), location.y - ((erea.height / 2) * erea.height_rate), location.x - ((erea.width / 2) * erea.width_rate) + erea.width, location.y - ((erea.height / 2) * erea.height_rate) + erea.height, 0xff00ff, FALSE);
}

//プレイヤーの移動
void Player::Move()
{
	// migi
	if (0.4f < PadInput::TipLeftLStick(STICKL_X))
	{
		direction = DIRECTION_RIGHT;
		location.x += 1.0f;
	}

	// hidari
	if (PadInput::TipLeftLStick(STICKL_X) < -0.4)
	{
		direction = DIRECTION_LEFT;
		location.x -= 1.0f;
	}
	
	//右側
	if (640 < (location.x - (erea.width / 2)))
	{
		location.x = -30;
	}
	//左側
	if ((location.x + (erea.width / 2)) < 0)
	{
		 location.x = 670;
	}
}

//プレイヤーの地面での歩行動作
void Player::PlayerGroundWalk()
{
	player_flg = 0;
	if(PadInput::OnButton(XINPUT_BUTTON_X) == 0 && player_flg == 0)
	{
		player_images[1];
		location.y = 0;
	}

}

//プレイヤーの空中状態
void Player::PlayerFlight()
{
	if (PadInput::OnButton(XINPUT_BUTTON_X) == 1)
	{
		player_flg = 1;
		location.y -= 4;
		player_images[17];

	}
	if (PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
	{
		player_flg = 1;
		location.y -= 0.5;
		player_images[17];

	}
}
void Player::PlayerBackLash()
{

}
