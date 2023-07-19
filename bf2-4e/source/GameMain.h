#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "BoxCollision.h"
#include"StageItem.h"

class GameMain : public AbstractScene {
private:
    Stage* object;
    Player* player;         //�v���C���[�N���X�̃I�u�W�F�N�g��
    Enemy* enemy;           // Enemy�N���X�̃I�u�W�F�N�g��
    BoxCollision* collision; //Collision�N���X�̃I�u�W�F�N�g�� 
    StageItem* stageitem;

    bool pause_flag;     //�|�[�Y�̃t���O���

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
