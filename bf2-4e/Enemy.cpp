#include "Enemy.h"
#include "DxLib.h"

// �R���X�g���N�^
Enemy::Enemy()
{
    // ����������
    try
    {
        //�摜�Ǎ�
        LoadDivGraph("source/Resource/images/Enemy/Enemy_G_Animation.png", 19, 8, 3, 32, 32, enemy_pink_image);

        ////LogoImage = LoadGraph("source/Resource/images/Title/Title_Logo.png");
        //if (enemy_pink_image == -1)
        //{
        //    throw "source/Resource/images/Title/Title_Logo.png";
        //}
    }
    catch (int& err)
    {
        printf("�G���[�R�[�h%d\n", err);
    }

    if (LoadDivGraph("images/block.bmp", 19, 8, 3, 32, 32, enemy_pink_image) == -1);


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

}
