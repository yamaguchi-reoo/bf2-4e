#pragma once
#include "Fps.h"
#include"BoxCollision.h"
#include "math.h"
#define _USE_MATH_DEFINES


class Thunder:public BoxCollision
{
private:
	/* 画像用変数 */
	//雷
	int thunder_cloud_image[3];
	int thunder_image[6];
	int thunder_effect_image[3];

	/*アニメーションの待機用変数*/
	//雷雲
	int cloud_X;				//雲のX座標
	int cloud_Y;				//雲のY座標
	int cloud_anime_num;

	int thunder_cloud_frame = 60;	//制限時間
	int thunder_cloud_anime_frame;	//雷雲のアニメーション用のフレーム

	//雷雲のアニメーション
	int thunder_cloud_time;	
	int thunder_cloud_anime_num;	//雷雲の画像のループ

	//稲光
	int thunder_time_anime;			//稲光のアニメーション
	int thunder_anime_num;			//稲光の画像のループ
	
	int thunder_frame = 60;			//制限時間
	int thunder_anime_frame;		//稲光のアニメーション用のフレーム

	bool is_thunder_shoot_ready;	//稲光を出すかどうか
	bool thunder_shoot_flg;			//稲光が出ているどうか

	//雷モドキ
	int thunder_effect_time_anime;			//雷モドキのアニメーション

	int thunder_effect_time = 60;			//制限時間
	int thunder_effect_anime_num;			//雷モドキの画像のループ

	bool thunder_effect_shoot_flg;			//雷モドキが出ているどうか
	bool is_thunder_effect_shoot_ready;		//雷モドキを出すかどうか

	float ball_angle;		//ボールの角度
	int speed;				//ボールのスピード
	float moveX;				//ボールのX移動量
	float moveY;				//ボールのY移動量
	//float BallX;				//ボールのX座標
	//float BallY;				//ボールのY座標
	int ball_flg;			//ボールの状態(0...移動中 1...バー接触 2...スタート状態)

	int thunder_angle;		//雷の角度

public:
	void ChangeAngle();		//角度変更処理
	void MoveBall();		//ボールの移動
	void StartBall();		//スタートボール
	int R_BallFlg();		//ボールの戻り値


	//float GetBallX()
	//{
	//	//ボールのX座標を返す
	//	return BallX;
	//}

	//float GetBallY()
	//{
	//	//ボールのY座標を返す
	//	return BallY;
	//}

	float* GetBallAngle()
	{
		//ボールの角度を返す
		return &ball_angle;
	}

	void SetBallAngle(float Angle)
	{
		ball_angle = (1 - Angle);
	}

	//コンストラクタ
	Thunder();

	//デストラクタ
	~Thunder();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

};

