#pragma once

struct Location		//���S���W
{
	float x;			
	float y;
};
struct Erea			//�͈�
{
	float height;		//����
	float width;		//��
	float height_rate;	//�����̔{��
	float width_rate;	//���̔{��
};
class BoxCollider
{
private:
	Location location;
	Erea erea;

public:
	BoxCollider();		//�R���X�g���N�^
	~BoxCollider();		//�f�X�g���N�^
	void Update();		//�`��ȊO�Ɋւ��邱�Ƃ���������
};