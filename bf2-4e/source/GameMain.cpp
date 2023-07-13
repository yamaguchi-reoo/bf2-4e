#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // 初期化処理
    stage = new Stage();

    //ポーズではない
    pauseflag = FALSE;
};

GameMain::~GameMain() 
{
    // 終了処理
};

AbstractScene* GameMain::Update() 
{ 
    //ポーズ切り替え処理
    if (PadInput::OnButton (XINPUT_BUTTON_START))       // STARTが押されたとき
    { 
        pauseflag = !pauseflag;
    }
    //ポーズ中ではない時
    if(pauseflag==FALSE)
    {
        //ゲームメイン処理を入れる
    }

    stage->Update();

    return this; // シーン継続
};

void GameMain::Draw() const 
{ 
    // やることは描画のみ、絶対に値の更新はしない

    //ポーズ画面の描画
    if (pauseflag == TRUE)
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, " PAUSE ");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);     //敵
    }
    else 
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, "Game Main");
    }
    

    stage->Draw();

    player.Draw();         //プレイヤー画像の描画処理

    enemy.Draw();         //プレイヤー画像の描画処理
};