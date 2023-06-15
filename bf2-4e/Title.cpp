#include "Title.h"
#include "DxLib.h"
#include "PadInput.h"
#include "GameMain.h"

Title::Title() {
    // 初期化処理
    state = 0;
};

Title::~Title() {
    // 終了処理
};

AbstractScene* Title::Update() { // ここで値の更新など、処理
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
        return new GameMain();
    }
    return this; // シーン継続
};

void Title::Draw() const { // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawString(20, 50, "bf", 0xffffff);

    DrawFormatString(20, 95, 0xffffff, "ゲームスタート：Spaceキー");
    DrawFormatString(20, 110, 0xffffff, "ゲーム終了：Escキー");
};