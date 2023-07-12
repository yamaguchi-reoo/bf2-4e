#pragma once

enum class EnemyState
{
	kInflatBealloon,					// ���D��c��܂���
	kFlight,							// �󒆂ŉH�΂���
	kParachute,							// �p���V���[�g
	kUpright,							// ����
	kDeath								// ���S
};

class Enemy
{
private:
	// �摜�p�ϐ�
	int enemy_pink_image[19];				// ���F�̓G�̉摜
	int enemy_green_image[19];				// �ΐF�̓G�̉摜
	int enemy_red_image[19];				// �ԐF�̓G�̉摜

	int enemy_x;							// �G��X���W
	int enemy_y;							// �G��Y���W
	int enemy_speed;						// �G�̃X�s�[�h
	int enemy_angle;						// �G�̈ړ��p�x
	float c;

	int fps_count;							// fps�̃J�E���g
	int second;								// �b���̃J�E���g

	int inflat_bealloon_count;				// ���D��c��܂�����܂ł̃J�E���g

	int now_image;							// ������\�������摜
	int next_image;							// ���ɕ\�������摜

	EnemyState enemy_state;					// �G�̏��

	int mouse_x;							// �}�E�X��X���W
	int mouse_y;							// �}�E�X��Y���W

	float radian;							// �G�ƃv���C���[�̊p�x

	int move_x;								// �G�̍��WX�̈ړ���
	int move_y;								// �G�̍��WY�̈ړ���

	int turn_flg;							// �摜�̍��E���]��ԁiTRUE:���]�@FALSE:���ʂɕ`��j

public:
	// �R���X�g���N�^
	Enemy();
	// �f�X�g���N�^
	~Enemy();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

	// �G�̏㉺���E�ړ�����
	void EnemyMove();

	// �G�̉���s������
	void Avoidance();

	// ���D��c��܂���A�j���[�V��������
	void InflatBealloon();

	// �󒆂ŉH�΂����A�j���[�V��������
	void Flight();

	// �p���V���[�g��Ԃ̃A�j���[�V��������
	void Parachute();

	// ������Ԃ̏���
	void Upright();

	// ���S���̃A�j���[�V��������
	void Death();
};

