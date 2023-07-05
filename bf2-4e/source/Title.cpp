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
        logo_image = LoadGraph("source/Resource/images/Title/Title_Logo.png");
        if (logo_image == -1)
        {
            throw "source/Resource/images/Title/Title_Logo.png";
        }
        select_image = LoadGraph("source/Resource/images/Title/Title_ModeSelect.png");
        if (select_image == -1)
        {
            throw "source/Resource/images/Title/Title_ModeSelect.png";
        }
        credit_image = LoadGraph("source/Resource/images/Title/Title_Credit.png");
        if (credit_image == -1)
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

AbstractScene* Title::Update() 
{ // ここで値の更新など、処理
    //Aボタンでゲームメインへ
    if (PadInput::OnButton(XINPUT_BUTTON_A)|| CheckHitKey(KEY_INPUT_Z))
    {
        return new GameMain();
    }

    return this; // シーン継続
};

void Title::Draw() const 
{ // やることは描画のみ、絶対に値の更新はしない
    //画像描画
    DrawGraph(45, 20, logo_image, TRUE);      //ロゴ
    DrawGraph(155, 270, select_image, TRUE); //セレクト
    DrawGraph(175, 430, credit_image, TRUE); //クレジット

};