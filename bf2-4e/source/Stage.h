#pragma once

class Stage 
{
private:
	int stage_number;//�X�e�[�W���p�ϐ�

	int stage_image01;
	int stage_image02;
	int stage_image03;
	int stage_image04;
public:
	//�R���X�g���N�^
	Stage();
	//�f�X�g���N�^
	~Stage();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;
};
