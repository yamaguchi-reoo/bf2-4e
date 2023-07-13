#include "GameMain.h"
#include "DxLib.h"
#include "PadInput.h"

GameMain::GameMain() 
{
    // 初期化処理
    object = new Stage();
    player = new Player();
    enemy = new Enemy();
    collision = new BoxCollision();
};

GameMain::~GameMain() 
{
    delete object;
    // 終了処理
};

AbstractScene* GameMain::Update() 
{ // ここで値の更新など、処理)

    object->Update();

    player->Update();
    
    enemy->Update();

    collision->HitBox(object);

    return this; // シーン継続
};

void GameMain::Draw() const 
{ // やることは描画のみ、絶対に値の更新はしない
    SetFontSize(16);

    DrawFormatString(20, 50, 0xffffff, "Game Main");

    object->Draw();        //ステージ画像の描画処理

    player->Draw();        //プレイヤー画像の描画処理

    enemy->Draw();         //プレイヤー画像の描画処理
};