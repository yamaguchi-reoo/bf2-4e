#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    stage = new Stage();

    //�|�[�Y�ł͂Ȃ�
    pauseflag = FALSE;
};

GameMain::~GameMain() 
{
    // �I������
};

AbstractScene* GameMain::Update() 
{ 
    //�|�[�Y�؂�ւ�����
    if (PadInput::OnButton (XINPUT_BUTTON_START))       // START�������ꂽ�Ƃ�
    { 
        pauseflag = !pauseflag;
    }
    //�|�[�Y���ł͂Ȃ���
    if(pauseflag==FALSE)
    {
        //�Q�[�����C������������
    }

    stage->Update();

    return this; // �V�[���p��
};

void GameMain::Draw() const 
{ 
    // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�

    //�|�[�Y��ʂ̕`��
    if (pauseflag == TRUE)
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, " PAUSE ");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);     //�G
    }
    else 
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, "Game Main");
    }
    

    stage->Draw();

    player.Draw();         //�v���C���[�摜�̕`�揈��

    enemy.Draw();         //�v���C���[�摜�̕`�揈��
};