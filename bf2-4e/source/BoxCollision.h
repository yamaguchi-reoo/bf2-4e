#pragma once
#include "Struct.h"

class BoxCollision
{
protected:
	Location location;
	Erea erea;
	Object object[8];
	

public:
	bool HitBox(BoxCollision* bCollider);

	Location GetLocation()const;

	Erea GetErea()const;

	void SetLocation(Location location);
};
