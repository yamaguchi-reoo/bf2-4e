#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene {
private:
    int LogoImage;      //ロゴ画像
    int SelectImage;    //セレクト画像
    int CreditImage;    //クレジット画像
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
