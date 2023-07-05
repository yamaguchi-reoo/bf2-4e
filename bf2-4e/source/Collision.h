#pragma once

struct Location		//中心座標
{
	float x;			
	float y;
};
struct Erea			//範囲
{
	float height;		//高さ
	float width;		//幅
	float height_rate;	//高さの倍率
	float width_rate;	//幅の倍率
};
class BoxCollider
{
private:
	Location location;
	Erea erea;

public:
	BoxCollider();		//コンストラクタ
	~BoxCollider();		//デストラクタ
	void Update();		//描画以外に関することを実装する
};