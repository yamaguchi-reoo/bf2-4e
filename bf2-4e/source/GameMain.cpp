#include "GameMain.h"
#include"common.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // ����������
    player = new Player();
    for (int i = 0; i <= 5; i++)
    {
        enemy[i] = nullptr;
    }
    for (int i = 0; i < 10; i++)
    {
        stage_floor[i] = nullptr;
    }
    stageitem = new StageItem();
    thunder = new Thunder();
    fish = new Fish();
    ui = new UI();

    for (int i = 0; i <= 5; i++) {
        bubble[i] = new Bubble(0, 0, false,false);
    }
    //bubble = new Bubble();

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

    enemy_death = 0;        // �|�����G�̐�
    wait_time = 0;          // �X�e�[�W�J�ڂ���܂ł̑ҋ@����
};

GameMain::~GameMain() 
{
    delete player;
    delete[] &enemy;
    delete[] &stage_floor;
    delete stageitem;
    delete thunder;
    delete fish;
    delete[] &bubble;
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

        fish->Update();

        thunder->Update();

        for (int i = 0; i <= 5; i++)
        {
            bubble[i]->Update();
            //�V���{���ʂƃv���C���[�̃q�b�g����
            if (bubble[i]->HitBox(player) == true)
            {
                if (bubble[i]->GetGetFlg() == false) 
                {
                    ui->AddScore(500);      //500�_���Z
                }
                bubble[i]->ChangeGetFlg();
            }
        }

        for (int i = 0; i <= 5; i++)
        {
            if (enemy[i] != nullptr)
            {
                // �G�̍X�V����
                enemy[i]->Update();

                // �G�ƃv���C���[�̓����蔻��
                if (enemy[i]->HitBealloon(player) == true)
                {
                    if (enemy[i]->enemy_state == EnemyState::kFlight)
                    {
                        enemy[i]->enemy_state = EnemyState::kParachute;
                    }
                }
                else if (enemy[i]->EnemyHitBox(player) == true && enemy[i]->enemy_state != EnemyState::kFlight)
                {
                    if (enemy[i]->enemy_state != EnemyState::kDeath && enemy[i]->enemy_state != EnemyState::kParachute)
                    {
                        enemy[i]->SetEnemyDeathFlg(1);
                        enemy[i]->enemy_state = EnemyState::kDeath;
                    }
                }

                // �G�ƃX�e�[�W�̓����蔻��
                for (int j = 0; j < 10; j++)
                {
                    if (stage_floor[j] != nullptr)
                    {
                        if (stage_floor[j]->EnemyHitBox(enemy[i]) == true && enemy[i]->enemy_state != EnemyState::kDeath)
                        {
                            if (stage_floor[j]->EnemyHitTopBox(enemy[i]) == true)
                            {
                                if (enemy[i]->enemy_state == EnemyState::kFlight)
                                {
                                    // ���ł���Ƃ��ɃX�e�[�W�ɒ��n�����Ƃ�
                                    // �����ɔ�ї���
                                   // enemy[i]->SetLevitationFlg(1);                                
                                }
                                else if (enemy[i]->enemy_state == EnemyState::kParachute)
                                {
                                    enemy[i]->enemy_state = EnemyState::kUpright;
                                }
                            }
                        }
                    }
                }

                //�V���{���ʃX�|�[��
                if (enemy[i]->EnemyStateJudgment() == true)
                {
                    if ((bubble[i]->GetDrawFlg() == false) && (bubble[i]->GetGetFlg() == false))
                    {
                        bubble[i] = new Bubble(enemy[i]->get_location_x, enemy[i]->get_location_y, true, false);
                    }
                }

                if (enemy[i]->GetEnemyDeathFlg() == 1)
                {
                    enemy_death++;
                    enemy[i]->SetEnemyDeathFlg(0);
                }

                if (enemy[i]->GetEnemyDeleteFlg() == 1)
                {
                    enemy[i] = nullptr;
                }
            }
        }

        // �X�e�[�W�J�ڂ̏���
        switch (stage)
        {
        case 0:
            // �X�e�[�W1
            if (enemy_death >= 3)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // �X�e�[�W�J��
                    ChangeScene();
                }
            }
            break;
        case 1:
            // �X�e�[�W2
            if (enemy_death >= 5)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // �X�e�[�W�J��
                    ChangeScene();
                }
            }
            break;
        case 2:
             // �X�e�[�W3
            if (enemy_death >= 5)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // �X�e�[�W�J��
                    ChangeScene();
                }
            }
            break;
        case 3:
            // �X�e�[�W4
            if (enemy_death >= 5)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // �X�e�[�W�J��
                    ChangeScene();
                }
            }
            break;
        case 4:
            // �X�e�[�W5
            if (enemy_death >= 6)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    stage = -1;
                    // �X�e�[�W�J��
                    ChangeScene();
                }
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
                //�v���C���[��X���W��160�ȏォ��X���W��480������Y���W��360�ȏ�ŋ����o��
                if (player->GetLocationX() >= 160 && player->GetLocationX() <= 480 && player->GetLocationY() >= 390) //&& ++fps > 180)
                {
                    //fps���Z 
                    if (++fps > 180)
                    {
                        if (fps > 220)
                        {
                            fps = 0;
                        }
                        fish->FishReversalFlg();
                        if (fish->HitBox(player) == true)
                        {
                            //player->PlayerReset();
                            //fish->PlayerEat();
                        }
                    }
                }
                else
                {
                    fps = 0;
                }
            }
            for (int i = 0; i < 3; i++)
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
    if(PadInput::OnButton(XINPUT_BUTTON_Y))
    {
        if (stage == 4)
        {
            stage = -1;
        }
        ChangeScene();
        ui->SetStageNum();     //�X�e�[�W���\���ύX
    }
    return this; // �V�[���p��
};

void GameMain::Draw() const 
{ 
    // ��邱�Ƃ͕`��̂݁A��΂ɒl�̍X�V�͂��Ȃ�

    // �f�o�b�O�p
    DrawFormatString(120, 50, 0xffffff, " enemy_d = %d", enemy_death);

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

        // �G�̕`�揈��
        for (int i = 0; i <= 5; i++)
        {
            if (enemy[i] != nullptr)
            {
                enemy[i]->Draw();
            }
        }
    }

    player->Draw();        //�v���C���[�摜�̕`�揈��

    thunder->Draw();        //���摜�̕`�揈��
   
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

    //�V���{���ʂ̕`�揈��
    for (int i = 0; i <= 5; i++)
    {
        bubble[i]->Draw();
    } 

    ui->Draw();
};
//�X�e�[�W�̐ؑ�
void GameMain::ChangeScene()
{
    stage++;
    enemy_death = 0;
    wait_time = 0;

    // �v���C���[���Q�[���J�n�ʒu��
    player = new Player();

    // �G�̔z�����ɂ���
    for (int i = 0; i <= 5; i++)
    {
        enemy[i] = nullptr;
    }

    // �X�e�[�W�̔z�����ɂ���
    for (int i = 0; i < 10; i++)
    {
        stage_floor[i] = nullptr;
    }

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

    // �V���{���ʂ̏�����
        for (int i = 0; i <= 5; i++)
        {
            bubble[i] = new Bubble(0, 0, false, false);
        }
}