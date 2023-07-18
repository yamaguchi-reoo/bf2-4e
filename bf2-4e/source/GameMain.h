#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include"StageFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "BoxCollision.h"

class GameMain : public AbstractScene {
private:
    Stage* object;
    Player* player;         //プレイヤークラスのオブジェクト化
    Enemy* enemy;           // Enemyクラスのオブジェクト化
    BoxCollision* collision; //Collisionクラスのオブジェクト化 
    StageFloor* stagefloor[9];
    bool pause_flag;     //ポーズのフラグ取り

    int stage;

public:
    // コンストラクタ
    GameMain();

    // デストラクタ
    ~GameMain();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;

    void ChangeScene();
    int GetNowStage() { return stage; }
};
