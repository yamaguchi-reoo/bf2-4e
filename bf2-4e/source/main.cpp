#include "DxLib.h"
#include "SceneManager.h"
#include "Title.h"
#include "common.h"
#include "PadInput.h"
#include "KeyInput.h"
#include "GameMain.h"
#include "Fps.h"

//メインプログラム 開始

int WINAPI WinMain(_In_ HINSTANCE  hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR LpCmdLine, _In_ int NCmdShow) {
    SetMainWindowText("bf");         // ウィンドウタイトルを設定

    ChangeWindowMode(TRUE);                        // ウインドウモードで起動

    SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32); // ウインドウのサイズ

    if (DxLib_Init() == -1) return -1;             // DXライブラリの初期化処理

    SetDrawScreen(DX_SCREEN_BACK);                 // 描画先画面を裏にする（ダブルバッファリング）

    // タイトル シーンオブジェクト作成
    SceneManager* sceneMng = new SceneManager((AbstractScene*) new Title());

    Fps fps;

    // ゲームループし、シーンマネジャーでシーンの更新
    while ((ProcessMessage() == 0) && (sceneMng->Update() != nullptr)) 
    {
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }

        ClearDrawScreen(); // 画面の初期化
        PadInput::UpdateKey();//入力処理
        KeyInput::UpdateKey();
        // シーンマネジャーでシーンの描画開始
        sceneMng->Draw();
        fps.Update();	//更新
        //強制終了
        if (PadInput::OnButton(XINPUT_BUTTON_BACK))
        {
            break;
        }
        ScreenFlip(); // 裏画面の内容を表画面に反映する
        fps.Wait();//待機
    };

    DxLib_End(); // DXライブラリ使用の終了処理
    return 0;    // プログラムの終了
};