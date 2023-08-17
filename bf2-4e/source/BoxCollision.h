#pragma once
#include "Struct.h"

class BoxCollision
{
private:
	int old_location_top;
	int old_location_bottom;

protected:
	Location location;
	Erea erea;
	
public:
	bool HitBox(BoxCollision* bCollider);

	Location GetLocation()const;

	Erea GetErea()const;

	void SetLocation(Location location);
	
	bool HitTopBox(BoxCollision* bCollider);

	bool EnemyHitBox(BoxCollision* bCollider);
	bool EnemyHitTopBox(BoxCollision* bCollider);

	// ���D�����̓����蔻��
	bool HitBealloon(BoxCollision* bCollider);
	// �̕����̓����蔻��
	bool HitBody(BoxCollision* bCollider);
};