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
class BoxCollider
{
protected:
	Location location;
	Erea erea;
	
public:
	bool HitBox(BoxCollider* bCollider);

	Location GetLocation()const;

	void GetErea()const;

	void SetLocation()const;
};