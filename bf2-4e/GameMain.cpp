#include "GameMain.h"
#include"DxLib.h"

GameMain::GameMain() {
    // ����������
    state = 0;
};

GameMain::~GameMain() {
    // �I������
};

AbstractScene* GameMain::Update() { // �����Œl�̍X�V�ȂǁA����

    return this; // �V�[���p��
};

void GameMain::Draw() const { // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Game Main");
};