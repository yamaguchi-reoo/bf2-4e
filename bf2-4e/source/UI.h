#pragma once

class UI
{
private:
	// スコア画像分割用の変数
	int num_image[10];
	
	//スコア文字用画像の変数
	int score_image;
	int hi_score_image;
	
	//ライフ用
	int stock_image;
	int stock;

	//ステージ数
	int phase;
	int phase_digit[2];		//桁ごとの画像切替
	int phase_image;

	//現在スコア
	int score;
	int score_digit[6];		//桁ごとの画像切替

	//ハイスコア
	int top_score;
	int topscore_digit[6];		//桁ごとの画像切替

	//ポーズ用変数
	/*bool pauseState;
	bool pauseFlag;
	bool pauseReset;*/

public:
	//コンストラクタ
	UI();

	//デストラクタ
	~UI();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

	//スコア表示用画像変更処理
	void ChangeImage(int _score ,int _digit[]);

	//ステージ数表示用画像変更処理
	void ChangeStageDigitImage(void);

	//スコア加算
	void AddScore(int addscore);

	//ライフ減少
	void SubScore(void);

	//ゲームオーバー判定
	bool CheckOver(void);

	//現在のステージ数取得
	void SetStageNum(void);
};
