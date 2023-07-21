#pragma once
#include "Struct.h"

class BoxCollision
{
private:

protected:
	Location location;
	Erea erea;
	


public:
	bool HitBox(BoxCollision* bCollider);

	Location GetLocation()const;

	Erea GetErea()const;

	void SetLocation(Location location);
	
	bool HitTopBox(BoxCollision* bCollider);
};
