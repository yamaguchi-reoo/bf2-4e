#pragma once
#include "AbstractScene.h"
#include"Stage.h"
#include "Player.h"
#include "Enemy.h"

class GameMain : public AbstractScene {
private:
    Stage* stage;
    Player player;      //プレイヤークラスのオブジェクト化
    Enemy enemy;        // Enemyクラスのオブジェクト化

    int KeyFlg;         //flg管理

    bool pauseState;
    bool pauseFlag;
    bool pauseReset;

    void Pause();

public:
    // コンストラクタ
    GameMain();

    // デストラクタ
    ~GameMain();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;
};
