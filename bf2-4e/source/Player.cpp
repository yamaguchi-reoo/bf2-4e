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
	
	player_flg = 1;
	location.x = 40.0;
	location.y = 300.0;
	erea.width = 64.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;
	speed_x = -20.0f;
	speed_y = -1.5f;
	flying_diameter = 0.04f;
	gravity_A = 0.7f;

	get_location_x = 0.0f;
	get_location_y = 0.0f;

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
	
	//player_flg = 1;
	//location.y += 0.6f;
	get_location_x = location.x;
	get_location_y = location.y;

	if (player_flg == 1) {
		location.y += 0.6f;
		PlayerGravity();
	}
}

void Player::Draw()const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[0], TRUE, direction);
	DrawFormatString(0, 30, 0xffffff,"flying_diameter ”%f”", flying_diameter);
	DrawBox(location.x - ((erea.width / 2) * erea.width_rate), location.y - ((erea.height / 2) * erea.height_rate), location.x - ((erea.width / 2) * erea.width_rate) + erea.width, location.y - ((erea.height / 2) * erea.height_rate) + erea.height, 0xff00ff, FALSE);
}

//プレイヤーの移動
void Player::Move()
{
	//右
	if (0.4f < PadInput::TipLeftLStick(STICKL_X))
	{
		//プレイヤーの向き(右)
		direction = DIRECTION_RIGHT;
		//プレイヤーの移動(左)
		location.x += 1.0f;
	}

	//左
	if (PadInput::TipLeftLStick(STICKL_X) < -0.4f)
	{
		//プレイヤーの向き(左)
		direction = DIRECTION_LEFT;
		//プレイヤーの移動(左)
		location.x -= 1.0f;
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
	player_flg = 0;
	gravity_A = 0.0f;
	if(PadInput::OnButton(XINPUT_BUTTON_X) == 0 && player_flg == 0)
	{
		player_images[1];
	}
}

//プレイヤーの空中状態
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

		gravity_A -= 0.10f;
	}
	if (player_flg == 1 && PadInput::OnButton(XINPUT_BUTTON_X) == 0)
	{
		gravity_A += 0.02f;
		location.y += gravity_A;
	}
}
bool Player::PlayerBackLash() {
	

	if (player_flg == 0) {
		return true;
	}
	
	return  false;
}
void Player::PlayerBack() {
	player_flg = !player_flg;
}