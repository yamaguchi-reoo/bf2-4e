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
	if (PAD_INPUT::OnButton(XINPUT_BUTTON_A)) {
		stage_number++;
	}

}
void Stage::Draw()const 
{
	switch (stage_number)
	{
	case 0://ステージ1
		DrawGraph(180, 284, floor_image01, TRUE);
		break;
	case 1:	//ステージ2
		DrawGraph(180, 284, floor_image01, TRUE);
		DrawGraph(99, 166, floor_image02, TRUE);
		DrawGraph(459, 149, floor_image02, TRUE);
		break;
	case 2: //ステージ3
		DrawGraph(279, 368, floor_image03, TRUE);
		DrawGraph(159, 267, floor_image04, TRUE);
		DrawGraph(320, 183, floor_image04, TRUE);
		DrawGraph(499, 98, floor_image04, TRUE);
		DrawGraph(199, 98, floor_image05, TRUE);
		break;
	case 3: //ステージ4
		DrawGraph(120, 267, floor_image06, TRUE);
		DrawGraph(239, 300, floor_image06, TRUE);
		DrawGraph(359, 368, floor_image06, TRUE);
		DrawGraph(320, 183, floor_image06, TRUE);
		DrawGraph(459, 284, floor_image06, TRUE);
		break;
	case 4: //ステージ5
		DrawGraph(199, 334, floor_image06, TRUE);
		DrawGraph(219, 81, floor_image06, TRUE);
		DrawGraph(379, 334, floor_image06, TRUE);
		DrawGraph(99, 199, floor_image07, TRUE);
		DrawGraph(259, 165, floor_image07, TRUE);
		DrawGraph(499, 149, floor_image08, TRUE);
		break;
	default:
		break;
	}
	//ステージ数が4になったら色変更
	if (stage_number < 3)
	{
		DrawGraph(0, 416, floor_left_image01, TRUE);
		DrawGraph(480, 416, floor_right_image01, TRUE);
	}
	else
	{
		DrawGraph(0, 416, floor_left_image02, TRUE);
		DrawGraph(480, 416, floor_right_image02, TRUE);
	}
	//海
	DrawGraph(160, 444, sea_image, TRUE);
}

