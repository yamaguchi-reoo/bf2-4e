#include "Title.h"
#include "common.h"
#include "DxLib.h"
#include "PadInput.h"
#include "GameMain.h"

Title::Title()
{
    // ����������
    try
    {
        //�摜�Ǎ�
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
        printf("�G���[�R�[�h%d\n", err);
    }
};

Title::~Title() 
{
    // �I������
};

AbstractScene* Title::Update() { // �����Œl�̍X�V�ȂǁA����
    //A�{�^���ŃQ�[�����C����
    if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)|| CheckHitKey(KEY_INPUT_Z))
    {
        return new GameMain();
    }

    return this; // �V�[���p��
};

void Title::Draw() const 
{ // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
    //�摜�`��
    DrawGraph(45, 20, LogoImage, TRUE);      //���S
    DrawGraph(155, 270, SelectImage, TRUE); //�Z���N�g
    DrawGraph(175, 430, CreditImage, TRUE); //�N���W�b�g

};