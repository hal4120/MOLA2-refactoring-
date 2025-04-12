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


	pause = end = false;
	nowEscape = prevEscaoe = 0;
	nowSpaceKey = prevSpaceKey = 0;

	pausegame.x = SCREEN_SIZE_WID / 4;
	pausegame.y = SCREEN_SIZE_HIG / 7 * 3;
	pausetitle.x = SCREEN_SIZE_WID / 4 * 3;
	pausetitle.y = SCREEN_SIZE_HIG / 7 * 3;

	return;
}

void Application::Run(void)
{
	while (ProcessMessage() == 0 && end == false) {
		if (!fps->UpdateFrameRate())continue;
		Update();
		Draw();
	}
}

void Application::Update(void)
{
	prevEscaoe = nowEscape;
	nowEscape = CheckHitKey(KEY_INPUT_ESCAPE);

	if (pause) {
		if (CheckHitKey(KEY_INPUT_Q) == 1 && nowEscape == 1)end = true;

		prevSpaceKey = nowSpaceKey;
		nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

		if (select) {

			if (CheckHitKey(KEY_INPUT_D) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) == 0)) {
				PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
				select = false;
			}
			if (nowSpaceKey == 0 && prevSpaceKey == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) == 0)) {
				PlaySoundMem(button, DX_PLAYTYPE_BACK, true);
				pause = false;
			}
		}
		else {

			if (CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_LEFT) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) == 0)) {
				PlaySoundMem(selectSound, DX_PLAYTYPE_BACK, true);
				select = true;
			}
			if (nowSpaceKey == 0 && prevSpaceKey == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) == 0)) {
				PlaySoundMem(button, DX_PLAYTYPE_BACK, true);
				SceneManager::GetInstance().ChangeTitle();
				pause = false;
			}
		}
		
	}
	else {
		if (prevEscaoe == 0 && nowEscape == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_8) == 0)) pause = true;

		SceneManager::GetInstance().Update();

	}
}

void Application::Draw(void)
{
	ClearDrawScreen();

	fps->CalcFrameRate();

	SceneManager::GetInstance().Draw();

	//ポーズ中の描画処理------------------------------------------------------------------------
	if (pause) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(200));
		DrawBox(0, 0, SCREEN_SIZE_WID, SCREEN_SIZE_HIG, RGB(50, 50, 50), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(SCREEN_SIZE_WID / 2, 50, 1, 0, pauseimage[0], true);
		DrawRotaGraph(SCREEN_SIZE_WID - 240, SCREEN_SIZE_HIG - 100, 1, 0, pauseimage[1], true);
		DrawRotaGraph(pausegame.x, pausegame.y, 1, 0, pauseimage[2], true);
		DrawRotaGraph(pausetitle.x, pausetitle.y, 1, 0, pauseimage[3], true);
		if (select) {
			DrawRotaGraph(pausegame.x, pausegame.y, 1, 0, pauseimage[4], true);
		}
		else {
			DrawRotaGraph(pausetitle.x, pausetitle.y, 1, 0, pauseimage[4], true);
		}
	}
	//-------------------------------------------------------------------------------------------

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
