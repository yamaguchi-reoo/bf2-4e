#pragma once

class UI
{
private:
	// �X�R�A�摜�����p�̕ϐ�
	int numimage[4];
	
	//�X�R�A�����p�摜�̕ϐ�
	int score;
	int hiscore;
	
	//���C�t�p
	int stock;

	//�|�[�Y�p�ϐ�
	bool pauseState;
	bool pauseFlag;
	bool pauseReset;

public:
	//�R���X�g���N�^
	UI();

	//�f�X�g���N�^
	~UI();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;
};
