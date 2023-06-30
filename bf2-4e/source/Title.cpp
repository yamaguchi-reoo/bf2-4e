#include "Title.h"

#include "DxLib.h"
#include "PadInput.h"
#include "GameMain.h"

Title::Title() {
    // 初期化処理
    state = 0;
    FlashTime = 0;
    FlashFlg = FALSE;

    try
    {
        image = LoadGraph("source/Resource/images/Title/Title_Logo.png");
        if (image == -1) 
        {
            throw "source/Resource/images/Title/Title_Logo.png";
        }
    }
    catch(int& err)
    {
        printf("エラーコード%d\n", err);
    }

};

Title::~Title() {
    // 終了処理
};

AbstractScene* Title::Update() { // ここで値の更新など、処理

    if (++FlashTime >= 70)
    {
        FlashFlg = !FlashFlg;
        FlashTime = 0;
    }
    //Aボタンでゲームメインへ
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
        return new GameMain();
    }

    
    return this; // シーン継続
};

void Title::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(100);

    //DrawString(155, 40, "BLLOOM", 0xffffff);
    //DrawString(185, 140, "FIGHT", 0xffffff);

    DrawGraph(0, 0, image, TRUE);

    SetFontSize(32);
    if (FlashFlg == TRUE) {
        DrawString(150, 400, "A   1-PLAYER  GAME", 0xffffff);
    }
    else
    {
        DrawString(150, 400, "A   1-PLAYER  GAME", 0xff0000);
    }
};