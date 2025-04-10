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
	//システム処理
	SetWindowText("MOLA2");								//ゲームウィンドウのタイトル
	SetGraphMode(SCREEN_SIZE_WID, SCREEN_SIZE_HIG, 32);	//ゲームウィンドウのサイズと色モードを設定
	ChangeWindowMode(true);								//ウィンドウの表示方法（false = フルスクリーン）

	errorInfo = false;
	if (DxLib_Init() == -1) {
		errorInfo = true;
		return;				//終了
	}
	//画像・音声読み込み
	if (Load() == false) {
		errorInfo = true;
		return;
	}

	//乱数の初期化
	SRand((unsigned int)time(NULL));

	//FPS
	fps = new FPS;
	if (fps == nullptr)return;
	fps->Init();

	//インスタンスの作成
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


//画像と音声の読み込み
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
