#pragma once
#include "Player.h"
#include "BoxCollision.h"

// �G�̏��
enum class EnemyState
{
	kInflatBealloon = 0,				// ���D��c��܂���
	kFlight,							// �󒆂ŉH�΂���
	kParachute,							// �p���V���[�g
	kUpright,							// ����
	kDeath								// ���S
};

// �����蔻�肠��
class Enemy : public BoxCollision
{
private:
	// �摜�p�ϐ�
	int enemy_pink_image[18];				// ���F�̓G�̉摜
	int enemy_green_image[18];				// �ΐF�̓G�̉摜
	int enemy_red_image[18];				// �ԐF�̓G�̉摜

	// �G�̏��
	//float enemy_x;							// �G��X���W
	//float enemy_y;							// �G��Y���W
	float enemy_speed;						// �G�̃X�s�[�h
	float acceleration;						// �����x
	int enemy_angle;						// �G�̈ړ��p�x
	int enemy_type;							// �G�̎�ށi0�F���F�@1�F�ΐF�@2�F�ԐF�j
	int power_up_flg;						// �p���[�A�b�v�̃t���O�iTRUE:�p���[�A�b�v����@FALSE:�p���[�A�b�v���Ȃ��j
	int enemy_life;							// �G�̐�����ԁiTRUE:�����Ă���@FALSE:���S�j

	int inertia_count;						// �����������J�E���g
	int inertia_flg;

	// �ړ�����Ƃ��̌v�Z�Ɏg���ϐ�
	float xc;								// �O�����̒藝�i�ΕӁj
	float yc;								// �O�����̒藝�i�ΕӁj
	float x;								// �v�Z��move_x�ɑ���p
	float y;								// �v�Z��move_y�ɑ���p

	// ��ŏ������
	int fps_count;							// fps�̃J�E���g
	int second;								// �b���̃J�E���g

	// �A�j���[�V�����p�J�E���g
	int inflat_bealloon_count;			// ���D��c��܂�����܂ł̃J�E���g
	//int flight_count;						// �H�΂����A�j���[�V�����p�J�E���g
	int animation_count;					// �A�j���[�V�����p�J�E���g

	int avoidance_count;					// �������Ƃ��̎���

	int now_image;							// ������\�������摜
	int next_image;							// ���ɕ\�������摜

	EnemyState enemy_state;					// �G�̏��

	// �ǂ�������Ώۂ̍��W
	float player_x;							// �v���C���[��X���W
	float player_y;							// �v���C���[��Y���W
	//int mouse_x;							// �}�E�X��X���W�i�v���C���[�̍��W�ɕς��j
	//int mouse_y;							// �}�E�X��Y���W�i�v���C���[�̍��W�ɕς��j

	// �ړ�����Ƃ��Ɏg���ϐ�
	float move_x;							// �G�̍��WX�̈ړ���
	float move_y;							// �G�̍��WY�̈ړ���

	int turn_flg;							// �摜�̍��E���]��ԁiTRUE:���]�@FALSE:���ʂɕ`��j
	int old_turn_flg;						// �O��̉摜�̏�Ԃ�ۑ�

	int ckeck_flg;							// �v���C���[�Ƃ̍��W�̍����擾����t���O
	int ckeck_count;						// ckeck_flg�p�J�E���g

	float angle;							// �p���V���[�g��Ԃ̍��E�ړ��p
	float angle2;							// �p���V���[�g��Ԃ̍��E�ړ��p
	float amplitude;						// �p���V���[�g��Ԃŉ��~����Ƃ��̐U�ꕝ
	float enemy_start_x;					// �p���V���[�g��ԂɂȂ���x���W

	int avoidance_flg;						// ����s���̃t���O

	float difference_y;						// ����s���̏����p�̃v���C���[�ƓG�̍��W�̍�

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

	// �v���C���[�Ƃ̍��W�̍����擾���邩�̔��菈��
	void CkeckPlayerLocation();

	// X���W�̃��[�v��������̍��W�ύX����
	void AfterWarp();
};

