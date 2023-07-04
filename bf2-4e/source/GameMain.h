#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include "Player.h"

class GameMain : public AbstractScene {
private:
    Stage* stage;
    Player player;      //�v���C���[�N���X�̃I�u�W�F�N�g��

public:
    // �R���X�g���N�^
    GameMain();

    // �f�X�g���N�^
    ~GameMain();

    // �`��ȊO�̍X�V������
    virtual AbstractScene* Update() override;

    // �`��Ɋւ��邱�Ƃ�����
    virtual void Draw() const override;
};
