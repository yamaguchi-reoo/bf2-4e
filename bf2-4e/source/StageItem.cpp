#include "StageItem.h"
#include "DxLib.h"

StageItem::StageItem()
{

	//—‹‚Ì‰æ‘œ“Ç
	LoadDivGraph("Source/Resource/images/Stage/Stage_CloudAnimation.png", 3, 3, 1, 128, 64, thunder_image); 
		
	anime_num = 0;
}

StageItem::~StageItem()
{
}

void StageItem::Update()
{
	++time;
	if (time % 100 == 0) 
	{
		anime_num = anime_num + 1;
	}
	if (anime_num == 3)
	{
		anime_num = 0;
	}
}

void StageItem::Draw() const
{
	DrawRotaGraph(150, 180, 1.5f, 0, thunder_image[anime_num], 1, 1);
}
