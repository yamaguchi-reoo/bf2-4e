#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene {
private:
    int state = 0;
    int FlashTime;        //ポーズ中の文字点滅用
    bool FlashFlg;      //ポーズ中の文字点滅用
public:
    // コンストラクタ
    Title();

    // デストラクタ
    ~Title();

    // 描画以外の更新を実装
    virtual AbstractScene* Update() override;

    // 描画に関することを実装
    virtual void Draw() const override;
};
