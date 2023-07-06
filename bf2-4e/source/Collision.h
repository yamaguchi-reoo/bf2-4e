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