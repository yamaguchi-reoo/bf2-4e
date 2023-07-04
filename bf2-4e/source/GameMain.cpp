#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // 初期化処理
    stage = new Stage();
};

GameMain::~GameMain() 
{
    // 終了処理
};

AbstractScene* GameMain::Update() 
{ // ここで値の更新など、処理

    stage->Update();

    return this; // シーン継続
};

void GameMain::Draw() const 
{ // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Game Main");

    stage->Draw();
};