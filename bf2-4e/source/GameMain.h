#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include"StageFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "BoxCollision.h"
#include"StageItem.h"

class GameMain : public AbstractScene {
private:
   // Stage* object;
    Player* player;         //�v���C���[�N���X�̃I�u�W�F�N�g��
    Enemy* enemy[6];           // Enemy�N���X�̃I�u�W�F�N�g��
    BoxCollision* collision; //Collision�N���X�̃I�u�W�F�N�g�� 
    StageFloor* stage_floor[8];

    StageItem* stageitem;

    bool pause_flag;     //�|�[�Y�̃t���O���

    int color;
    int stage;
    bool flg;

    //int enemy_max[6] = {2,4,4,4,4,5};           // �X�e�[�W���Ƃ̓G�̐�

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
