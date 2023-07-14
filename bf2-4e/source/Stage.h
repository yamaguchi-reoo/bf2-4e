#pragma once
#include"BoxCollision.h"

//オブジェクト配置
struct STAGE {
	int x;
	int y;
	int w;
	int h;
	int image;
};
class Stage :public BoxCollision
{
private:
	int stage_number;//ステージ数用変数
	struct STAGE stage_location[8]{ 0,0,0,0,0,0,0,0,0 };
	struct STAGE floor_number[12];//構造体用配列
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

	int floor_image[8];
	int floor_image_left[2];
	int floor_image_right[2];
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
	void SetPosition(int position_x, int position_y, int number, int image);

	//オブジェクトの位置を受け取る関数
	void GetObjectErea(int _width, int _height, int _x, int _y,int _number);
};
