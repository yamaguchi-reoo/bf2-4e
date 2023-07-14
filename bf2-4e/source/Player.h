#pragma once
#include "BoxCollision.h"

class Player :public BoxCollision
{
private:
	int player_images[30];
	int player_flg; //0:地面にいる状態　１：落下状態
	int direction;			// プレイヤーの向き

public:
	void Move();		//プレイヤーの移動
	void NotTipMove();
	void PlayerFlight();		//プレイヤーの空中状態
	void PlayerGroundWalk();	//プレイヤーの地面歩行

public:
	Player();			//コンストラクタ
	~Player();			//デストラクタ	
	void Update();		//描画以外に関することを実装する
	void Draw()const;	//描画に関することを実装する
};