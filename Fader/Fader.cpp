#include<DxLib.h>
#include"Fader.h"
#include"../Application.h"

Fader::Fader(void)
{

}

Fader::~Fader(void)
{

}

//�����������i�ŏ��̈��̂ݎ��s�j
bool Fader::SystemInit(void)
{
	GameInit();

	return true;
}

//�Q�[���N���E�ĊJ���ɕK���Ăяo������
void Fader::GameInit(void)
{
	stat = E_STAT_FADE_NON;
	alpha = 0.0f;
	endFlg = true;
}

//�X�V����
void Fader::Update(void)
{
	if (endFlg)return;

	switch (stat){
	case E_STAT_FADE_NON:
		return;
	case E_STAT_FADE_OUT:
		alpha += FADE_SPEED_ALPHA;				//�A���t�@�l�����Z���ď����������Ȃ��i�������s�����Ɂj����
		if (alpha > 255.0f) {
			//�t�F�[�h�A�E�g�I��
			alpha = 255.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	case E_STAT_FADE_IN:
		alpha -= FADE_SPEED_ALPHA;				//�A���t�@�l�����Y���ď���������l�Ɂi�����������Ɂj����
		if (alpha < 0) {
			//�t�F�[�h�C���I��
			alpha = 0.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	default:
		return;
	}
}

//�`�揈��
void Fader::Draw(void)
{
	switch (stat)
	{
	case E_STAT_FADE_NON:
		return;
	case E_STAT_FADE_OUT:
	case E_STAT_FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);		//�A���t�@�l���u�����h���郂�[�h�ɐݒ肷��
		DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, GetColor(0,0,0),true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//�u�����h�s���ʏ�̃��[�h�ɖ߂�
		break;
	default:
		return;
	}
}

//��������i�Ō�̈��̂ݎ��s�j
bool Fader::Release(void)
{
	return true;
}

//�t�F�[�h�A�E�g�E�t�F�[�h�C�����J�n����Ƃ��ɌĂяo��
void Fader::SetFade(E_FADE_STAT_ID id)
{
	
	stat = id;
	if (stat != E_STAT_FADE_NON) {
		endFlg = false;
	}
}
