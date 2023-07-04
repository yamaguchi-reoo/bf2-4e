#include"Stage.h"
#include"DxLib.h"


Stage::Stage() 
{
	stage_number = 0;

	stage_image01= LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
}
Stage::~Stage() 
{
}
void Stage::Update() 
{
}
void Stage::Draw()const 
{
	DrawGraph(180, 284, stage_image01, TRUE);
}
