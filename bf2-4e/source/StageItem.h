#pragma once

class StageItem
{
private:
	
public:
	//コンストラクタ
	StageItem();

	//デストラクタ
	~StageItem();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

};

