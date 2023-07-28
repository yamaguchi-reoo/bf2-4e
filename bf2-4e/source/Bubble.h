#pragma once
#include "BoxCollision.h"

class Bubble :public BoxCollision
{
private:
	int BubbleImage[4];

	int animation_count;					// アニメーション用カウント

	int now_image;							// 今から表示される画像
	int next_image;							// 次に表示される画像
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

};