#include"Stage.h"
#include"DxLib.h"
#include"PadInput.h"

Stage::Stage() 
{
	
	stage_number = 0;


	floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
	floor_image02 = LoadGraph("source/Resource/images/Stage/Stage_Footing02.png");
	floor_image03 = LoadGraph("source/Resource/images/Stage/Stage_Footing03.png");
	floor_image04 = LoadGraph("source/Resource/images/Stage/Stage_Footing04.png");
	floor_image05 = LoadGraph("source/Resource/images/Stage/Stage_Footing05.png");
	floor_image06 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
	floor_image07 = LoadGraph("source/Resource/images/Stage/Stage_Footing07.png");
	floor_image08 = LoadGraph("source/Resource/images/Stage/Stage_Footing08.png");

	floor_left_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
	floor_left_image02 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left02.png");
	floor_right_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
	floor_right_image02 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right02.png");

	sea_image = LoadGraph("source/Resource/images/Stage/Stage_Sea01.png");
}
Stage::~Stage() 
{
	
}
void Stage::Update()
{
	//Aボタンでステージ遷移
	if (PadInput::OnButton(XINPUT_BUTTON_A))
	{
		stage_number++;
	}

	//オブジェクト配置
	switch (stage_number)
	{
	case 0://ステージ1
		for (stage_object = 0; stage_object <= 4; stage_object++)
		{
			if (stage_object == 0) 
			{
				SetPosition(180, 284, stage_object, floor_image01);
			}
		}
		break;
	case 1://ステージ2
		for (stage_object = 0; stage_object <= 4; stage_object++)
		{
			if (stage_object == 0) 
			{
				SetPosition(99, 166, stage_object, floor_image02);
			}
			if (stage_object == 1) 
			{
				SetPosition(180, 284, stage_object, floor_image01);
			}
			if (stage_object == 2) 
			{
				SetPosition(459, 149, stage_object, floor_image02);
			}
		}
		break;
	case 2://ステージ3
		for (stage_object = 0; stage_object <= 4; stage_object++)
		{
			if (stage_object == 0)
			{
				SetPosition(199,98, stage_object, floor_image05);
			}
			if (stage_object == 1)
			{
				SetPosition(159, 267, stage_object, floor_image04);
			}
			if (stage_object == 2)
			{
				SetPosition(320, 183, stage_object, floor_image04);
			}
			if (stage_object == 3) 
			{
				SetPosition(279, 368, stage_object, floor_image03);
			}
			if (stage_object == 4) 
			{
				SetPosition(499, 98, stage_object, floor_image04);
			}
		}
		break;
	case 3://ステージ4
		for (stage_object = 0; stage_object <= 4; stage_object++)
		{
			if (stage_object == 0)
			{
				SetPosition(120, 267, stage_object, floor_image06);
			}
			if (stage_object == 1)
			{
				SetPosition(239, 300, stage_object, floor_image06);
			}
			if (stage_object == 2)
			{
				SetPosition(320, 183, stage_object, floor_image06);
			}
			if (stage_object == 3)
			{
				SetPosition(359, 368, stage_object, floor_image06);
			}
			if (stage_object == 4)
			{
				SetPosition(450, 284, stage_object, floor_image06);
			}
		}
		break;
	case 4://ステージ5
		for (stage_object = 0; stage_object <= 5; stage_object++)
		{
			if (stage_object == 0)
			{
				SetPosition(99, 199, stage_object, floor_image07);
			}
			if (stage_object == 1)
			{
				SetPosition(219, 81, stage_object, floor_image06);
			}
			if (stage_object == 2)
			{
				SetPosition(199, 334, stage_object, floor_image06);
			}
			if (stage_object == 3)
			{
				SetPosition(259, 165, stage_object, floor_image07);
			}
			if (stage_object == 4)
			{
				SetPosition(374, 334, stage_object, floor_image06);
			}
			if (stage_object == 5)
			{
				SetPosition(499, 149, stage_object, floor_image08);
			}
		}
		break;
	default:
		break;
	}
	//床（左右）
	//ステージ数が4になったら色変更
	if (stage_number < 3)
	{
		for (stage_object = 6; stage_object <= 7; stage_object++)
		{
			if (stage_object == 6)
			{
				SetPosition(0, 416, stage_object, floor_left_image01);
			}
			if (stage_object == 7)
			{
				SetPosition(480, 416, stage_object, floor_right_image01);
			}
		}
	}
	else
	{
		for (stage_object = 6; stage_object <= 7; stage_object++)
		{
			if (stage_object == 6)
			{
				SetPosition(0, 416, stage_object, floor_left_image02);
			}
			if (stage_object == 7)
			{
				SetPosition(480, 416, stage_object, floor_right_image02);
			}
		}
	}
}
void Stage::Draw()const 
{
	switch (stage_number)
	{
	case 0://ステージ1
		DrawGraph(stage_location[0].x, stage_location[0].y , stage_location[0].image, TRUE);
		break;
	case 1:	//ステージ2
		for (int i = 0; i <= 3; i++) {
			DrawGraph(stage_location[i].x, stage_location[i].y, stage_location[i].image, TRUE);
		}
		break;
	case 2: //ステージ3
		for (int i = 0; i <= 4; i++) {
			DrawGraph(stage_location[i].x, stage_location[i].y, stage_location[i].image, TRUE);
		}
		break;
	case 3: //ステージ4
		for (int i = 0; i <= 4; i++) {
			DrawGraph(stage_location[i].x, stage_location[i].y, stage_location[i].image, TRUE);
		}
		break;
	case 4: //ステージ5
		for (int i = 0; i <= 5; i++) {
			DrawGraph(stage_location[i].x, stage_location[i].y, stage_location[i].image, TRUE);
		}
		break;
	default:
		break;
	}
	//ステージ数が4になったら色変更
	for (int i = 6; i <= 7; i++) {
		DrawGraph(stage_location[i].x, stage_location[i].y, stage_location[i].image, TRUE);
	}
	//海
	DrawGraph(160, 444, sea_image, TRUE);
}
// オブジェクトの位置設定する関数
void Stage::SetPosition(int posX, int posY, int num, int image)
{
	stage_location[num].x = posX;
	stage_location[num].y = posY;

	stage_location[num].image = image;

	if (image == floor_image01) 
	{
		stage_location[num].w = 280;
		stage_location[num].h = 17;
	}
	if (image == floor_image02)
	{
		stage_location[num].w = 122;
		stage_location[num].h = 17;
	}
	if (image == floor_image03)
	{
		stage_location[num].w = 81;
		stage_location[num].h = 17;
	}
	if (image == floor_image04)
	{
		stage_location[num].w = 62;
		stage_location[num].h = 32;
	}
	if (image == floor_image05)
	{
		stage_location[num].w = 42;
		stage_location[num].h = 17;
	}
	if (image == floor_image06)
	{
		stage_location[num].w = 62;
		stage_location[num].h = 17;
	}
	if (image == floor_image07)
	{
		stage_location[num].w = 22;
		stage_location[num].h = 51;
	}
	if (image == floor_image08)
	{
		stage_location[num].w = 22;
		stage_location[num].h = 67;
	}

	if (image == floor_image02)
	{
		stage_location[num].w = 122;
		stage_location[num].h = 17;
	}

	if (image == floor_left_image01 || image == floor_left_image02)
	{
		stage_location[num].w = 160;
		stage_location[num].h = 32;
	}
	if (image == floor_right_image01 || image == floor_right_image02)
	{
		stage_location[num].w = 160;
		stage_location[num].h = 32;
	}
}

