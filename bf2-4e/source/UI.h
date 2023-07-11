#pragma once

class UI
{
private:
	int score;	//スコア
	

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
