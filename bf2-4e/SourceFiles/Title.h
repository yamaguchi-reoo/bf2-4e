#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene {
private:
    int state = 0;
public:
    // �R���X�g���N�^
    Title();

    // �f�X�g���N�^
    ~Title();

	// �`��ȊO�̍X�V������
	virtual AbstractScene* Update() override;

	// �`��Ɋւ��邱�Ƃ�����
	virtual void Draw() const override;
};