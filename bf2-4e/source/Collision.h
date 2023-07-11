#pragma once

struct Location		//’†SÀ•W
{
	float x;			
	float y;
};
struct Erea				//”ÍˆÍ
{
	float height;		//‚‚³
	float width;		//•
	float height_rate;	//‚‚³‚Ì”{—¦
	float width_rate;	//•‚Ì”{—¦
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