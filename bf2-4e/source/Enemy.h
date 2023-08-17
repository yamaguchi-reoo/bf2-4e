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
	float enemy_speed;						// �����x
	float acceleration;						// �����x
	float bounce_coefficient;				// �����W��
	int enemy_type;							// �G�̎�ށi0�F���F�@1�F�ΐF�@2�F�ԐF�j
	int power_up_flg;						// �p���[�A�b�v�̃t���O�iTRUE:�p���[�A�b�v����@FALSE:�p���[�A�b�v���Ȃ��j
	int enemy_death;						// �G�̐�����ԁiTRUE:���S�@FALSE:�����j
	int enemy_delete;						// �G�̍폜�iTRUE:�폜�j
	int bound_flg;							// �G�̒��˕Ԃ��ԁi1:���˕Ԃ�@0:���˕Ԃ�Ȃ��j
	int levitation_flg;						// �G�̕���iTRUE:���シ��j

	// �ړ�����Ƃ��̌v�Z�Ɏg���ϐ�
	float abs_x;							// X���W�̐�Βl
	float abs_y;							// Y���W�̐�Βl
	float distance_x;						// X���W�̋���
	float distance_y;						// Y���W�̋���

	// �A�j���[�V�����p�J�E���g
	int inflat_bealloon_count;				// ���D��c��܂�����܂ł̃J�E���g
	//int flight_count;						// �H�΂����A�j���[�V�����p�J�E���g
	int animation_count;					// �A�j���[�V�����p�J�E���g
	int levitation_count;					// ���シ��J�E���g

	int now_image;							// ������\�������摜
	int next_image;							// ���ɕ\�������摜

	// �ǂ�������Ώۂ̍��W
	float player_x;							// �v���C���[��X���W
	float player_y;							// �v���C���[��Y���W

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

	int avoidance_count;					// �������
	int avoidance_flg;						// ����s���̃t���O
	float difference_y;						// ����s���̏����p�̃v���C���[�ƓG�̍��W�̍�

public:
	EnemyState enemy_state;					// �G�̏��

	// �R���X�g���N�^
	Enemy(float set_x, float set_y, int set_type);
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

	// �����̏���
	void Inertia();

	// ���D��c��܂��鏈��
	void InflatBealloon();

	// �󒆂ŉH�΂����A�j���[�V��������
	void Flight();

	// �󒆗����A�j���[�V��������
	void AirFall();

	// �p���V���[�g��Ԃ̏���
	void Parachute();

	// ������Ԃ̏���
	void Upright();

	// ���S���̏���
	void Death();

	// �v���C���[�Ƃ̍��W�̍����擾���邩�̔��菈��
	void CkeckPlayerLocation();

	// X���W�̃��[�v��������̍��W�ύX����
	void AfterWarp();

	// �������ɒ��˕Ԃ�
	void BoundDown();

	// �G�̒��˕Ԃ�t���O�̐ݒ�
	void SetBoundFlg(int set_flg);

	// ���シ�鏈��
	void Levitation(void);

	// �G�̕���t���O�̐ݒ�
	void SetLevitationFlg(int set_flg);

	// �G�̎��S�t���O�̎擾
	int GetEnemyDeathFlg();

	// �G�̎��S�t���O�̐ݒ�
	void SetEnemyDeathFlg(int flg);

	// �G�̍폜�t���O�̎擾
	int GetEnemyDeleteFlg();

	//�V���{���ʃX�|�[�����̓G�̏�Ԃ���̔��f���邽�߂̏���
	bool EnemyStateJudgment(void);

	public:
		static float get_location_x;		// �G��X���W�Q�Ɨp�̕ϐ�
		static float get_location_y;		// �G�̂�Y���W�Q�Ɨp�̕ϐ�
};

