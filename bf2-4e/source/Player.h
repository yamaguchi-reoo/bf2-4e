#pragma once
#include "BoxCollision.h"

class Player :public BoxCollision
{
	enum class PlayerState
	{
		kStandBalloon2,
		kStandBalloon1,
		kDashBalloon2,
		kDashBalloon1,
		kFlyingBalloon2,
		kFlyingBalloon1,
		kDeath,
		kElectrocution
	};
private:
	/*******************    変数宣言    ********************/

	int player_images[30];		//プレイヤーのイメージ画像

	bool ground_flg;			//0:地面にいる状態　１：落下状態
	int a_button_flg;			//0:Aボタンが押されていない 1:押されてた
	int a_count;				//Bボタンの処理
	int fly_cnt;				//浮上時間制御変数
	int direction;				//プレイヤーの向き
	float player_gravity;		//プレイヤーにかかる重力

	float move_x;				//プレイヤーの移動量(横)
	float move_y;				//プレイヤーの移動量(縦)
	int x_count;				//X座標移動時のカウントダウン用変数

	int now_image;				//現在の画像
	int next_image;				//次に画面に表示する画像
	int animation_interval;		//アニメーション用のインターバル変数
	int state_image;			//イメージ画像の配列用変数

	PlayerState player_state;	//プレイヤーの状態用変数
	int anim_count;				//アニメーション用カウンター
	int anim_flg;				//アニメーション用切り替えフラグ	0:カウントアップ　1:カウントダウン

	int flying_images;			//浮上状態時の画像格納用変数

public:
	/*******************    関数宣言    ********************/

	void PlayerGroundState();	//プレイヤーの地面歩行
	void HitCeiling();			//プレイヤーの移動範囲

	bool PlayerFlg();			//立っているか判断する
	void PlayerReversalFlg();	//フラグを反転させる
	void Bounce();				//反発（仮）
	float GetLocationX();		//プレイヤーのX座標
	float GetLocationY();		//プレイヤーのY座標
	void PlayerReset();			//プレイヤーを初期位置に

	int AButtonFlg();			//Aボタンが押されたときのフラグ処理

	void Animation();			//プレイヤーアニメーション

public:
	Player();					//コンストラクタ
	~Player();					//デストラクタ	
	void Update();				//描画以外に関することを実装する
	void Draw()const;			//描画に関することを実装する

public:
	static float get_location_x;		// プレイヤーのX座標参照用の変数
	static float get_location_y;		// プレイヤーのY座標参照用の変数

};