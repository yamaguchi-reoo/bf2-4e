#pragma once
#include "BoxCollision.h"

class Player :public BoxCollision
{
private:
	int player_images[30];
	int player_flg; //0:地面にいる状態　１：落下状態
	float player_x1;
	float player_y1;
	float player_x2;
	float player_y2;

public:
	void PlayerFlight();
	void PlayerGroundWalk();	//プレイヤーの地面での動作

public:
	Player();			//コンストラクタ
	~Player();			//デストラクタ	
	void Update();		//描画以外に関することを実装する
	void Draw()const;	//描画に関することを実装する
};