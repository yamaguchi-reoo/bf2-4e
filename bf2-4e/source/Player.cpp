#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"
#include "math.h"

Player::Player()
{
	for (int i = 0; i < 30; i++)
	{
		player_images[i];
	}
	LoadDivGraph("Source/Resource/images/Player/Player_Animation.png",30,8,4,64,64, player_images);
	
	player_flg = 1;
	location.x = 100.0;
	location.y = 385.0;
	erea.width = 64.0;
	erea.height = 64.0;
	erea.width_rate = 1.0;
	erea.height_rate = 1.0;
	player_x1 = location.x - (erea.width * erea.width_rate);
	player_y1 = location.y - (erea.height * erea.height_rate);
	player_x2 = player_x1 + erea.width;
	player_y2 = player_y1 + erea.height;
}
Player::~Player()
{

}
void Player::Update()
{
	player_x1 = location.x - ((erea.width/2) * erea.width_rate);
	player_y1 = location.y - ((erea.height/2) * erea.height_rate);
	player_x2 = player_x1 + erea.width;
	player_y2 = player_y1 + erea.height;
	PlayerGroundWalk();
	PlayerFlight();
	location.y += 0.1;
}
void Player::Draw()const
{
	DrawRotaGraph((int)location.x, (int)location.y, 1, 0, player_images[0], TRUE, FALSE);

	DrawFormatString(100, 100, 0xffffff, "x1:%f y1:%f,x2:%f y2:%f", player_x1, player_y1, player_x2, player_y2);

	DrawBox(player_x1, player_y1, player_x2, player_y2, 0xff0000, FALSE);
}
void Player::PlayerGroundWalk()
{
	player_flg = 0;
	if(PadInput::OnButton(XINPUT_BUTTON_X) == 0 && player_flg == 0)
	{
		player_images[1];
	}
}
void Player::PlayerFlight()
{
	if (PadInput::OnButton(XINPUT_BUTTON_X) == 1)
	{
		player_flg = 1;
		location.y -= 2;
	}
}