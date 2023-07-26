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
};
