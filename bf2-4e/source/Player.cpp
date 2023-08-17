#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"
#include "math.h"

#define DIRECTION_LEFT		(0)
#define DIRECTION_RIGHT		(1)
#define MAX_MOVE_X			(3.0f)

// 静的メンバ変数の定義
float Player::get_location_x;
float Player::get_location_y;

Player::Player()
{
	direction = DIRECTION_RIGHT;		// 初期の向き（左）
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
	/**************アニメーション用カウンター処理************/
	if (anim_count <= -1)
	{
		anim_count = 10;
	}
	/******************* ボタン操作処理 *********************/

	//Aボタンが押されたかを判定する処理
	AButtonFlg();
	if (a_button_flg == 1)		// Aボタンが押された時
	{
		fly_cnt = 15;			//浮上用カウントを１０にする
		ground_flg = 1;			//プレイヤーを落下状態にする
	}
	if (fly_cnt > 0)			//浮上用カウントが０より大きい場合
	{
		move_y = -2.f;			//プレイヤーを1ずつ浮上させる

		player_state = PlayerState::kFlyingBalloon2;	//プレイヤーの画像状態を浮上状態にする

		fly_cnt -= 1;			//浮上用カウントを1ずつ減らす
	}
	/*********************************************************/
	/**					プレイヤーの左右移動				**/
	/*********************************************************/

	//左スティックの傾きの割合が右方向に4割以上の場合
	if (0.2f < PadInput::TipLeftLStick(STICKL_X))
	{
		//空中にいる場合
		if ((move_x < MAX_MOVE_X) && ground_flg == 1)
		{
			//プレイヤーの移動量に1.0を加算する
			move_x += 0.1f;

			//浮上処理が行われていた場合
			if (0 < fly_cnt)
			{
				move_x += 0.9f;
			}
		}
		//地面にいる場合
		else if ((move_x < MAX_MOVE_X) && ground_flg == 0)
		{
			//プレイヤーの移動量に3.0を加算する
			move_x += 1.0f;
		}

		//プレイヤーの向きを右方向に変更する
		direction = DIRECTION_RIGHT;
	}

	//左スティックの傾きの割合が左方向に４割以上の場合
	if (PadInput::TipLeftLStick(STICKL_X) < -0.2)
	{
		if (-MAX_MOVE_X < move_x && ground_flg == 1)
		{
			//プレイヤーのＸ座標から1.0を減算する
			move_x -= 0.f;

			//浮上処理が行われていた場合
			if (0 < fly_cnt)
			{
				move_x += -0.5f;
			}
		}
		if (-MAX_MOVE_X < move_x && ground_flg == 0)
		{
			//プレイヤーのＸ座標から1.0を減算する
			move_x += -1.0f;
		}
		//プレイヤーの向きを左方向に変更する
		direction = DIRECTION_LEFT;
	}
	if ((PadInput::TipLeftLStick(STICKL_X) < 0.1f)
		&& (-0.1 < PadInput::TipLeftLStick(STICKL_X))
		&& ground_flg == 0)
	{
		move_x = 0.0f;
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

	/***************** 天井での反射 ********************/
	//天井での反射
	HitCeiling();

	if (ground_flg == 1)			//プレイヤーが空中状態の時
	{
		move_y += player_gravity;	//プレイヤーに重力をかける
		inertia = 0.05f;			//慣性力を与える。
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

//プレイヤーの移動
//void Player::Move()
//{
//	if (0.4f < PadInput::TipLeftLStick(STICKL_X))
//	{
//		//プレイヤーの向き(右)
//		direction = DIRECTION_RIGHT;
//
//		//プレイヤーの移動(右(地面にいる状態))
//		if (ground_flg == 0)
//		{
//			move_x += 2.0f;
//		}
//
//		//Bボタン長押し＋左スティックの右入力時のプレイヤー移動
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
//	//左
//	if (PadInput::TipLeftLStick(STICKL_X) < -0.4f)
//	{
//		//プレイヤーの向き(左)
//		direction = DIRECTION_LEFT;
//		//プレイヤーの移動(左(地面にいる状態))
//		if (ground_flg == 0)
//		{
//			move_x -= 2.0f;
//		}
//		//Bボタン長押し＋左スティックの右入力時のプレイヤー移動
//		if (ground_flg == 1 && PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
//		{
//			move_x -= 2.0f;
//		}
//	}
//	//プレイヤーが画面右端を越えた場合、画面反対の端にワープする
//	if (640 < (location.x - (erea.width / 2)))
//	{
//		location.x = -15;
//	}
//	//プレイヤーが画面左端を越えた場合、画面反対の端にワープする
//	if ((location.x + (erea.width / 2)) < 0)
//	{
//		location.x = 655;
//	}
//}

//プレイヤーの空中状態
void Player::PlayerFlight()
{
	if (PadInput::OnButton(XINPUT_BUTTON_A) == 1 || PadInput::OnPressed(XINPUT_BUTTON_B) == 1)
	{
		ground_flg = 1;
	}
}

//天井にぶつかった場合の反発処理
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

//プレイヤーの地面状態用関数
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

/******************** アニメーション処理 ***********************/
void Player::Animation()
{
	/************ 地面に立っている時のアニメーション *************/
	if ((player_state == PlayerState::kStandBalloon2) && (anim_flg == 0)
		&& (ground_flg == 0))
	{
		//アニメーションカウントが０より大きい場合
		if (0 < anim_count)
		{
			//毎フレーム減算する
			anim_count -= 1;
		}
		else if (anim_count <= 0)
		{
			//アニメーションカウントが０になった場合、画像用変数に１加算する
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
	/*************** 落下状態の時のアニメーション ****************/
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