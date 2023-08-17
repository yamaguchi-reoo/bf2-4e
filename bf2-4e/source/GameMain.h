#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include"StageFloor.h"
#include "Player.h"
#include "Enemy.h"
#include "BoxCollision.h"
#include"StageItem.h"
#include"Thunder.h"
#include"Fish.h"

#include "Bubble.h"

class GameMain : public AbstractScene {
private:
   // Stage* object;
    Player* player;         //プレイヤークラスのオブジェクト化
    Enemy* enemy[6];           // Enemyクラスのオブジェクト化
    StageFloor* stage_floor[10];

    StageItem* stageitem;
    Thunder* thunder;       //雷クラスのオブジェクト化
    Fish* fish;

    Bubble* bubble[6];         //シャボン玉のオブジェクト化

    bool pause_flag;     //ポーズのフラグ取り

    int color;
    int stage;
    bool flg;
    int time;
    int fps;
    int enemy_death;        // 倒した敵の数
    int wait_time;          // ステージ遷移するまでの待機時間

public:
    // コンストラクタ
    GameMain();

    // デストラクタ
    ~GameMain();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;

    //ステージの切り替え
    void ChangeScene();
};
