#include "Enemy.h"
#include "DxLib.h"

// �R���X�g���N�^
Enemy::Enemy()
{
	for (int i = 0; i < 19; i++)
	{
		enemy_pink_image[i];
		enemy_green_image[i];
		enemy_red_image[i];
	}
	// �G�̉摜�̓Ǎ�
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_P_Animation.png", 19, 8, 3, 64, 64, enemy_pink_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_G_Animation.png", 19, 8, 3, 64, 64, enemy_green_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_R_Animation.png", 19, 8, 3, 64, 64, enemy_red_image);

	fps_count = 0;
	animation_pattern_number = 0;
}

// �f�X�g���N�^
Enemy::~Enemy()
{

}

// �`��ȊO�̍X�V������
void Enemy::Update()
{
	fps_count++;

	if (fps_count >= 60)
	{
		// fps�̃J�E���g��0�ɖ߂�
		fps_count = 0;
	}

	// ���D��c��܂���A�j���[�V��������
	InflatBealloon();
}

// �`��Ɋւ��邱�Ƃ�����
void Enemy::Draw() const
{
	// �X�e�[�W�P�ɓG�̉摜�̕`��
	DrawRotaGraph(200, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);
	DrawRotaGraph(300, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);
	DrawRotaGraph(400, 252, 1, 0, enemy_pink_image[animation_pattern_number], TRUE, FALSE);

}

// ���D��c��܂���A�j���[�V��������
void Enemy::InflatBealloon()
{
	if (fps_count <= 30)
	{
		animation_pattern_number = 1;
	}
	else
	{
		animation_pattern_number = 0;
	}
}
