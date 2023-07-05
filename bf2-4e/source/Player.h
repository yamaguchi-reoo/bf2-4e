#pragma once

class Player
{
private:
	int PlayerImages[30];

public:
	void PlayerDash();
	void PlayerFlight();

public:
	Player();			//コンストラクタ
	~Player();			//デストラクタ
	void Update();		//描画以外に関することを実装する
	void Draw()const;	//描画に関することを実装する
};