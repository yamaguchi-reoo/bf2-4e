#pragma once

struct Location		//���S���W
{
	float x;			
	float y;
};
struct Erea				//�͈�
{
	float height;		//����
	float width;		//��
	float height_rate;	//�����̔{��
	float width_rate;	//���̔{��
};
struct Object			//�I�u�W�F�N�g
{
	float x;			//��
	float y;			//�c
	float h;			//����
	float w;			//��
};
class BoxCollider
{
protected:
	Location location;
	Erea erea;
	Object object[8];

public:
	bool HitBox(BoxCollider* bCollider);

	Location GetLocation()const;

	Erea GetErea()const;

	void SetLocation(Location location);
};