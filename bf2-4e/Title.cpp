#include "Title.h"
#include "DxLib.h"
#include "PadInput.h"
#include "GameMain.h"

Title::Title() {
    // ����������
    state = 0;
    FlashTime = 0;
    FlashFlg = FALSE;

};

Title::~Title() {
    // �I������
};

AbstractScene* Title::Update() { // �����Œl�̍X�V�ȂǁA����

    if (++FlashTime >= 70)
    {
        FlashFlg = !FlashFlg;
        FlashTime = 0;
    }
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
        return new GameMain();
    }

    
    return this; // �V�[���p��
};

void Title::Draw() const { // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
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