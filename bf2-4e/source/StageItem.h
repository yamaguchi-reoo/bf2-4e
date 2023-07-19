#pragma once

class StageItem
{
private:
	//画像用変数
	int thunder_image[2];
	int fish_image;

	//アニメーションの待機変数
	int time;
	int anime_num;

public:
	//コンストラクタ
	StageItem();

	//デストラクタ
	~StageItem();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

};

