#include "Title.h"

#include "DxLib.h"
#include "PadInput.h"
#include "GameMain.h"

Title::Title() {
    // ����������
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
        printf("�G���[�R�[�h%d\n", err);
    }

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
    //A�{�^���ŃQ�[�����C����
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
        return new GameMain();
    }

    
    return this; // �V�[���p��
};

void Title::Draw() const { // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
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