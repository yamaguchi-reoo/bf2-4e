#include "DxLib.h"
#include "UI.h"
#include "Title.h"

// �R���X�g���N�^
UI::UI()
{
	
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
	//�X�R�A�̕`��i���j
	DrawFormatString(0, 100, 0xffffff, "Hallo");

	//�|�[�Y��ʂ̕`��
	SetFontSize(100);
	DrawString(200, 320, "--- �|�[�Y�� ---", 0x000000);
}