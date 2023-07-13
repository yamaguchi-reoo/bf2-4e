#include "DxLib.h"
#include "UI.h"
#include "Title.h"

// コンストラクタ
UI::UI()
{
	for (int i = 0; i < 19; i++)
	{
		scoreimage[i];
	
	}

	LoadGraph("Source/Resource/images/UI/UI_Score.png");
}

// デストラクタ
UI::~UI()
{
}

// 描画以外の更新を実装
void UI::Update()
{
}

// 描画に関することを実装
void UI::Draw() const
{
	DrawGraph(0,0,)

	//スコアの描画（仮）
	DrawFormatString(0, 100, 0xffffff, "Hallo");

	//ポーズ画面の描画
	SetFontSize(100);
	DrawString(200, 320, "--- ポーズ中 ---", 0x000000);
}