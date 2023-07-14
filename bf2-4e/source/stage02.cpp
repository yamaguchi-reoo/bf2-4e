#include"Stage.h"
#include"DxLib.h"
#include"PadInput.h"

Stage::Stage() 
{
	stage_number;

	//floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
	//floor_image02 = LoadGraph("source/Resource/images/Stage/Stage_Footing02.png");
	//floor_image03 = LoadGraph("source/Resource/images/Stage/Stage_Footing03.png");
	//floor_image04 = LoadGraph("source/Resource/images/Stage/Stage_Footing04.png");
	//floor_image05 = LoadGraph("source/Resource/images/Stage/Stage_Footing05.png");
	//floor_image06 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
	//floor_image07 = LoadGraph("source/Resource/images/Stage/Stage_Footing07.png");
	//floor_image08 = LoadGraph("source/Resource/images/Stage/Stage_Footing08.png");

	//floor_left_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
	//floor_left_image02 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left02.png");
	//floor_right_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
	//floor_right_image02 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right02.png");

	sea_image = LoadGraph("source/Resource/images/Stage/Stage_Sea01.png");

	floor_number[0].image = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
	floor_number[0].x = 0;
	floor_number[0].y = 0;
	floor_number[0].w = 0;
	floor_number[0].h = 0;

	floor_number[1].image= LoadGraph("source/Resource/images/Stage/Stage_Footing02.png");
	floor_number[1].x = 0;
	floor_number[1].y = 0;

	//floor_number[2] = LoadGraph("source/Resource/images/Stage/Stage_Footing03.png");
	floor_image[3] = LoadGraph("source/Resource/images/Stage/Stage_Footing04.png");
	floor_image[4] = LoadGraph("source/Resource/images/Stage/Stage_Footing05.png");
	floor_image[5] = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
	floor_image[6] = LoadGraph("source/Resource/images/Stage/Stage_Footing07.png");
	floor_image[7] = LoadGraph("source/Resource/images/Stage/Stage_Footing08.png");

	floor_image_left[0] = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
	floor_image_left[1] = LoadGraph("source/Resource/images/Stage/Stage_Land_Left02.png");
	floor_image_right[0] = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
	floor_image_right[1] = LoadGraph("source/Resource/images/Stage/Stage_Land_Right02.png");
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
	}
	//Bボタンで前のステージへ
	if (PadInput::OnButton(XINPUT_BUTTON_B))
	{
		--stage_number;
	}
	//オブジェクト配置
	switch (stage_number)
	{
	case 0://ステージ1

	}

}
void Stage::Draw()const
{

}