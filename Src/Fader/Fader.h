#pragma once

#include"../StDefineData.h"

class Fader
{
public:

	static constexpr float FADE_SPEED_ALPHA = 2;			//�t�F�[�h�̑���

	Fader(void);
	~Fader(void);

	bool SystemInit(void);			//�����������i�ŏ��̈��̂ݎ��s�j
	void GameInit(void);			//�Q�[���N���E�ĊJ���ɕK���Ăяo������
	void Update(void);				//�X�V����
	void Draw(void);				//�`�揈��
	bool Release(void);				//��������i�Ō�̈��̂ݎ��s�j

	//�Q�b�^�[�E�Z�b�^�[�֐�
	E_FADE_STAT_ID GetNowState(void) { return stat; }
	bool IsEnd(void) { return endFlg; }
	void SetFade(E_FADE_STAT_ID id);

private:

	E_FADE_STAT_ID stat;		//�X�e�[�^�X
	float alpha;				//�A���t�@�l�p�̕ϐ�
	bool endFlg;				//�t�F�[�h�����I���t���O�itrue = �����s�@/�@false = ���s���j

};