#include "GameMain.h"
#include"common.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // 初期化処理
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
    case 0://ステージ1
        for (int i = 0; i < 3; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // 敵の生成
        for (int i = 0; i <= 2; i++)
        {
            // ピンク色の敵が3体
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        break;
    case 1://ステージ2
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // 敵の生成
        for (int i = 0; i <= 2; i++)
        {
            // ピンク色の敵が3体
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        // 緑の敵が2体
        enemy[3] = new Enemy(150.0f, 135.0f, 1);
        enemy[4] = new Enemy(510.0f, 115.0f, 1);
    case 2://ステージ3
        for (int i = 0; i <10 ;i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // ピンク色の敵が1体
        enemy[0] = new Enemy(320.0f, 335.0f, 0);
        // 緑色の敵が2体
        enemy[1] = new Enemy(190.0f, 232.0f, 1);
        enemy[2] = new Enemy(345.0f, 150.0f, 1);
        // 赤色の敵が2体
        enemy[3] = new Enemy(220.0f, 65.0f, 2);
        enemy[4] = new Enemy(530.0f, 65.0f, 2);
        break;
    case 3://ステージ4
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i, stage);
        }
        // ピンク色の敵が3体
        enemy[0] = new Enemy(145.0f, 235.0f, 0);
        enemy[1] = new Enemy(265.0f, 266.0f, 0);
        enemy[2] = new Enemy(485.0f, 250.0f, 0);
        // 緑色の敵が1体
        enemy[3] = new Enemy(355.0f, 150.0f, 1);
        // 赤色の敵が1体
        enemy[4] = new Enemy(390.0f, 335.0f, 2);
        break;
    case 4://ステージ5
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // ピンク色の敵が2体
        enemy[0] = new Enemy(230.0f, 300.0f, 0);
        enemy[1] = new Enemy(380.0f, 300.0f, 0);
        // 緑色の敵が3体
        enemy[2] = new Enemy(110.0f, 165.0f, 1);
        enemy[3] = new Enemy(270.0f, 132.0f, 1);
        enemy[4] = new Enemy(510.0f, 117.0f, 1);
        // 赤色の敵が1体
        enemy[5] = new Enemy(240.0f, 50.0f, 2);
        break;
    }

    //ポーズではない
    pause_flag = FALSE;

    enemy_death = 0;        // 倒した敵の数
    wait_time = 0;          // ステージ遷移するまでの待機時間
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
    // 終了処理
};

AbstractScene* GameMain::Update()
{
    //ポーズ切り替え処理
    if (PadInput::OnButton(XINPUT_BUTTON_START))       // STARTボタンが押されたとき
    {
        pause_flag = !pause_flag;
    }
    //ポーズ中ではない時

    if (pause_flag == FALSE)
    {
        //ゲームメイン処理を入れる
        stageitem->Update();

        player->Update();

        fish->Update();

        thunder->Update();

        for (int i = 0; i <= 5; i++)
        {
            bubble[i]->Update();
            //シャボン玉とプレイヤーのヒット処理
            if (bubble[i]->HitBox(player) == true)
            {
                if (bubble[i]->GetGetFlg() == false) 
                {
                    ui->AddScore(500);      //500点加算
                }
                bubble[i]->ChangeGetFlg();
            }
        }

        for (int i = 0; i <= 5; i++)
        {
            if (enemy[i] != nullptr)
            {
                // 敵の更新処理
                enemy[i]->Update();

                // 敵とプレイヤーの当たり判定
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

                // 敵とステージの当たり判定
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
                                    // 飛んでいるときにステージに着地したとき
                                    // 直ぐに飛び立つ
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

                //シャボン玉スポーン
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

        // ステージ遷移の条件
        switch (stage)
        {
        case 0:
            // ステージ1
            if (enemy_death >= 3)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // ステージ遷移
                    ChangeScene();
                }
            }
            break;
        case 1:
            // ステージ2
            if (enemy_death >= 5)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // ステージ遷移
                    ChangeScene();
                }
            }
            break;
        case 2:
             // ステージ3
            if (enemy_death >= 5)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // ステージ遷移
                    ChangeScene();
                }
            }
            break;
        case 3:
            // ステージ4
            if (enemy_death >= 5)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    // ステージ遷移
                    ChangeScene();
                }
            }
            break;
        case 4:
            // ステージ5
            if (enemy_death >= 6)
            {
                if (++wait_time >= 10)
                {
                    WaitTimer(1000);
                    stage = -1;
                    // ステージ遷移
                    ChangeScene();
                }
            }
            break;
        }

        //プレイヤーが床に当たったら......
        switch (stage)
        {
        case 0://ステージ1
            if (player->PlayerFlg() == true)
            {
                player->PlayerReversalFlg();
                color = 0x0ffff0;
            }
            else {
                color = 0xffffff;
                //プレイヤーがX座標が160以上かつX座標が480未満でY座標が360以上で魚が出現
                if (player->GetLocationX() >= 160 && player->GetLocationX() <= 480 && player->GetLocationY() >= 390) //&& ++fps > 180)
                {
                    //fps加算 
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
        case 1://ステージ2
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
        case 2://ステージ3
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
        case 3://ステージ4
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
        case 4://ステージ5
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

    // ここで値の更新など、処理)

    //object->Update();
    
    //player->Move();

    //collision->HitBox(object);


    // ステージの管理
    if(PadInput::OnButton(XINPUT_BUTTON_Y))
    {
        if (stage == 4)
        {
            stage = -1;
        }
        ChangeScene();
        ui->SetStageNum();     //ステージ数表示変更
    }
    return this; // シーン継続
};

void GameMain::Draw() const 
{ 
    // やることは描画のみ、絶対に値の更新はしない

    // デバッグ用
    DrawFormatString(120, 50, 0xffffff, " enemy_d = %d", enemy_death);

    //ポーズ画面の描画
    if (pause_flag == TRUE)
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, " PAUSE ");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 0);  //ステージ以外全て消す
    }
    else 
    {
        SetFontSize(16);
        DrawFormatString(20, 50, color, "Game Main");
        player->Draw();     //プレイヤー画像の描画処理
        fish->Draw();

        // 敵の描画処理
        for (int i = 0; i <= 5; i++)
        {
            if (enemy[i] != nullptr)
            {
                enemy[i]->Draw();
            }
        }
    }

    player->Draw();        //プレイヤー画像の描画処理

    thunder->Draw();        //雷画像の描画処理
   
    //ポーズでプレイヤーと敵を消す為にALPHA、NOBLENDの中に書け
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0); 

    //↓UI、ステージを書く

    //ステージ画像の描画処理
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

    //シャボン玉の描画処理
    for (int i = 0; i <= 5; i++)
    {
        bubble[i]->Draw();
    } 

    ui->Draw();
};
//ステージの切替
void GameMain::ChangeScene()
{
    stage++;
    enemy_death = 0;
    wait_time = 0;

    // プレイヤーをゲーム開始位置へ
    player = new Player();

    // 敵の配列を空にする
    for (int i = 0; i <= 5; i++)
    {
        enemy[i] = nullptr;
    }

    // ステージの配列を空にする
    for (int i = 0; i < 10; i++)
    {
        stage_floor[i] = nullptr;
    }

    switch (stage)
    {
    case 0:
        // ステージ1
        for (int i = 0; i < 3; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // 敵の生成
        for (int i = 0; i <= 2; i++)
        {
            // ピンク色の敵が3体
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        break;
    case 1:
        // ステージ2
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // 敵の生成
        for (int i = 0; i <= 2; i++)
        {
            // ピンク色の敵が3体
            enemy[i] = new Enemy(i * 100.0f + 220.0f, 252.0f, 0);
        }
        // 緑の敵が2体
        enemy[3] = new Enemy(150.0f, 135.0f, 1);
        enemy[4] = new Enemy(510.0f, 115.0f, 1);
        break;
    case 2:
        for (int i = 0; i < 10; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // ピンク色の敵が1体
        enemy[0] = new Enemy(320.0f, 335.0f, 0);
        // 緑色の敵が2体
        enemy[1] = new Enemy(190.0f, 232.0f, 1);
        enemy[2] = new Enemy(345.0f, 150.0f, 1);
        // 赤色の敵が2体
        enemy[3] = new Enemy(220.0f, 65.0f, 2);
        enemy[4] = new Enemy(530.0f, 65.0f, 2);
        break;
    case 3:
        // ステージ4
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i, stage);
        }
        // ピンク色の敵が3体
        enemy[0] = new Enemy(145.0f, 235.0f, 0);
        enemy[1] = new Enemy(265.0f, 266.0f, 0);
        enemy[2] = new Enemy(485.0f, 250.0f, 0);
        // 緑色の敵が1体
        enemy[3] = new Enemy(355.0f, 150.0f, 1);
        // 赤色の敵が1体
        enemy[4] = new Enemy(390.0f, 335.0f, 2);
        break;
    case 4:
        // ステージ5
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        // ピンク色の敵が2体
        enemy[0] = new Enemy(230.0f, 300.0f, 0);
        enemy[1] = new Enemy(380.0f, 300.0f, 0);
        // 緑色の敵が3体
        enemy[2] = new Enemy(110.0f, 165.0f, 1);
        enemy[3] = new Enemy(270.0f, 132.0f, 1);
        enemy[4] = new Enemy(510.0f, 117.0f, 1);
        // 赤色の敵が1体
        enemy[5] = new Enemy(240.0f, 50.0f, 2);
        break;
    }

    // シャボン玉の初期化
        for (int i = 0; i <= 5; i++)
        {
            bubble[i] = new Bubble(0, 0, false, false);
        }
}