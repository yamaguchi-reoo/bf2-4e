#pragma once

class Player
{
public:
	int PlayerImages[30];

public:
	Player();			//�R���X�g���N�^
	~Player();			//�f�X�g���N�^
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
	void Draw()const;	//�`��Ɋւ��邱�Ƃ���������
};