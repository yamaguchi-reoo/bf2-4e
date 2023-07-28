#pragma once
#include "Fps.h"

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
	int thunder_cloud_time;			
	int thunder_cloud_anime_num;	

	//稲光
	int thunder_time_anime;		//
	int thunder_anime_num;		//

	int thunder_frame = 60;		//制限時間
	int thunder_anime_frame;	//稲光のアニメーション用のフレーム

	bool is_thunder_shoot_ready;	//稲光を出すかどうか
	bool thunder_shoot_flg;			//稲光が出ているどうか

	//雷モドキ
	int thunder_effect_time;
	int thunder_effect_anime_num;

public:
	//コンストラクタ
	Thunder();

	//デストラクタ
	~Thunder();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

};

