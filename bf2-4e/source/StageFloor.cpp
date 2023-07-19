#include"StageFloor.h""
#include"PadInput.h"

StageFloor::StageFloor(int i,int _stage)
{
	switch (_stage)
	{
	case 0:
		switch (i)
		{
		case 0:
			location.x = 180;
			location.y = 284;
			erea.width = 280;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
			break;
		case 1:
			location.x = 0;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
			break;
		case 2:
			location.x = 480;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
			break;
		}
		break;
	case 1:
		switch (i)
		{
		case 0:
			location.x = 180;
			location.y = 284;
			erea.width = 280;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing01.png");
			break;
		case 1:
			location.x = 99;
			location.y = 166;
			erea.width = 122;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing02.png");
			break;
		case 2:
			location.x = 459;
			location.y = 149;
			erea.width = 122;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing02.png");
			break;
		case 3:
			location.x = 0;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
			break;
		case 4:
			location.x = 480;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
			break;
		}
		break;
	case 2:
		switch (i)
		{
		case 0:
			location.x = 279;
			location.y = 368;
			erea.width = 81;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing03.png");
			break;
		case 1:
			location.x = 159;
			location.y = 267;
			erea.width = 62;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing04.png");
			break;
		case 2:
			location.x = 320;
			location.y = 183;
			erea.width = 62;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing04.png");
			break;
		case 3:
			location.x = 499;
			location.y = 98;
			erea.width = 62;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing04.png");
			break;
		case 4:
			location.x = 199;
			location.y = 98;
			erea.width = 42;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing05.png");
			break;
		case 5:
			location.x = 0;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left01.png");
			break;
		case 6:
			location.x = 480;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right01.png");
			break;
		}
		break;
	case 3:
		switch (i)
		{
		case 0:
			location.x = 120;
			location.y = 267;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 1:
			location.x = 239;
			location.y = 300;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 2:
			location.x = 320;
			location.y = 183;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 3:
			location.x = 359;
			location.y = 368;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 4:
			location.x = 450;
			location.y = 284;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 5:
			location.x = 0;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left02.png");
			break;
		case 6:
			location.x = 480;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right02.png");
			break;
		}
		break;
	case 4:
		switch (i)
		{
		case 0:
			location.x = 219;
			location.y = 81;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 1:
			location.x = 199;
			location.y = 334;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 2:
			location.x = 347;
			location.y = 334;
			erea.width = 62;
			erea.height = 17;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing06.png");
			break;
		case 3:
			location.x = 99;
			location.y = 199;
			erea.width = 22;
			erea.height = 51;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing07.png");
			break;
		case 4:
			location.x = 259;
			location.y = 165;
			erea.width = 22;
			erea.height = 51;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing07.png");
			break;
		case 5:
			location.x = 499;
			location.y = 149;
			erea.width = 22;
			erea.height = 67;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Footing08.png");
			break;
		case 6:
			location.x = 0;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Left02.png");
			break;
		case 7:
			location.x = 480;
			location.y = 416;
			erea.width = 160;
			erea.height = 32;
			floor_image01 = LoadGraph("source/Resource/images/Stage/Stage_Land_Right02.png");
			break;
		}
		break;
	}

	erea.width_rate = 0.1;
	erea.height_rate = 0.1;
	sea_image = LoadGraph("source/Resource/images/Stage/Stage_Sea01.png");
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
	DrawGraph(160, 444, sea_image, TRUE);
	DrawBox(location.x, location.y, location.x + erea.width, location.y + erea.height, 0xffffff, FALSE);

}	