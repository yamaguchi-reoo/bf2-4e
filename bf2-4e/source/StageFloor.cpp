#include"StageFloor.h""
#include"PadInput.h"

StageFloor::StageFloor(int i)
{
	switch (i)
	{
	case 0:
		location.x = 180;
		location.y = 284;
		erea.width = 280;
		erea.height = 17;
		erea.width_rate = 0.1;
		erea.height_rate = 0.1;
		floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
		break;
	case 1:
		location.x = 0;
		location.y = 416;
		floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
		break;
	case 2:
		location.x = 480;
		location.y = 416;
		floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
		break;
	case 3:
		location.x = 160;
		location.y = 444;
		floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Sea01.png");
		break;
	}
	erea.width = 280;
	erea.height = 17;
	erea.width_rate = 0.1;
	erea.height_rate = 0.1;
	//floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
}
StageFloor::~StageFloor()
{
}
void StageFloor::Update()
{


}
void StageFloor::Draw()const
{
	DrawGraph(location.x, location.y, floor_image01,TRUE);
	//DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, FALSE);
}