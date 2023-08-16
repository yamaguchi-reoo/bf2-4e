#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include"StageFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "BoxCollision.h"
#include"StageItem.h"
#include"Thunder.h"
#include"Fish.h"

#include "Bubble.h"

class GameMain : public AbstractScene {
private:
   // Stage* object;
    Player* player;         //�v���C���[�N���X�̃I�u�W�F�N�g��
    Enemy* enemy[6];           // Enemy�N���X�̃I�u�W�F�N�g��
    StageFloor* stage_floor[10];

    StageItem* stageitem;
    Thunder* thunder;       //���N���X�̃I�u�W�F�N�g��
    Fish* fish;

    Bubble* bubble[6];         //�V���{���ʂ̃I�u�W�F�N�g��

    bool pause_flag;     //�|�[�Y�̃t���O���

    int color;
    int stage;
    bool flg;
    int time;
    int fps;
    int enemy_death;        // �|�����G�̐�
    int wait_time;          // �X�e�[�W�J�ڂ���܂ł̑ҋ@����

public:
    // �R���X�g���N�^
    GameMain();

    // �f�X�g���N�^
    ~GameMain();

    // �`��ȊO�̍X�V������
    virtual AbstractScene* Update() override;

    // �`��Ɋւ��邱�Ƃ�����
    virtual void Draw() const override;

    //�X�e�[�W�̐؂�ւ�
    void ChangeScene();
};
