#include "DxLib.h"
#include "UI.h"
#include "Title.h"

UI::UI()
{
	
}

UI::~UI()
{
}

void UI::Update()
{
}

void UI::Draw() const
{
	//�X�R�A�̕`��i���j
	DrawFormatString(0, 100, 0xffffff, "Hallo");

	//�|�[�Y��ʂ̕`��
	SetFontSize(100);
	DrawString(200, 320, "--- �|�[�Y�� ---", 0x000000);
}