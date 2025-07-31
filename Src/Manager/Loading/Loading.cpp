#include "Loading.h"

#include <DxLib.h>

#include"../../Application/Application.h"

Loading* Loading::instance_ = nullptr;

// �R���X�g���N�^
Loading::Loading()
	: handle_(-1)
	, posX_(0)
	, posY_(0)
	, isLoading_(false)
	, loadTimer_(0)
{}

// �f�X�g���N�^
Loading::~Loading()
{}

// ������
void Loading::Init(void)
{
	loadTimer_ = 0;
	isLoading_ = false;
	posX_ = Application::SCREEN_SIZE_X / 2;
	posY_ = Application::SCREEN_SIZE_Y / 2;
}

// �ǂݍ���
void Loading::Load(void)
{
	handle_ = LoadGraph("Data/Image/Axe.png");
}

// �X�V
void Loading::Update(void)
{
	loadTimer_++;

	// �Ǎ����̂��̂��Ȃ��Ȃ����� or �ŒჍ�[�h���Ԍo��
	if (GetASyncLoadNum() == 0 && loadTimer_ >= MIN_LOAD_TIME)
	{
		// ���[�h�I��
		Init();
	}
	// �ǂݍ��ݒ�
	else
	{
		// ���[�h��ʂ𓮍삳����Ȃ炱���ɋL�q
	}
}

// �`��
void Loading::Draw(void)
{
	DrawRotaGraph(
		posX_, posY_,	// ���W
		1.0f,			// �g��l
		0.0f,			// ��]�l
		handle_,		// �n���h��
		true			// ���߃t���O
	);
}

// ���
void Loading::Release(void)
{
	DeleteGraph(handle_);
}

// �񓯊��ǂݍ��݂ɐ؂�ւ���
void Loading::StartAsyncLoad(void)
{
	isLoading_ = true;
	// �񓯊��ǂݍ��݊J�n
	SetUseASyncLoadFlag(true);
}

// �����ǂݍ��݂ɐ؂�ւ���
void Loading::EndAsyncLoad(void)
{
	// �񓯊��ǂݍ��ݏI��
	SetUseASyncLoadFlag(false);
}
