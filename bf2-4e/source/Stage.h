#pragma once

class Stage 
{
private:
	int stage_number;//ステージ数用変数

	int stage_image01;
	int stage_image02;
	int stage_image03;
	int stage_image04;
public:
	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;
};
