#pragma once

class Enemy
{
private:
	// �摜�ϐ�
	int enemy_pink_image[19];				// ���F�̓G�̉摜
	int enemy_green_image[19];				// �ΐF�̓G�̉摜
	int enemy_red_image[19];				// �ԐF�̓G�̉摜

public:
	// �R���X�g���N�^
	Enemy();
	// �f�X�g���N�^
	~Enemy();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

