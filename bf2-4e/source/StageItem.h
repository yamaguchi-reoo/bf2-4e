#pragma once

class StageItem
{
private:
	//�摜�p�ϐ�
	int thunder_image[2];
	int fish_image;

	//�A�j���[�V�����̑ҋ@�ϐ�
	int time;
	int anime_num;

public:
	//�R���X�g���N�^
	StageItem();

	//�f�X�g���N�^
	~StageItem();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

};

