/********************************
* �^�C�g��
* ��ҁF����
********************************/
#include "main.h"

Title::Title() {
    // ����������
    state = 0;
};

Title::~Title() {
    // �I������
};

AbstractScene* Title::Update() { // �����Œl�̍X�V�ȂǁA����

    return this; // �V�[���p��
};

void Title::Draw() const { // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, GAME_NAME);

    DrawFormatString(20, 95, 0xffffff, "�Q�[���X�^�[�g�FSpace�L�[");
    DrawFormatString(20, 110, 0xffffff, "�Q�[���I���FEsc�L�[");
};