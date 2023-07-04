#pragma once

class Player
{
public:
	int PlayerImages[30];

public:
	Player();			//コンストラクタ
	~Player();			//デストラクタ
	void Update();		//描画以外に関することを実装する
	void Draw()const;	//描画に関することを実装する
};