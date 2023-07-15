#pragma once

enum class EnemyState
{
	kInflatBealloon = 0,				// ���D��c��܂���
	kFlight,							// �󒆂ŉH�΂���
	kParachute,							// �p���V���[�g
	kUpright,							// ����
	kDeath								// ���S
};

class Enemy
{
private:
	// �摜�p�ϐ�
	int enemy_pink_image[18];				// ���F�̓G�̉摜
	int enemy_green_image[18];				// �ΐF�̓G�̉摜
	int enemy_red_image[18];				// �ԐF�̓G�̉摜

	// �G�̏��
	float enemy_x;							// �G��X���W
	float enemy_y;							// �G��Y���W
	float enemy_speed;						// �G�̃X�s�[�h
	int enemy_angle;						// �G�̈ړ��p�x
	int enemy_type;							// �G�̎�ށi0�F���F�@1�F�ΐF�@2�F�ԐF�j
	int power_up_flg;						// �p���[�A�b�v�̃t���O�iTRUE:�p���[�A�b�v����@FALSE:�p���[�A�b�v���Ȃ��j

	// �ړ�����Ƃ��̌v�Z�Ɏg���ϐ�
	float xc;								// �O�����̒藝�i�ΕӁj
	float yc;								// �O�����̒藝�i�ΕӁj
	float x;
	float y;

	int fps_count;							// fps�̃J�E���g
	int second;								// �b���̃J�E���g

	// �A�j���[�V�����p�J�E���g
	int inflat_bealloon_count;				// ���D��c��܂�����܂ł̃J�E���g
	int flight_count;						// �H�΂����A�j���[�V�����p�J�E���g

	int now_image;							// ������\�������摜
	int next_image;							// ���ɕ\�������摜

	EnemyState enemy_state;					// �G�̏��

	// �ǂ�������Ώۂ̍��W
	int mouse_x;							// �}�E�X��X���W�i�v���C���[�̍��W�ɕς��j
	int mouse_y;							// �}�E�X��Y���W�i�v���C���[�̍��W�ɕς��j

	float radian;							// �G�ƃv���C���[�̊p�x�i�ʓx�@�j
	float degree;							// �G�ƃv���C���[�̊p�x�i�x���@�j

	// �ړ�����Ƃ��Ɏg���ϐ�
	float move_x;							// �G�̍��WX�̈ړ���
	float move_y;							// �G�̍��WY�̈ړ���

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

	// �󒆗����A�j���[�V��������
	void AirFall();

	// �p���V���[�g��Ԃ̃A�j���[�V��������
	void Parachute();

	// ������Ԃ̏���
	void Upright();

	// ���S���̃A�j���[�V��������
	void Death();
};

