#pragma once

class UI
{
private:
	// �X�R�A�摜�ϐ�
	int scoreimage[4];
	
	//�X�R�A�����̕ϐ�
	int score;

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
