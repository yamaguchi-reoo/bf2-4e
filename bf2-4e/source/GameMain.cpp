#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    object = new Stage();
    player = new Player();
    enemy = new Enemy();
    collision = new BoxCollision();
};

GameMain::~GameMain() 
{
    delete object;
    // �I������
};

AbstractScene* GameMain::Update() 
{ // �����Œl�̍X�V�ȂǁA����)

    object->Update();

    player->Update();
    
    enemy->Update();

    collision->HitBox(object);

    return this; // �V�[���p��
};

void GameMain::Draw() const 
{ // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Game Main");

    object->Draw();        //�X�e�[�W�摜�̕`�揈��

    player->Draw();        //�v���C���[�摜�̕`�揈��

    enemy->Draw();         //�v���C���[�摜�̕`�揈��
};