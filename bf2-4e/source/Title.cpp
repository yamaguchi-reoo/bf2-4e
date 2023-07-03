#include "Title.h"
#include "common.h"
#include "DxLib.h"
#include "PadInput.h"
#include "GameMain.h"

Title::Title()
{
    // 初期化処理
    try
    {
        //画像読込
        LogoImage = LoadGraph("source/Resource/images/Title/Title_Logo.png");
        if (LogoImage == -1)
        {
            throw "source/Resource/images/Title/Title_Logo.png";
        }
        SelectImage = LoadGraph("source/Resource/images/Title/Title_ModeSelect.png");
        if (LogoImage == -1)
        {
            throw "source/Resource/images/Title/Title_ModeSelect.png";
        }
        CreditImage = LoadGraph("source/Resource/images/Title/Title_Credit.png");
        if (LogoImage == -1)
        {
            throw "source/Resource/images/Title/Title_Credit.png";
        }
    }
    catch(int& err)
    {
        printf("エラーコード%d\n", err);
    }
};

Title::~Title() 
{
    // 終了処理
};

AbstractScene* Title::Update() { // ここで値の更新など、処理
    //Aボタンでゲームメインへ
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)|| CheckHitKey(KEY_INPUT_Z))
    {
        return new GameMain();
    }

    return this; // シーン継続
};

void Title::Draw() const 
{ // やることは描画のみ、絶対に値の更新はしない
    //画像描画
    DrawGraph(45, 20, LogoImage, TRUE);      //ロゴ
    DrawGraph(155, 270, SelectImage, TRUE); //セレクト
    DrawGraph(175, 430, CreditImage, TRUE); //クレジット

};