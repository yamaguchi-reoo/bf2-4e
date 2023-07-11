#pragma once
#include"Collision.h"

//オブジェクト配置
struct STAGE {
	int x;
	int y;
	int w;
	int h;
	int image;
};
class Stage :public BoxCollider
{
private:
	int stage_number;//ステージ数用変数
	struct STAGE stage_location[8]{0,0,0,0,0,0,0,0};//構造体用配列
	int stage_object;//オブジェクト数

	//画像用変数
	int floor_image01;
	int floor_image02;
	int floor_image03;
	int floor_image04;
	int floor_image05;
	int floor_image06;
	int floor_image07;
	int floor_image08;

	int floor_left_image01;
	int floor_left_image02;
	int floor_right_image01;
	int floor_right_image02;
	int sea_image;
public:
	//コンストラクタ
	Stage();
	//デストラクタ
	~Stage();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

	// オブジェクトの位置設定する関数
	void SetPosition(int posX, int posY, int num, int image);

	void SetObjectErea(int _w, int _h, int _x, int _y,int _num);
};
