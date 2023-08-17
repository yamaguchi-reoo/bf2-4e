#pragma once
#include "BoxCollision.h"
#include "Player.h"

class Bubble :public BoxCollision
{
private:
	int BubbleImage[4];

	int animation_count;					// �A�j���[�V�����p�J�E���g

	int delete_count;						//�����p�J�E���g

	int now_image;							// ������\�������摜
	int next_image;							// ���ɕ\�������摜

	float PosX;		// �`����WX
	float PosY;		// �`����WY
	float Radius;		// ���a(�`��p)
	float CenterX;	// ���S���WX
	float CenterY;	// ���S���WY
	float Angle;		// �p�x
	float Length;		// ���a�̒���

	bool GetFlg;		//�Q�b�g�t���O(true:Get false:NotGet)

	bool DrawFlg;		//�摜�̕`��t���O(true:�`�悷�� false:�`�悵�Ȃ�)

	int scoreimage;		//�X�R�A�摜�\���p
	
public:
	//�R���X�g���N�^
	Bubble(float posX,float posY, bool drawflg, bool getflg);

	//�f�X�g���N�^
	~Bubble();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

	//�V���{���ʂ̃A�j���[�V�����֐�
	void BubbleAnimation(void);

	//�V���{���ʂ̈ړ�
	void MoveBubble(void);

	//�Q�b�g�t���O�ύX
	void ChangeGetFlg(void);

	//�`��t���O�̎Q��
	int GetDrawFlg(void);

	//�擾�t���O�̎Q��
	int GetGetFlg(void);

public:
	static float NowUpdateBubble;
};
