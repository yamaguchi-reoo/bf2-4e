#pragma once

class UI
{
private:
	// �X�R�A�摜�����p�̕ϐ�
	int num_image[10];
	
	//�X�R�A�����p�摜�̕ϐ�
	int score_image;
	int hi_score_image;
	
	//���C�t�p
	int stock_image;
	int stock;

	//�X�e�[�W��
	int phase;
	int phase_digit[2];		//�����Ƃ̉摜�ؑ�
	int phase_image;

	//���݃X�R�A
	int score;
	int score_digit[6];		//�����Ƃ̉摜�ؑ�

	//�n�C�X�R�A
	int top_score;
	int topscore_digit[6];		//�����Ƃ̉摜�ؑ�

	//�|�[�Y�p�ϐ�
	/*bool pauseState;
	bool pauseFlag;
	bool pauseReset;*/

public:
	//�R���X�g���N�^
	UI();

	//�f�X�g���N�^
	~UI();

	// �`��ȊO�̍X�V������
	void Update();

	// �`��Ɋւ��邱�Ƃ�����
	void  Draw() const;

	//�X�R�A�\���p�摜�ύX����
	void ChangeImage(int _score ,int _digit[]);

	//�X�e�[�W���\���p�摜�ύX����
	void ChangeStageDigitImage(void);

	//�X�R�A���Z
	void AddScore(int addscore);

	//���C�t����
	void SubScore(void);

	//�Q�[���I�[�o�[����
	bool CheckOver(void);

	//���݂̃X�e�[�W���擾
	void SetStageNum(void);
};
