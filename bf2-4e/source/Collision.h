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
struct Object 
{
	float x;
	float y;
	float h;
	float w;
};
class BoxCollider
{
protected:
	Location location;
	Erea erea;
	Object stage[8];

public:
	bool HitBox(BoxCollider* bCollider);

	Location GetLocation()const;

	Erea GetErea()const;

	void SetLocation()const;
};