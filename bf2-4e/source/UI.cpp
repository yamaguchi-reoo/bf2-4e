#include "DxLib.h"
#include "UI.h"
#include "Title.h"

// �R���X�g���N�^
UI::UI()
{
	for (int i = 0; i < 19; i++)
	{
		numimage[i];
	
	}

	//LoadGraph("Source/Resource/images/UI/UI_Score.png");
}

// �f�X�g���N�^
UI::~UI()
{
}

// �`��ȊO�̍X�V������
void UI::Update()
{
}

// �`��Ɋւ��邱�Ƃ�����
void UI::Draw() const
{


	//�X�R�A�`��
	DrawGraph(100, 100,scoreimage,TRUE);

	//�X�R�A�̕`��i���j
	//DrawFormatString(0, 100, 0xffffff, "Hallo");

	//�|�[�Y��ʂ̕`��
	SetFontSize(100);
	DrawString(200, 320, "--- PAUSE ---", 0x000000);
}