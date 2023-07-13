#pragma once

class UI
{
private:
	// スコア画像変数
	int scoreimage[4];
	
	//スコア文字の変数
	int score;

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
