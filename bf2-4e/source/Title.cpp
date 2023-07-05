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
        printf("�G���[�R�[�h%d\n", err);
    }
};

Title::~Title() 
{
    // �I������
};

AbstractScene* Title::Update() 
{ // �����Œl�̍X�V�ȂǁA����
    //A�{�^���ŃQ�[�����C����
    if (PadInput::OnButton(XINPUT_BUTTON_A)|| CheckHitKey(KEY_INPUT_Z))
    {
        return new GameMain();
    }

    return this; // �V�[���p��
};

void Title::Draw() const 
{ // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
    //�摜�`��
    DrawGraph(45, 20, logo_image, TRUE);      //���S
    DrawGraph(155, 270, select_image, TRUE); //�Z���N�g
    DrawGraph(175, 430, credit_image, TRUE); //�N���W�b�g

};