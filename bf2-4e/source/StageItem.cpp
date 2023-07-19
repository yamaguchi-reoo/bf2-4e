#include "StageItem.h"
#include "DxLib.h"

StageItem::StageItem()
{
	//—‹‚Ì‰æ‘œ“Ç
	for (int i = 0; i < 2; i++)
	{
		thunder_image[i] = NULL;
	}
	LoadDivGraph("Source/Resource/images/Stage/Stage_CloudAnimation.png", 30, 8, 4, 64, 64, thunder_image);
}

StageItem::~StageItem()
{
}

void StageItem::Update()
{
}

void StageItem::Draw() const
{
	DrawRotaGraph(150, 180, 1, 0, thunder_image[0], TRUE, FALSE);

}


