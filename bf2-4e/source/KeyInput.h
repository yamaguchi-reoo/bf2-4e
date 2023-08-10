#pragma once
#include"DxLib.h"

#define KEY_MAX 256
#define MOUSE_MAX 256

struct CURSOR {
	int x;	//x座標
	int y;	//y座標
};

class KeyInput
{
private:
	static int NowKey[KEY_MAX];		//今回の入力キー
	static int OldKey[KEY_MAX];		//前回の入力キー
	static int NowMouse[MOUSE_MAX]; //今回の入力キー
	static int OldMouse[MOUSE_MAX]; //前回の入力キー
	static CURSOR Cursor;

public:
	//パッド情報の更新
	static void UpdateKey() {
		// 入力キー取得
		for (int i = 0; i < KEY_MAX; i++) {
			OldKey[i] = NowKey[i];
			NowKey[i] = CheckHitKey(i);
		}
		//入力(マウス)取得
		for (int i = 0; i < MOUSE_MAX; i++) {
			OldMouse[i] = NowMouse[i];
			if (GetMouseInput() == i)
			{
				NowMouse[i] = 1;
			}
			else
			{
				NowMouse[i] = 0;
			}
		}
		//カーソルの取得
		GetMousePoint(&Cursor.x, &Cursor.y);
	}
	//ボタンを押した瞬間
	static bool OnKey(int key) {
		return (NowKey[key] == 1 && OldKey[key] == 0);
	}

	//ボタンを押した瞬間
	static bool OnPresed(int key) {
		return (NowKey[key] == 1);

	}
	//ボタンを押した瞬間
	static bool OnRelease(int key) {
		return (NowKey[key] == 0 && OldKey[key] == 1);
	}

	//マウス押した瞬間
	static bool OnMouse(int mouse) {
		return (NowMouse[mouse] == 1 && OldMouse[mouse] == 0);
	}

	//マウス押した瞬間
	static bool OnPresedMouse(int mouse) {
		return (NowMouse[mouse] == 1);
	}

	//マウス押した瞬間
	static bool OnReleaseMouse(int mouse) {
		return (NowMouse[mouse] == 0 && OldMouse[mouse] == 1);
	}

	static CURSOR GetMouseCursor()
	{
		return Cursor;
	}
};



