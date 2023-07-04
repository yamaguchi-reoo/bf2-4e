#include "DxLib.h"
#include "Player.h"
#include "PadInput.h"

Player::Player()
{
	for (int i = 0; i < 30; i++)
	{
		PlayerImages[i];
	}
	LoadDivGraph("Source/Resource/images/Player/Player_Animation.png",30,8,4,64,64, PlayerImages);
	
}
Player::~Player()
{

}
void Player::Update()
{
	
}
void Player::Draw()const
{
	DrawRotaGraph(250, 250, 1, 0, PlayerImages[0], TRUE, FALSE);
}
void Player::PlayerDash()
{
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A) == 1)
	{
		PlayerImages
	}
}