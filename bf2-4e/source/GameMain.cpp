#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    stage = new Stage();

    //�|�[�Y�ł͂Ȃ�
    pause_flag = FALSE;
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
        pause_flag = !pause_flag;
    }
    //�|�[�Y���ł͂Ȃ���
    if(pause_flag==FALSE)
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
    if (pause_flag == TRUE)
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, " PAUSE ");
        //SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);     //�G
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