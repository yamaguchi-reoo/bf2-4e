#pragma once
#include "BoxCollision.h"

class Bubble :public BoxCollision
{
private:
	int BubbleImage[4];

	int animation_count;					// アニメーション用カウント

	int now_image;							// 今から表示される画像
	int next_image;							// 次に表示される画像

	float PosX;		// 描画座標X
	float PosY;		// 描画座標Y
	float Radius;		// 半径(描画用)
	float CenterX;	// 中心座標X
	float CenterY;	// 中心座標Y
	float Angle;		// 角度
	float Length;		// 半径の長さ

public:
	//コンストラクタ
	Bubble();

	//デストラクタ
	~Bubble();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

	//シャボン玉のアニメーション関数
	void BubbleAnimation(void);

	//シャボン玉の移動
	void MoveBubble(void);

};