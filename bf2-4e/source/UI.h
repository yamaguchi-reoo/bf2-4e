#pragma once

class UI
{
private:
	// スコア画像分割用の変数
	int numimage[4];
	
	//スコア文字用画像の変数
	int score;
	int hiscore;
	
	//ライフ用
	int stock;

	//ポーズ用変数
	bool pauseState;
	bool pauseFlag;
	bool pauseReset;

public:
	//コンストラクタ
	UI();

	//デストラクタ
	~UI();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;
};
