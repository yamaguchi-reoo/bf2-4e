#pragma once

class UI
{
private:
	int score;	//�X�R�A
	

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
