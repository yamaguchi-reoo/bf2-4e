#pragma once

struct Location		//中心座標
{
	float x;			
	float y;
};
struct Erea				//範囲
{
	float height;		//高さ
	float width;		//幅
	float height_rate;	//高さの倍率
	float width_rate;	//幅の倍率
};
struct Object			//オブジェクト
{
	float x;			//横
	float y;			//縦
	float h;			//高さ
	float w;			//幅
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