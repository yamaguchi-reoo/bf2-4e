#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene 
{
private:
    int logo_image;      //���S�摜
    int select_image;    //�Z���N�g�摜
    int credit_image;    //�N���W�b�g�摜
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
