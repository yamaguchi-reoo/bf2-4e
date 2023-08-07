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

	a_button_flg = 0;
	fly_cnt = 0;
}
Player::~Player()
{

}

void Player::Update()
{
	/************ プレイヤー操作に関する処理 ************/

	//Aボタンが押されたかを判定する処理
	AButtonFlg();
	// Aボタンが押された時
	if (a_button_flg == 1)
	{
		//浮上用カウントを１０にする
		fly_cnt = 10;
		//プレイヤーを落下状態にする
		ground_flg = 1;
	}
	//浮上用カウントが０より大きい場合
	if (fly_cnt > 0)
	{
		//プレイヤーを2ずつ浮上させる
		move_y = -2.f;
		//浮上用カウントを1ずつ減らす
		fly_cnt -= 1;
	}
	/*ButtonAInterval();*/
	//プレイヤーの地面での歩行動作
	//PlayerGroundWalk();
	if (ground_flg == 1)
	{
		move_y += player_gravity;
	}
	location.y += move_y;
	location.x += move_x;
	get_location_x = location.x;
	get_location_y = location.y;
	move_x = 0.0f;
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
	DrawFormatString(300, 400, 0xffffff, "fly_cnt %d", fly_cnt);
}

////Aボタンを押したときのインターバル処理
//void Player::ButtonAInterval()
//{
//	//Aボタンが押されている間かつ浮上状態の時
//	if (PadInput::OnPressed(XINPUT_BUTTON_A) == 1)
//	{
//		//浮上状態になる
//		ground_flg = 1;
//		move_y -= 4.0f;
//		//10フレーム経つまで上昇し続ける
//		for (int i = 0; i<100; i++)
//		{
//
//		}
//		//100フレーム経ったらY座標の移動量を0にする
//		move_y = 0;
//	}
//}

//Aボタンが押された時のフラグの切り替え
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

//プレイヤーの地面での歩行動作
void Player::PlayerGroundWalk()
{
	//player_flg = 0;
	ground_flg = 0;
	if ((PadInput::OnButton(XINPUT_BUTTON_A) == 0 && ground_flg == 0) ||
		(PadInput::OnPressed(XINPUT_BUTTON_B) == 0 && ground_flg == 0))
	{
		//player_gravity;
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
