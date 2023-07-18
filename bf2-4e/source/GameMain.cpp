#include "GameMain.h"
#include"common.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    object = new Stage();
    player = new Player();
    enemy = new Enemy();
    collision = new BoxCollision();

    stage = 0;

    switch (stage)
    {
    case BLOCK_NUMBER::STAGE1:
        for (int i = 0; i < BLOCK_NUMBER::STAGE1; i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    case BLOCK_NUMBER::STAGE2:
        for (int i = 0; i < BLOCK_NUMBER::STAGE2; i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    case BLOCK_NUMBER::STAGE3_STAGE4:
        for (int i = 0; i < BLOCK_NUMBER::STAGE3_STAGE4 ;i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    case BLOCK_NUMBER::STAGE5:
        for (int i = 0; i < BLOCK_NUMBER::STAGE5; i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    }

    //�|�[�Y�ł͂Ȃ�
    pause_flag = FALSE;
};

GameMain::~GameMain() 
{
    delete object;
    delete stagefloor;
    // �I������
};

AbstractScene* GameMain::Update()
{
    //�|�[�Y�؂�ւ�����
    if (PadInput::OnButton(XINPUT_BUTTON_START))       // START�������ꂽ�Ƃ�
    {
        pause_flag = !pause_flag;
    }
    //�|�[�Y���ł͂Ȃ���
    if (pause_flag == FALSE)
    {
        //�Q�[�����C������������

        player->Update();

        enemy->Update();

        collision->HitBox(object);
    }
    // �����Œl�̍X�V�ȂǁA����)

    object->Update();

    player->Update();
    
    //player->Move();
    enemy->Update();

    collision->HitBox(object);


    if(PadInput::OnButton(XINPUT_BUTTON_START)) {
        ChangeScene();
    }
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
        SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);     //�X�e�[�W�ȊO�S�ď���
    }
    else 
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, "Game Main");
    }

    player->Draw();        //�v���C���[�摜�̕`�揈��

    enemy->Draw();         //�G�摜�̕`�揈��


    for (int i = 0; i < 4; i++)
    {
        switch (i)
        {
        case BLOCK_NUMBER::STAGE1:
            for (int i = 0; i < BLOCK_NUMBER::STAGE1; i++)
            {
                stagefloor[i]->Draw();
            }
            break;
        case BLOCK_NUMBER::STAGE2:
            for (int i = 0; i < BLOCK_NUMBER::STAGE2; i++)
            {
                stagefloor[i]->Draw();
            }
            break;
        case BLOCK_NUMBER::STAGE3_STAGE4:
            for (int i = 0; i < BLOCK_NUMBER::STAGE3_STAGE4; i++)
            {
                stagefloor[i]->Draw();
            }
            break;
        case BLOCK_NUMBER::STAGE5:
            for (int i = 0; i < BLOCK_NUMBER::STAGE5; i++)
            {
                stagefloor[i]->Draw();
            }
            break;
        }
    }
    //�|�[�Y�Ńv���C���[�ƓG�������ׂ�ALPHA�ANOBLEND�̒��ɏ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0); 

    //��UI�A�X�e�[�W������
    //object->Draw();        //�X�e�[�W�摜�̕`�揈��
};
void GameMain::ChangeScene()
{
    stage++;

    switch (stage)
    {
    case BLOCK_NUMBER::STAGE1:
        for (int i = 0; i < BLOCK_NUMBER::STAGE1; i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    case BLOCK_NUMBER::STAGE2:
        for (int i = 0; i < BLOCK_NUMBER::STAGE2; i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    case BLOCK_NUMBER::STAGE3_STAGE4:
        for (int i = 0; i < BLOCK_NUMBER::STAGE3_STAGE4; i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    case BLOCK_NUMBER::STAGE5:
        for (int i = 0; i < BLOCK_NUMBER::STAGE5; i++)
        {
            stagefloor[i] = new StageFloor(i,stage);
        }
        break;
    }
}