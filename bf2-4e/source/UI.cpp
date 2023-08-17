#include "DxLib.h"
#include <math.h>

#include "UI.h"
#include "Title.h"
#include "PadInput.h"

// コンストラクタ
UI::UI()
{
	for (int i = 0; i < 10; i++)
	{
		num_image[i];
	}

	score_image = LoadGraph("Source/Resource/images/UI/UI_Score.png");
	hi_score_image = LoadGraph("Source/Resource/images/UI/UI_HiScore.png");

	stock_image = LoadGraph("Source/Resource/images/UI/UI_Stock.png");

	phase_image = LoadGraph("Source/Resource/images/UI/UI_Phase.png");

	LoadDivGraph("Source/Resource/images/UI/UI_NumAnimation.png", 10, 10, 1, 32, 32, num_image);

	phase = 1;

	for (int i = 0; i < 2; i++)
	{
		phase_digit[i] = 0;
	}

	stock = 2;

	score = 0;

	for (int i = 0; i < 6; i++)
	{
		score_digit[i] = 0;
	}

	top_score = 0;

	for (int i = 0; i < 6; i++)
	{
		topscore_digit[i] = 0;
	}

	

	//ランキングデータ読み込み
	FILE *fp;
#pragma warning(disable:4996)

	//ファイルオープン
	if ((fp = fopen("Source/Resource/data/TopScore.txt", "r")) == NULL) return;

	//ランキングデータを読み込む
	if (fscanf(fp, "%d", &top_score) == 1)

	//ファイルクローズ
	fclose(fp);
}

// デストラクタ
UI::~UI()
{
	FILE* fp;
#pragma warning(disable:4996)

	//ファイルオープン
	if ((fp = fopen("Source/Resource/data/TopScore.txt", "r")) == NULL) return;

	// ランキングデータ分配列データを書き込む
	if(fprintf(fp, "% d", top_score) == 1)
	
	//ファイルクローズ
	fclose(fp);
}

// 描画以外の更新を実装
void UI::Update()
{
	ChangeStageDigitImage();
	ChangeImage(score,score_digit);
	ChangeImage(top_score, topscore_digit);

	if (score >= top_score) 
	{
		top_score = score;
	}
}

// 描画に関することを実装
void UI::Draw() const
{
	//スコア描画
	DrawGraph(60, 10, score_image, TRUE);

	for (int i = 0; i < 6; i++) 
	{
		DrawGraph(75 + 20 * i, 4, num_image[score_digit[i]], TRUE);
	}
	
	//ハイスコア表示
	DrawGraph(240, 10, hi_score_image, TRUE);

	for (int i = 0; i < 6; i++) 
	{
		DrawGraph(270 + 20 * i, 4, num_image[topscore_digit[i]], TRUE);
	}

	//ライフの表示
	for (int i = stock; i > 0; i--) 
	{
		DrawGraph(187 - 20 * i, 32, stock_image, TRUE);
	}

	//ステージ数表示
	DrawGraph(240, 28, phase_image, TRUE);

	for (int i = 0; i < 2; i++)
	{
		DrawGraph(355 + 20 * i, 20, num_image[phase_digit[i]], TRUE);
	}

	//スコアの描画（仮）
	//DrawFormatString(0, 100, 0xffffff, "Hallo");

	//ポーズ画面の描画
	/*SetFontSize(100);
	DrawString(200, 320, "--- PAUSE ---", 0x000000);*/
}

void UI::ChangeImage(int _score,int _digit[])
{
	int score_dummy = _score;

	for (int i = 6 - 1; i >= 0; i--) {
		_digit[i] = score_dummy % 10;
		score_dummy /= 10;
	}
}

void UI::ChangeStageDigitImage(void)
{	
	int phase_dummy = phase;

	for (int i = 2 - 1; i >= 0; i--) {
		phase_digit[i] = phase_dummy % 10;
		phase_dummy /= 10;
	}
}

void UI::AddScore(int addscore)
{
	score += addscore;
}

void UI::SubScore(void)
{
	stock--;
}

bool UI::CheckOver(void)
{
	bool ret = false;

	if (stock < 0) 
	{
		ret = true;
	}

	return ret;
}

void UI::SetStageNum(void)
{
	phase++;
}
