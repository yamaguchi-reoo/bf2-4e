#include "Title.h"
#include "DxLib.h"
#include "PadInput.h"
#include "GameMain.h"

Title::Title() {
    // 初期化処理
    state = 0;
    FlashTime = 0;
    FlashFlg = FALSE;

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
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
        return new GameMain();
    }

    
    return this; // シーン継続
};

void Title::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(100);

    DrawString(155, 40, "BLLOOM", 0xffffff);
    DrawString(185, 140, "FIGHT", 0xffffff);

    SetFontSize(32);
    if (FlashFlg == TRUE) {
        DrawString(150, 290, "A   1-PLAYER  GAME", 0xffffff);
    }
    else
    {
        DrawString(150, 290, "A   1-PLAYER  GAME", 0x000000);
    }
    
};