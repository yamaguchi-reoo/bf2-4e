#include "DxLib.h"
#include "UI.h"
#include "Title.h"

UI::UI()
{
	
}

UI::~UI()
{
}

void UI::Update()
{
}

void UI::Draw() const
{
	//スコアの描画（仮）
	DrawFormatString(0, 100, 0xffffff, "Hallo");

	//ポーズ画面の描画
	SetFontSize(100);
	DrawString(200, 320, "--- ポーズ中 ---", 0x000000);
}