#include "GameMain.h"
#include"common.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    //object = new Stage();
    player = new Player();
    collision = new BoxCollision();
    stageitem = new StageItem();
    thunder = new Thunder();
    fish = new Fish();

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
        // �G�̐���
        for (int i = 0; i <= 2; i++)
        {
            // �s���N�F�̓G��3��
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        break;
    case 1://�X�e�[�W2
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // �G�̐���
        for (int i = 0; i <= 2; i++)
        {
            // �s���N�F�̓G��3��
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        // �΂̓G��2��
        enemy[3] = new Enemy(150.0f, 135.0f, 1);
        enemy[4] = new Enemy(510.0f, 115.0f, 1);
    case 2://�X�e�[�W3
        for (int i = 0; i <10 ;i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // �s���N�F�̓G��1��
        enemy[0] = new Enemy(320.0f, 335.0f, 0);
        // �ΐF�̓G��2��
        enemy[1] = new Enemy(190.0f, 232.0f, 1);
        enemy[2] = new Enemy(345.0f, 150.0f, 1);
        // �ԐF�̓G��2��
        enemy[3] = new Enemy(220.0f, 65.0f, 2);
        enemy[4] = new Enemy(530.0f, 65.0f, 2);
        break;
    case 3://�X�e�[�W4
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i, stage);
        }
        // �s���N�F�̓G��3��
        enemy[0] = new Enemy(145.0f, 235.0f, 0);
        enemy[1] = new Enemy(265.0f, 266.0f, 0);
        enemy[2] = new Enemy(485.0f, 250.0f, 0);
        // �ΐF�̓G��1��
        enemy[3] = new Enemy(355.0f, 150.0f, 1);
        // �ԐF�̓G��1��
        enemy[4] = new Enemy(390.0f, 335.0f, 2);
        break;
    case 4://�X�e�[�W5
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // �s���N�F�̓G��2��
        enemy[0] = new Enemy(230.0f, 300.0f, 0);
        enemy[1] = new Enemy(380.0f, 300.0f, 0);
        // �ΐF�̓G��3��
        enemy[2] = new Enemy(110.0f, 165.0f, 1);
        enemy[3] = new Enemy(270.0f, 132.0f, 1);
        enemy[4] = new Enemy(510.0f, 117.0f, 1);
        // �ԐF�̓G��1��
        enemy[5] = new Enemy(240.0f, 50.0f, 2);
        break;
    }

    //�|�[�Y�ł͂Ȃ�
    pause_flag = FALSE;
};

GameMain::~GameMain() 
{
    for (int i = 0; i < 10; i++)
    {
        delete stage_floor[i];
    }
    // �I������
};

AbstractScene* GameMain::Update()
{
    time++;
    if (time >= 60)
    {
        // �b���̃J�E���g�𑝂₷
        fps++;
        // fps�̃J�E���g��0�ɖ߂�
        time= 0;
    }
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

        fish->Update();

        thunder->Update();

        //collision->HitBox(object);

        // �X�e�[�W���Ƃ̓G�̍X�V����
        switch (stage)
        {
        case 0:
            // �X�e�[�W1
            for (int i = 0; i <= 2; i++)
            {
                enemy[i]->Update();
            }
            break;
        case 1:
            // �X�e�[�W2
            for (int i = 0; i <= 4; i++)
            {
                enemy[i]->Update();
            }
            break;
        case 2:
             // �X�e�[�W3
            for (int i = 0; i <= 4; i++)
            {
                enemy[i]->Update();
            }
            break;
        case 3:
            // �X�e�[�W4
            for (int i = 0; i <= 4; i++)
            {
                enemy[i]->Update();
            }
            break;
        case 4:
            // �X�e�[�W5
            for (int i = 0; i <= 5; i++)
            {
                enemy[i]->Update();
            }
            break;
        }

        //�v���C���[�����ɓ���������......
        switch (stage)
        {
        case 0://�X�e�[�W1
            if (player->PlayerFlg() == true)
            {
                player->PlayerReversalFlg();
                color = 0x0ffff0;
            }
            else {
                color = 0xffffff;
                if (fish->HitBox(player) == true ) {
                    fish->PlayerEat();
                    color = 0x000000;
                }
                else {
                    fish->FishReset();
                }
            }
            for (int i = 0; i < 3; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    color = 0xf00fff;
                    if (stage_floor[i]->HitTopBox(player) == true /* && stage_floor[i]->HitBox(player) == true */) {
                        player->PlayerGroundWalk();
                        color = 0x0ff000;
                    }
                    player->Bounce();

                }
            }
            break;
        case 1://�X�e�[�W2
            if (player->PlayerFlg() == true)
            {
                player->PlayerReversalFlg();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 5; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    color = 0xf00fff;
                    if (stage_floor[i]->HitTopBox(player) == true /* && stage_floor[i]->HitBox(player) == true */) {
                        //if (player->adsfg() < 0) {
                        player->PlayerGroundWalk();
                        color = 0x0ff000;
                        //}
                    }
                    player->Bounce();
                }
            }
            break;
        case 2://�X�e�[�W3
            if (player->PlayerFlg() == true)
            {
                player->PlayerReversalFlg();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 10; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    color = 0xf00fff;
                    if (stage_floor[i]->HitTopBox(player) == true /* && stage_floor[i]->HitBox(player) == true */) {
                        //if (player->adsfg() < 0) {
                        player->PlayerGroundWalk();
                        color = 0x0ff000;
                        //}
                    }
                    player->Bounce();
                }
            }
            break;
        case 3://�X�e�[�W4
            if (player->PlayerFlg() == true)
            {
                player->PlayerReversalFlg();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 7; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    color = 0xf00fff;
                    if (stage_floor[i]->HitTopBox(player) == true /* && stage_floor[i]->HitBox(player) == true */) {
                        //if (player->adsfg() < 0) {
                        player->PlayerGroundWalk();
                        color = 0x0ff000;
                        //}
                    }
                    player->Bounce();
                }
            }
            break;
        case 4://�X�e�[�W5
            if (player->PlayerFlg() == true)
            {
                player->PlayerReversalFlg();
                color = 0x0ffff0;
            }
            for (int i = 0; i < 8; i++)
            {
                if (stage_floor[i]->HitBox(player) == true)
                {
                    color = 0xf00fff;
                    if (stage_floor[i]->HitTopBox(player) == true /* && stage_floor[i]->HitBox(player) == true */) {
                        //if (player->adsfg() < 0) {
                        player->PlayerGroundWalk();
                        color = 0x0ff000;
                        //}
                    }
                    player->Bounce();
                }
            }
            break;
        }

    }
    // �����Œl�̍X�V�ȂǁA����)

    //object->Update();
    
    //player->Move();

    //collision->HitBox(object);


    // �X�e�[�W�̊Ǘ�
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

    DrawFormatString(30, 100, 0xffffff, "%d", fps);
   //�|�[�Y��ʂ̕`��
    if (pause_flag == TRUE)
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, " PAUSE ");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);  //�X�e�[�W�ȊO�S�ď���
    }
    else 
    {
        SetFontSize(16);
        DrawFormatString(20, 50, color, "Game Main");
        player->Draw();     //�v���C���[�摜�̕`�揈��
        fish->Draw();

        // �X�e�[�W���Ƃ̓G�̕`�揈��
        switch (stage)
        {
        case 0:
            // �X�e�[�W1
            for (int i = 0; i <= 2; i++)
            {
                enemy[i]->Draw();
            }
            break;
        case 1:
            // �X�e�[�W2
            for (int i = 0; i <= 4; i++)
            {
                enemy[i]->Draw();
            }
            break;
        case 2:
            // �X�e�[�W3
            for (int i = 0; i <= 4; i++)
            {
                enemy[i]->Draw();
            }
            break;
        case 3:
            // �X�e�[�W4
            for (int i = 0; i <= 4; i++)
            {
                enemy[i]->Draw();
            }
            break;
        case 4:
            // �X�e�[�W5
            for (int i = 0; i <= 5; i++)
            {
                enemy[i]->Draw();
            }
            break;
        }

    }

    player->Draw();        //�v���C���[�摜�̕`�揈��

    //enemy->Draw();         //�G�摜�̕`�揈��

    thunder->Draw();        //���摜�̕`�揈��

    //stageitem->Draw();     //�X�e�[�W�A�C�e���̕`�揈��

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
        for (int i = 0; i < 10; i++)
        {
            stage_floor[i]->Draw();
        }
        break;
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
        // �X�e�[�W1
        for (int i = 0; i < 3; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // �G�̐���
        for (int i = 0; i <= 2; i++)
        {
            // �s���N�F�̓G��3��
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        break;
    case 1:
        // �X�e�[�W2
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // �G�̐���
        for (int i = 0; i <= 2; i++)
        {
            // �s���N�F�̓G��3��
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        // �΂̓G��2��
        enemy[3] = new Enemy(150.0f, 135.0f, 1);
        enemy[4] = new Enemy(510.0f, 115.0f, 1);
        break;
    case 2:
        for (int i = 0; i < 10; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // �s���N�F�̓G��1��
        enemy[0] = new Enemy(320.0f, 335.0f, 0);
        // �ΐF�̓G��2��
        enemy[1] = new Enemy(190.0f, 232.0f, 1);
        enemy[2] = new Enemy(345.0f, 150.0f, 1);
        // �ԐF�̓G��2��
        enemy[3] = new Enemy(220.0f, 65.0f, 2);
        enemy[4] = new Enemy(530.0f, 65.0f, 2);
        break;
    case 3:
        // �X�e�[�W4
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i, stage);
        }
        // �s���N�F�̓G��3��
        enemy[0] = new Enemy(145.0f, 235.0f, 0);
        enemy[1] = new Enemy(265.0f, 266.0f, 0);
        enemy[2] = new Enemy(485.0f, 250.0f, 0);
        // �ΐF�̓G��1��
        enemy[3] = new Enemy(355.0f, 150.0f, 1);
        // �ԐF�̓G��1��
        enemy[4] = new Enemy(390.0f, 335.0f, 2);
        break;
    case 4:
        // �X�e�[�W5
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // �s���N�F�̓G��2��
        enemy[0] = new Enemy(230.0f, 300.0f, 0);
        enemy[1] = new Enemy(380.0f, 300.0f, 0);
        // �ΐF�̓G��3��
        enemy[2] = new Enemy(110.0f, 165.0f, 1);
        enemy[3] = new Enemy(270.0f, 132.0f, 1);
        enemy[4] = new Enemy(510.0f, 117.0f, 1);
        // �ԐF�̓G��1��
        enemy[5] = new Enemy(240.0f, 50.0f, 2);
        break;
    }
}