#include"Stage.h"
#include"DxLib.h"
#include"PadInput.h"

Stage::Stage() 
{
	stage_number = 0;

	sea_image = LoadGraph("source/Resource/images/Stage/Stage_Sea01.png");

	floor_number[0].image = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
	floor_number[1].image= LoadGraph("source/Resource/images/Stage/Stage_Footing02.png");
	floor_number[2].image = LoadGraph("source/Resource/images/Stage/Stage_Footing03.png");
	floor_number[3].image = LoadGraph("source/Resource/images/Stage/Stage_Footing04.png");
	floor_number[4].image = LoadGraph("source/Resource/images/Stage/Stage_Footing05.png");
	floor_number[5].image = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
	floor_number[6].image = LoadGraph("source/Resource/images/Stage/Stage_Footing07.png");
	floor_number[7].image = LoadGraph("source/Resource/images/Stage/Stage_Footing08.png");

	floor_number[8].image = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
	floor_number[9].image = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
	floor_number[10].image = LoadGraph("source/Resource/images/Stage/Stage_Land_Left02.png");
	floor_number[11].image = LoadGraph("source/Resource/images/Stage/Stage_Land_Right02.png");
}
Stage::~Stage()
{
}
void Stage::Update()
{
	//Aボタンで次のステージへ
	if (PadInput::OnButton(XINPUT_BUTTON_A))
	{
		++stage_number;
		if (stage_number == 5) {
			stage_number = 0;
		}
	}
	//Bボタンで前のステージへ
	if (PadInput::OnButton(XINPUT_BUTTON_Y))
	{
		--stage_number;
		if (stage_number == -1) {
			stage_number = 0;
		}
	}
	//オブジェクト配置
	switch (stage_number)
	{
	case 0://ステージ1
		break;
	case 1:
		break;
	}

}
void Stage::Draw()const
{
	switch (stage_number)
	{
	case 0://ステージ1
		DrawGraph(180, 284, floor_number[0].image, TRUE);
		break;
	case 1:
		DrawGraph(180, 284, floor_number[0].image, TRUE);
		DrawGraph(99, 166, floor_number[1].image, TRUE);
		DrawGraph(459, 149, floor_number[1].image, TRUE);
		break;
	case 2:
		DrawGraph(279, 368, floor_number[2].image, TRUE);
		DrawGraph(159, 267, floor_number[3].image, TRUE);
		DrawGraph(320, 183, floor_number[3].image, TRUE);
		DrawGraph(499, 98, floor_number[3].image, TRUE);
		DrawGraph(199, 98, floor_number[4].image, TRUE);
		break;
	case 3:
		DrawGraph(120, 267, floor_number[5].image, TRUE);
		DrawGraph(239, 300, floor_number[5].image, TRUE);
		DrawGraph(320, 183, floor_number[5].image, TRUE);
		DrawGraph(359, 368, floor_number[5].image, TRUE);
		DrawGraph(450, 284, floor_number[5].image, TRUE);
		break;
	case 4:
		DrawGraph(219, 81, floor_number[5].image, TRUE);
		DrawGraph(199, 334, floor_number[5].image, TRUE);
		DrawGraph(374, 334, floor_number[5].image, TRUE);
		DrawGraph(99, 199, floor_number[6].image, TRUE);
		DrawGraph(259, 165, floor_number[6].image, TRUE);
		DrawGraph(499, 149, floor_number[7].image, TRUE);
		break;
	}

	if (stage_number < 3) 
	{
		DrawGraph(0, 416, floor_number[8].image, TRUE);
		DrawGraph(480, 416, floor_number[9].image, TRUE);
	}
	else
	{
		DrawGraph(0, 416, floor_number[10].image, TRUE);
		DrawGraph(480, 416, floor_number[11].image, TRUE);
	}
	//海
	DrawGraph(160, 444, sea_image, TRUE);
}