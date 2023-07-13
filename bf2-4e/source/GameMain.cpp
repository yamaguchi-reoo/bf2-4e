#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    stage = new Stage();
};

GameMain::~GameMain() 
{
    // �I������
};

AbstractScene* GameMain::Update() 
{ // �����Œl�̍X�V�ȂǁA����

    if (KeyFlg & PAD_INPUT_8) { // START�������ꂽ�Ƃ�
        if (pauseFlag == 0) { // �܂���x��Pause��ԂɂȂ��ĂȂ��Ȃ�
            pauseFlag = 1; // Pause��ԂɂȂ�Ƃ����t���O
        }
        else {
            pauseFlag = 0;
        }
    }
    if (pauseFlag == 1) {
        Pause();
    }

    stage->Update();

    return this; // �V�[���p��
};

void GameMain::Draw() const 
{ // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�


    SetFontSize(16);
    DrawFormatString(20, 50, 0xffffff, "Game Main");

    stage->Draw();

    player.Draw();         //�v���C���[�摜�̕`�揈��

    enemy.Draw();         //�v���C���[�摜�̕`�揈��
};