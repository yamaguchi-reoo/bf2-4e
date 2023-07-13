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

    if (KeyFlg & PAD_INPUT_8) { // STARTが押されたとき
        if (pauseFlag == 0) { // まだ一度もPause状態になってないなら
            pauseFlag = 1; // Pause状態になるというフラグ
        }
        else {
            pauseFlag = 0;
        }
    }
    if (pauseFlag == 1) {
        Pause();
    }

    stage->Update();

    return this; // シーン継続
};

void GameMain::Draw() const 
{ // やることは描画のみ、絶対に値の更新はしない


    SetFontSize(16);
    DrawFormatString(20, 50, 0xffffff, "Game Main");

    stage->Draw();

    player.Draw();         //プレイヤー画像の描画処理

    enemy.Draw();         //プレイヤー画像の描画処理
};