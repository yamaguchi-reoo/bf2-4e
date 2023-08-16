#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"
#include "math.h"

#define DIRECTION_LEFT		(0)
#define DIRECTION_RIGHT		(1)

// 静的メンバ変数の定義
float Player::get_location_x;
float Player::get_location_y;

Player::Player()
{
	direction = DIRECTION_LEFT;		// 初期の向き（左）
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
	DrawFormatString(0, 400, 0xffffff, "move_x = %3f, move_y = %3f", move_x, move_y);

	//DrawBox(location.x - ((erea.width / 2) * erea.width_rate), location.y, location.x - ((erea.width / 2) * erea.width_rate) + erea.width, location.y - ((erea.height / 2) * erea.height_rate) + erea.height, 0xffffff, FALSE);
}

//プレイヤーの移動
void Player::Move()
{
	//右
	if (0.4f < PadInput::TipLeftLStick(STICKL_X))
	{
		//プレイヤーの向き(右)
		direction = DIRECTION_RIGHT;
		//プレイヤーの移動(右(地面にいる状態))
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

	//左
	if (PadInput::TipLeftLStick(STICKL_X) < -0.4f)
	{
		//プレイヤーの向き(左)
		direction = DIRECTION_LEFT;
		//プレイヤーの移動(左(地面にいる状態))
		if (ground_flg == 0)
		{
			move_x -= 2.0f;
		}
		else if (ground_flg == 1 && (PadInput::OnButton(XINPUT_BUTTON_X) == 1 || PadInput::OnPressed(XINPUT_BUTTON_B) == 1))
		{
			move_x -= 2.0f;
		}
	}

	//プレイヤーが画面右端を越えた場合、画面反対の端にワープする
	if (640 < (location.x - (erea.width / 2)))
	{
		location.x = -15;
	}
	//プレイヤーが画面左端を越えた場合、画面反対の端にワープする
	if ((location.x + (erea.width / 2)) < 0)
	{
		 location.x = 655;
	}
}

//プレイヤーの地面での歩行動作
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

//プレイヤーの空中状態
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
	if (ground_flg == 1 && PadInput::OnPressed(XINPUT_BUTTON_B) == 1)	//Bボタンを押している間かつプレイヤーが浮上状態の時
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
int Player::GetLocationX()
{
	return location.x;
}
int Player::GetLocationY()
{
	return location.y;
}

void Player::PlayerReset()
{
	ground_flg = 1;
	location.x = 40.0;
	location.y = 384.8f;
	erea.width = 32.0f;
	erea.height = 62.0f;
}
