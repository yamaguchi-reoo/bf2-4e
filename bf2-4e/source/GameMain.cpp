#include "GameMain.h"
#include"common.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // 初期化処理
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

    //ポーズではない
    pause_flag = FALSE;
};

GameMain::~GameMain() 
{
    delete object;
    delete stagefloor;
    // 終了処理
};

AbstractScene* GameMain::Update()
{
    //ポーズ切り替え処理
    if (PadInput::OnButton(XINPUT_BUTTON_START))       // STARTが押されたとき
    {
        pause_flag = !pause_flag;
    }
    //ポーズ中ではない時
    if (pause_flag == FALSE)
    {
        //ゲームメイン処理を入れる

        player->Update();

        enemy->Update();

        collision->HitBox(object);
    }
    // ここで値の更新など、処理)

    object->Update();

    player->Update();
    
    //player->Move();
    enemy->Update();

    collision->HitBox(object);


    if(PadInput::OnButton(XINPUT_BUTTON_START)) {
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
        DrawFormatString(20, 50, 0xffffff, "Game Main");
    }

    player->Draw();        //プレイヤー画像の描画処理

    enemy->Draw();         //敵画像の描画処理


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
    //ポーズでプレイヤーと敵を消す為にALPHA、NOBLENDの中に書け
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND,0); 

    //↓UI、ステージを書く
    //object->Draw();        //ステージ画像の描画処理
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