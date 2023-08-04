#pragma once
#include "Fps.h"
#include "math.h"
#define _USE_MATH_DEFINES


class Thunder
{
private:
	/* 画像用変数 */
	//雷
	int thunder_cloud_image[3];
	int thunder_image[6];
	int thunder_effect_image[3];

	/*アニメーションの待機用変数*/
	//雷雲
	int cloud_anime_num;

	int thunder_cloud_frame = 60;	//制限時間
	int thunder_cloud_anime_frame;	//雷雲のアニメーション用のフレーム

	//雷雲のアニメーション
	int thunder_cloud_time;			//
	int thunder_cloud_anime_num;	//雷雲の画像のループ

	//稲光
	int thunder_time_anime;			//
	int thunder_anime_num;			//雷雲の画像のループ
	
	int thunder_frame = 60;			//制限時間
	int thunder_anime_frame;		//稲光のアニメーション用のフレーム

	bool is_thunder_shoot_ready;	//稲光を出すかどうか
	bool thunder_shoot_flg;			//稲光が出ているどうか

	//雷モドキ
	int thunder_effect_time_anime;			//

	int thunder_effect_time = 60;				//制限時間
	int thunder_effect_anime_num;			//

	bool thunder_effect_shoot_flg;			//雷モドキが出ているどうか
	bool is_thunder_effect_shoot_ready;		//雷モドキを出すかどうか

	float BallAngle;		//ボールの角度
	int Speed;				//ボールのスピード
	int MoveX;				//ボールのX移動量
	int MoveY;				//ボールのY移動量
	int BallX;				//ボールのX座標
	int BallY;				//ボールのY座標
	int BallFlg;			//ボールの状態(0...移動中 1...バー接触 2...スタート状態)


public:
	void ChangeAngle();		//角度変更処理
	void MoveBall();		//ボールの移動

	//コンストラクタ
	Thunder();

	//デストラクタ
	~Thunder();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

};

