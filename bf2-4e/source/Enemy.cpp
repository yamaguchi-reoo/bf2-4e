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

	LoadDivGraph("Source/Resource/images/Enemy/Enemy_P_Animation.png", 19, 8, 3, 64, 64, enemy_pink_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_G_Animation.png", 19, 8, 3, 64, 64, enemy_green_image);
	LoadDivGraph("Source/Resource/images/Enemy/Enemy_R_Animation.png", 19, 8, 3, 64, 64, enemy_red_image);

    //if (LoadDivGraph("images/block.bmp", 19, 8, 3, 32, 32, enemy_pink_image) == -1);
}

// �f�X�g���N�^
Enemy::~Enemy()
{

}

// �`��ȊO�̍X�V������
void Enemy::Update()
{

}

// �`��Ɋւ��邱�Ƃ�����
void Enemy::Draw() const
{
	// �X�e�[�W�P�ɓG�̉摜�̕`��
	DrawRotaGraph(200, 252, 1, 0, enemy_pink_image[0], TRUE, FALSE);
	DrawRotaGraph(300, 252, 1, 0, enemy_pink_image[0], TRUE, FALSE);
	DrawRotaGraph(400, 252, 1, 0, enemy_pink_image[0], TRUE, FALSE);

}
