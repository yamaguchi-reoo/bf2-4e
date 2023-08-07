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

	a_button_flg = 0;
	fly_cnt = 0;
}
Player::~Player()
{

}

void Player::Update()
{
	/************ �v���C���[����Ɋւ��鏈�� ************/

	//A�{�^���������ꂽ���𔻒肷�鏈��
	AButtonFlg();
	// A�{�^���������ꂽ��
	if (a_button_flg == 1)
	{
		//����p�J�E���g���P�O�ɂ���
		fly_cnt = 10;
		//�v���C���[�𗎉���Ԃɂ���
		ground_flg = 1;
	}
	//����p�J�E���g���O���傫���ꍇ
	if (fly_cnt > 0)
	{
		//�v���C���[��2�����コ����
		move_y = -2.f;
		//����p�J�E���g��1�����炷
		fly_cnt -= 1;
	}
	/*ButtonAInterval();*/
	//�v���C���[�̒n�ʂł̕��s����
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

////A�{�^�����������Ƃ��̃C���^�[�o������
//void Player::ButtonAInterval()
//{
//	//A�{�^����������Ă���Ԃ������Ԃ̎�
//	if (PadInput::OnPressed(XINPUT_BUTTON_A) == 1)
//	{
//		//�����ԂɂȂ�
//		ground_flg = 1;
//		move_y -= 4.0f;
//		//10�t���[���o�܂ŏ㏸��������
//		for (int i = 0; i<100; i++)
//		{
//
//		}
//		//100�t���[���o������Y���W�̈ړ��ʂ�0�ɂ���
//		move_y = 0;
//	}
//}

//A�{�^���������ꂽ���̃t���O�̐؂�ւ�
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

//�v���C���[�̒n�ʂł̕��s����
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
