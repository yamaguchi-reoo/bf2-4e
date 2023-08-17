#include "DxLib.h"
#include "Bubble.h"
#include <math.h>

Bubble::Bubble(float posX, float posY, bool drawflg, bool getflg)
{
	for (int i = 0; i < 4; i++)
	{
		BubbleImage[i] = 0;
	}
	LoadDivGraph("Source/Resource/images/Stage/Stage_BubbleAnimation.png", 4, 4, 1, 64, 64, BubbleImage);

	animation_count = 0;					// アニメーション用カウント

	delete_count = 0;						//消去用カウント

	now_image = 0;							// 今から表示される画像
	next_image = 0;							// 次に表示される画像

	location.x = 0;
	location.y = 0;
	erea.height = 40;
	erea.width = 40;
	erea.width_rate = 0;
	erea.height_rate = 0;


	PosX = 0;		// 描画座標X
	PosY = 0;		// 描画座標Y
	Radius = 0;		// 半径(描画用)
	CenterX = posX;	// 中心座標X
	CenterY = posY;	// 中心座標Y
	Angle = 0;		// 角度
	Length = 30;		// 半径の長さ

	GetFlg = getflg;//false;		//ゲットフラグ(true:Get false:NotGet)

	DrawFlg = drawflg;		//画像の描画フラグ(true:描画する false:描画しない)

	scoreimage = LoadGraph("Source/Resource/images/Score/GetScore_500.png");
}

Bubble::~Bubble()
{

}

void Bubble::Update()
{

	location.x = PosX - erea.width / 2;
	location.y = PosY - erea.height / 2;

	//ゲット処理
	if (GetFlg == true) 
	{
		if(now_image!=3){
			now_image = 3;
		}
		if (++delete_count >= 60) 
		{
			DrawFlg = false;
		}
	}
	else
	{
		BubbleAnimation();
		MoveBubble();
	}
	
}

void Bubble::Draw() const
{
	if (DrawFlg == true) 
	{
		DrawRotaGraph((int)PosX, (int)PosY, 1, 0, BubbleImage[now_image], TRUE);
		//DrawBox((int)location.x, (int)location.y, (int)location.x + (int)erea.width, (int)location.y + (int)erea.height, 0xffffff, false);

		if (now_image == 3)
		{
			DrawGraph((int)PosX - 15, (int)PosY - 30, scoreimage, TRUE);
		}
	}
}

void Bubble::BubbleAnimation(void) 
{
	animation_count++;

	// 画像番号は8, 9（2枚）
	next_image = animation_count / 25 ;

	if (now_image != next_image && next_image < 3)
	{
		now_image = next_image;
	}

	if (animation_count >= 75)
	{
		// カウントを0に戻す
		animation_count = 0;
	}
}

void Bubble::MoveBubble(void)
{
	// 中心座標に角度と長さを使用した円の位置を加算する
	// 度数法の角度を弧度法に変換
	float radius = Angle * 3.14f / 180.0f;

	// 三角関数を使用し、円の位置を割り出す。
	float add_x = (float)cos(radius) * Length;
	float add_y = (float)sin(radius) * Length;

	// 結果ででた位置を中心位置に加算し、それを描画位置とする
	PosX = CenterX + add_x;
	//location.y = CenterY + add_y;

	// 角度を変える
	Angle += 2.0f;

	//浮上する
	CenterY -= 0.5f;
	PosY = CenterY;
}

//ゲットフラグ変更
void Bubble::ChangeGetFlg(void)
{
	GetFlg = true;
}

int Bubble::GetDrawFlg(void)
{
	return DrawFlg;
}

int Bubble::GetGetFlg(void)
{
	return GetFlg;
}

