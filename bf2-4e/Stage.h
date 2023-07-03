#pragma once

class Stage 
{
private:
public:
	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;
};
