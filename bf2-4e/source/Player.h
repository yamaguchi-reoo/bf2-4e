#pragma once
#include "BoxCollision.h"

#define MAX_FLYING_DIAMETER (1.20f)

class Player :public BoxCollision
{
private:
	int player_images[30];	//プレイヤーのイメージ画像
	bool ground_flg;		//0:地面にいる状態　１：落下状態
	int direction;			//プレイヤーの向き
	float player_gravity;	//プレイヤーにかかる重力

	float move_x;			//プレイヤーの移動量(横)
	float move_y;			//プレイヤーの移動量(縦)

public:
	void Move();				//プレイヤーの移動
	void PlayerFlight();		//プレイヤーの空中状態
	void PlayerGroundWalk();	//プレイヤーの地面歩行
	void HitCeiling();			//プレイヤーの移動範囲
	void PlayerFalling();		//プレイヤーにかかる重力

	bool PlayerFlg();			//立っているか判断する
	void PlayerReversalFlg();	//フラグを反転させる
	void Bounce();				//反発（仮）
	int GetLocationX();
	int GetLocationY();
	void PlayerReset();
public:
	Player();			//コンストラクタ
	~Player();			//デストラクタ	
	void Update();		//描画以外に関することを実装する
	void Draw()const;	//描画に関することを実装する

public:
	static float get_location_x;		// プレイヤーのX座標参照用の変数
	static float get_location_y;		// プレイヤーのY座標参照用の変数

};