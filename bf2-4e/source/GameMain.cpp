#include "GameMain.h"
#include"common.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    //object = new Stage();
    player = new Player();
    enemy = new Enemy();
    collision = new BoxCollision();
    stageitem = new StageItem();

    stage = 0;
    flg = false;

    color = 0xffffff;
    switch (stage)
    {
    case 0://�X�e�[�W1
        for (int i = 0; i < 3; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 1://�X�e�[�W2
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 2://�X�e�[�W3
        for (int i = 0; i <7 ;i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 3://�X�e�[�W4
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i, stage);
        }
        break;
    case 4://�X�e�[�W5
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    }

    //�|�[�Y�ł͂Ȃ�
    pause_flag = FALSE;
};

GameMain::~GameMain() 
{
    delete stage_floor;
    // �I������
};

AbstractScene* GameMain::Update()
{
    //�|�[�Y�؂�ւ�����
    if (PadInput::OnButton(XINPUT_BUTTON_START))       // START�{�^���������ꂽ�Ƃ�
    {
        pause_flag = !pause_flag;
    }
    //�|�[�Y���ł͂Ȃ���

    if (pause_flag == FALSE)
    {
        //�Q�[�����C������������
        stageitem->Update();

        player->Update();

        enemy->Update();

        //collision->HitBox(object);

        //�v���C���[�����ɓ���������......
        switch (stage)
        {
        case 0://�X�e�[�W1
            if (player->PlayerBackLash() == true)
            {
                player->PlayerBack();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 3; i++)
            {
                
                if (stage_floor[i]->HitBox(player) == true)
                {
                    player->PlayerGroundWalk();
                    DrawString(100, 100, "asdfyuytrssdfghj", 0x00ff00, TRUE);
                    color = 0x0ff000;
                }
            }
            break;
        case 1://�X�e�[�W2
            if (player->PlayerBackLash() == true)
            {
                player->PlayerBack();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 5; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    player->PlayerGroundWalk();
                    DrawString(100, 100, "asdfyuytrssdfghj", 0x00ff00, TRUE);
                    color = 0x0ff000;
                }
            }
            break;
        case 2://�X�e�[�W3
            if (player->PlayerBackLash() == true)
            {
                player->PlayerBack();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 7; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    player->PlayerGroundWalk();
                    DrawString(100, 100, "asdfyuytrssdfghj", 0x00ff00, TRUE);
                    color = 0x0ff000;
                }
            }
            break;
        case 3://�X�e�[�W4
            if (player->PlayerBackLash() == true)
            {
                player->PlayerBack();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 7; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    player->PlayerGroundWalk();
                    DrawString(100, 100, "asdfyuytrssdfghj", 0x00ff00, TRUE);
                    color = 0x0ff000;
                }
            }
            break;
        case 4://�X�e�[�W5
            if (player->PlayerBackLash() == true)
            {
                player->PlayerBack();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 8; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    player->PlayerGroundWalk();
                    DrawString(100, 100, "asdfyuytrssdfghj", 0x00ff00, TRUE);
                    color = 0x0ff000;
                }
            }
            break;
        }

    }
    // �����Œl�̍X�V�ȂǁA����)

    //object->Update();
    
    //player->Move();

    //collision->HitBox(object);



    if(PadInput::OnButton(XINPUT_BUTTON_Y)) {
        if (stage == 4)
        {
            stage = -1;
        }
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
        DrawFormatString(20, 50, color, "Game Main");
        player->Draw();        //�v���C���[�摜�̕`�揈��

        enemy->Draw();         //�G�摜�̕`�揈��

    }

    player->Draw();        //�v���C���[�摜�̕`�揈��

    enemy->Draw();         //�G�摜�̕`�揈��

    stageitem->Draw();     //�X�e�[�W�A�C�e���̕`�揈��

    //�|�[�Y�Ńv���C���[�ƓG�������ׂ�ALPHA�ANOBLEND�̒��ɏ���
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0); 

    //��UI�A�X�e�[�W������

    //�X�e�[�W�摜�̕`�揈��
    switch (stage)
    {
    case 0:
        for (int i = 0; i < 3; i++)
        {
            stage_floor[i]->Draw();
        }
        break;
    case 1:
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i]->Draw();
        }
        break;
    case 2:
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i]->Draw();
        }
    case 3:
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i]->Draw();
        }
        break;
    case 4:
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i]->Draw();
        }
        break;
    }      
};
//�X�e�[�W�̐ؑ�
void GameMain::ChangeScene()
{
    stage++;

    switch (stage)
    {
    case 0:
        for (int i = 0; i < 3; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 1:
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 2:
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 3:
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i, stage);
        }
    case 4:
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    }
}

