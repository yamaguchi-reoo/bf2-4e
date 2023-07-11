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
    delete stage;
    // �I������
};

AbstractScene* GameMain::Update() 
{ // �����Œl�̍X�V�ȂǁA����)

    stage->Update();

    return this; // �V�[���p��
};

void GameMain::Draw() const 
{ // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Game Main");

    stage->Draw();        //�X�e�[�W�摜�̕`�揈��

    player.Draw();        //�v���C���[�摜�̕`�揈��

    enemy.Draw();         //�v���C���[�摜�̕`�揈��
};