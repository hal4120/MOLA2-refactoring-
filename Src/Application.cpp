#include<DxLib.h>
#include<time.h>
#include"Application.h"
#include"Manager/SceneManager.h"

Application* Application::instance = nullptr;

Application::Application()
{
	fps = nullptr;
	errorInfo = false;
}

Application::~Application()
{

}

void Application::SystemInit(void)
{
	//�V�X�e������
	SetWindowText("MOLA2");								//�Q�[���E�B���h�E�̃^�C�g��
	SetGraphMode(SCREEN_SIZE_WID, SCREEN_SIZE_HIG, 32);	//�Q�[���E�B���h�E�̃T�C�Y�ƐF���[�h��ݒ�
	ChangeWindowMode(true);								//�E�B���h�E�̕\�����@�ifalse = �t���X�N���[���j

	errorInfo = false;
	if (DxLib_Init() == -1) {
		errorInfo = true;
		return;				//�I��
	}
	//�摜�E�����ǂݍ���
	if (Load() == false) {
		errorInfo = true;
		return;
	}

	//�����̏�����
	SRand((unsigned int)time(NULL));

	//FPS
	fps = new FPS;
	if (fps == nullptr)return;
	fps->Init();

	//�C���X�^���X�̍쐬
	SceneManager::CreateInstance();

	SetDrawScreen(DX_SCREEN_BACK);

	return;
}

void Application::Run(void)
{
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		if (!fps->UpdateFrameRate())continue;
		Update();
		Draw();
	}
}

void Application::Update(void)
{
	SceneManager::GetInstance().Update();
}

void Application::Draw(void)
{
	ClearDrawScreen();

	fps->CalcFrameRate();

	SceneManager::GetInstance().Draw();

	fps->DrawFrameRate();

	ScreenFlip();
}

void Application::Release(void)
{
	SceneManager::GetInstance().Release();
	SceneManager::DeleteInstance();

	if (DxLib_End() == -1) {
		errorInfo = true;
		return;
	}

}

bool Application::IsError(void) { return errorInfo; }

Vector2 Application::Round(Vector2F val)
{
	Vector2 ret;
	ret.x = static_cast<int>(Round(val.x));
	ret.y = static_cast<int>(Round(val.y));
	return ret;
}


//�摜�Ɖ����̓ǂݍ���
bool Application::Load(void)
{
	selectSound = LoadSoundMem("Data/sound/select.mp3");
	if (selectSound == -1)return false;
	button = LoadSoundMem("Data/sound/button.mp3");
	if (button == -1)return false;
	clearsound = LoadSoundMem("Data/sound/ClearBGM.mp3");
	if (clearsound == -1)return false;

	pauseimage[0] = LoadGraph("Data/image/PAUSE.png");
	pauseimage[1] = LoadGraph("Data/image/PauseSystemEnd.png");
	pauseimage[2] = LoadGraph("Data/image/PauseGame.png");
	pauseimage[3] = LoadGraph("Data/image/PauseTitle.png");
	pauseimage[4] = LoadGraph("Data/image/PauseSelect.png");
	for (int ii = 0; ii < 5; ii++) {
		if (pauseimage[ii] == -1)return false;
	}
}
