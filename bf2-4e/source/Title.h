#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene {
private:
    int LogoImage;      //���S�摜
    int SelectImage;    //�Z���N�g�摜
    int CreditImage;    //�N���W�b�g�摜
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
