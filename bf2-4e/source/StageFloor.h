#pragma once
#include"BoxCollision.h"
#include"common.h"

class StageFloor :public BoxCollision
{
private:

	//画像用変数
	int floor_image01;
	int sea_image;
	int stage_number;
public:
	//コンストラクタ
	StageFloor(int i, int _stage);
	//デストラクタ
	~StageFloor();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

};

