#include "GameMain.h"
#include"common.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // 初期化処理
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
    case 0://ステージ1
        for (int i = 0; i < 3; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 1://ステージ2
        for (int i = 0; i < 5; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 2://ステージ3
        for (int i = 0; i <7 ;i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    case 3://ステージ4
        for (int i = 0; i < 7; i++)
        {
            stage_floor[i] = new StageFloor(i, stage);
        }
        break;
    case 4://ステージ5
        for (int i = 0; i < 8; i++)
        {
            stage_floor[i] = new StageFloor(i,stage);
        }
        break;
    }

    //ポーズではない
    pause_flag = FALSE;
};

GameMain::~GameMain() 
{
    delete stage_floor;
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

        enemy->Update();

        //collision->HitBox(object);

        //プレイヤーが床に当たったら......
        switch (stage)
        {
        case 0://ステージ1
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
        case 1://ステージ2
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
        case 2://ステージ3
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
        case 3://ステージ4
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
        case 4://ステージ5
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
    // ここで値の更新など、処理)

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
    return this; // シーン継続
};

void GameMain::Draw() const 
{ 
    // やることは描画のみ、絶対に値の更新はしない

    //ポーズ画面の描画
    if (pause_flag == TRUE)
    {
        SetFontSize(16);
        DrawFormatString(20, 50, 0xffffff, " PAUSE ");
        SetDrawBlendMode(DX_BLENDMODE_ALPHA,0);     //ステージ以外全て消す
    }
    else 
    {
        SetFontSize(16);
        DrawFormatString(20, 50, color, "Game Main");
        player->Draw();        //プレイヤー画像の描画処理

        enemy->Draw();         //敵画像の描画処理

    }

    player->Draw();        //プレイヤー画像の描画処理

    enemy->Draw();         //敵画像の描画処理

    stageitem->Draw();     //ステージアイテムの描画処理

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
//ステージの切替
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

