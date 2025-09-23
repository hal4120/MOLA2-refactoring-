#include "Application.h"

#include <DxLib.h>

#include"../Manager/FPS/FPS.h"
#include"../Manager/Input/InputManager.h"
#include"../Manager/Input/KeyManager.h"
#include"../Scene/SceneManager/SceneManager.h"
#include"../Manager/Score/Score.h"
#include"../Manager/Sound/SoundManager.h"

Application* Application::instance_ = nullptr;

// �R���X�g���N�^
Application::Application(void)
{
	gameEnd_ = false;
	isInitFail_ = false;
	isReleaseFail_ = false;
	fps_ = nullptr;
}

// �f�X�g���N�^
Application::~Application(void)
{
}

// ������
void Application::Init(void)
{
	// �A�v���P�[�V�����̏����ݒ�
	SetWindowText("MOLA2");

	// �E�B���h�E�֘A
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);	// �T�C�Y�ύX
	ChangeWindowMode(false);	// false = �t���X�N���[��

	// DxLib�̏�����
	isInitFail_ = false;
	if (DxLib_Init() == -1)
	{
		// ���������s
		isInitFail_ = true;
		return;
	}

	// �`����ʂ𗠂ɂ���
	SetDrawScreen(DX_SCREEN_BACK);

	// �L�[���䏉����
	SetUseDirectInputFlag(true);
	InputManager::CreateInstance();
	InputManager::GetInstance().Init();
	KEY::CreateIns();

	// �X�R�A�Ǘ��N���X�̐����ƃ��[�h
	Score::CreateInstance();

	// �����Ǘ��N���X�̐����ƃ��[�h
	Smng::CreateIns();
	// �����ȏꏊ�Ŏg���������[�h
	Smng::GetIns().Load(SOUND::SELECT);
	Smng::GetIns().Load(SOUND::BUTTON);

	// �V�[���Ǘ�������
	SceneManager::CreateInstance();
	SceneManager::GetInstance().Init();

	// FPS������
	fps_ = new FPS;
	fps_->Init();
}

// �Q�[�����[�v
void Application::Run(void)
{
	// �Q�[�����[�v
	while (ProcessMessage() == 0 && !gameEnd_)
	{
		// �t���[�����[�g�X�V
		// 1/60�b�o�߂��Ă��Ȃ��Ȃ�ă��[�v������
		if (!fps_->UpdateFrameRate()) continue;

		InputManager::GetInstance().Update();	// ���͐���X�V
		KEY::GetIns().Update();
		SceneManager::GetInstance().Update();	// �V�[���Ǘ��X�V
		fps_->CalcFrameRate();					// �t���[�����[�g�v�Z

		ClearDrawScreen();

		SceneManager::GetInstance().Draw();		// �V�[���Ǘ��`��
		fps_->DrawFrameRate();					// �t���[�����[�g�`��

		ScreenFlip();
	}
}

// ���
void Application::Release(void)
{
	// ���͐���폜
	InputManager::GetInstance().Destroy();
	KEY::DeleteIns();

	// �X�R�A�Ǘ��N���X�̃Z�[�u�ƍ폜
	Score::DeleteIns();

	// �����Ǘ��N���X�̍폜
	Smng::DeleteIns();
							   
	// �V�[���Ǘ�����E�폜	
	SceneManager::GetInstance().Release();
	SceneManager::DeleteInstance();

	// �t���[�����[�g���
	delete fps_;

	// DxLib�I��
	if (DxLib_End() == -1)
	{
		isReleaseFail_ = true;
	}
}
