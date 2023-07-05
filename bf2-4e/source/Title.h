#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene 
{
private:
    int logo_image;      //ロゴ画像
    int select_image;    //セレクト画像
    int credit_image;    //クレジット画像
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
