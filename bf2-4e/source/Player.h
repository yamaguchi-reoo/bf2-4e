#pragma once
#include "BoxCollision.h"

#define MAX_FLYING_DIAMETER (1.2)

class Player :public BoxCollision
{
private:
	int player_images[30];	//プレイヤーのイメージ画像
	int player_flg;			//0:地面にいる状態　１：落下状態
	int direction;			//プレイヤーの向き
	int speed_x;			//プレイヤーの速度(x座標)
	float speed_y;			//プレイヤーの速度(y座標)
	float flying_diameter;		//プレイヤーの上昇

	int move_x;
	int move_y;
	int player_angle;

public:
	void Move();				//プレイヤーの移動
	void NotTipMove();
	void PlayerFlight();		//プレイヤーの空中状態
	void PlayerGroundWalk();	//プレイヤーの地面歩行
	void MaxDiameter();			//プレイヤーの上昇倍率
	void MoveLocation();		//プレイヤーの移動範囲

	void PlayerBackLash();

public:
	Player();			//コンストラクタ
	~Player();			//デストラクタ	
	void Update();		//描画以外に関することを実装する
	void Draw()const;	//描画に関することを実装する

public:
	static float get_location_x;		// プレイヤーのX座標参照用の変数
	static float get_location_y;		// プレイヤーのY座標参照用の変数

};