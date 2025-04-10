#include<DxLib.h>
#include"SceneManager.h"
#include"../Fader/Fader.h"
#include"../Scene/TitleScene.h"
#include"../Scene/Score.h"
//#include"GameScene.h"
//#include"GameOverScene.h"

SceneManager* SceneManager::instance = nullptr;

SceneManager::SceneManager()
{
	scene_ID = waitScene = E_SCENE_NON;

	fader = nullptr;
	
	titleInst = nullptr;
	scoreInst = nullptr;
	gameInst = nullptr;
	gameover = nullptr;
}

SceneManager::~SceneManager()
{
}


bool SceneManager::SystemInit(void)
{

	fader = new Fader();
	if (fader == nullptr)return false;

	SetTransColor(0xff, 0x00, 0xff);

	fader->SystemInit();

	ChangeScene(E_SCENE_TITLE);

	sceneChangeFlg = false;
	
	scene_ID = E_SCENE_TITLE;

	return true;
}

void SceneManager::Update(void)
{
	fader->Update();

	if (sceneChangeFlg) {
		if (fader->IsEnd() && waitScene != E_SCENE_NON) {
			ChangeScene(waitScene);
			waitScene = E_SCENE_NON;
			fader->SetFade(E_STAT_FADE_IN);
		}
		else if (fader->IsEnd() && waitScene == E_SCENE_NON) {
			sceneChangeFlg = false;
		}
	}
	else {
		E_SCENE_ID nextSceneID = scene_ID;

		switch (scene_ID)
		{
		case E_SCENE_TITLE:
			titleInst->Update();
			nextSceneID = titleInst->GetNextSceneID();
			break;
		case E_SCENE_SCORE:
			scoreInst->Update();
			nextSceneID = scoreInst->GetNextSceneID();
			break;
		case E_SCENE_MODESELECT:
			break;
		case E_SCENE_GAME:
			break;
		case E_SCENE_GAMEOVER:
			break;
		case E_SCENE_GAMECLEAR:
			break;
		case E_SCENE_ID_MAX:
			break;
		default:
			break;
		}

		if (scene_ID != nextSceneID) {
			sceneChangeFlg = true;
			waitScene = nextSceneID;
			fader->SetFade(E_STAT_FADE_OUT);
		}
	}
}
void SceneManager::Draw(void)
{
	switch (scene_ID)
	{
	case E_SCENE_TITLE:
		titleInst->Draw();
		break;
	case E_SCENE_SCORE:
		scoreInst->Draw();
		break;
	case E_SCENE_MODESELECT:
		break;
	case E_SCENE_GAME:
		break;
	case E_SCENE_GAMEOVER:
		break;
	case E_SCENE_GAMECLEAR:
		break;
	case E_SCENE_ID_MAX:
		break;
	default:
		break;
	}
	fader->Draw();
}


bool SceneManager::Release(void)
{
	if (fader->Release() == false)return false;

	ReleaseScene(E_SCENE_TITLE);
	ReleaseScene(E_SCENE_SCORE);
	ReleaseScene(E_SCENE_GAME);
	ReleaseScene(E_SCENE_GAMEOVER);

	delete fader;
	fader = nullptr;

	return true;
}

bool SceneManager::ChangeScene(E_SCENE_ID id) {

	ReleaseScene(scene_ID);

	scene_ID = id;

	switch (scene_ID)
	{
	case E_SCENE_TITLE:
		if (titleInst == nullptr) {
			titleInst = new TitleScene();
			if (titleInst == nullptr)return false;
			titleInst->SystemInit();
			titleInst->GameInit();
		}
		break;
	case E_SCENE_SCORE:
		if (scoreInst == nullptr) {
			scoreInst = new Score();
			if (scoreInst == nullptr)return false;
			scoreInst->SystemInit();
			scoreInst->GameInit();
		}
		break;
	case E_SCENE_MODESELECT:
		break;
	case E_SCENE_GAME:
		break;
	case E_SCENE_GAMEOVER:
		break;
	case E_SCENE_GAMECLEAR:
		break;
	case E_SCENE_ID_MAX:
		break;
	default:
		break;
	}


	return true;
}

void SceneManager::ReleaseScene(E_SCENE_ID id)
{
	switch (id)
	{
	case E_SCENE_TITLE:
		if (titleInst != nullptr) {
			titleInst->Release();
			delete titleInst;
			titleInst = nullptr;
		}
		break;
	case E_SCENE_SCORE:
		if (scoreInst != nullptr) {
			scoreInst->Release();
			delete scoreInst;
			scoreInst = nullptr;
		}
		break;
	case E_SCENE_MODESELECT:
		break;
	case E_SCENE_GAME:
		break;
	case E_SCENE_GAMEOVER:
		break;
	case E_SCENE_GAMECLEAR:
		break;
	case E_SCENE_ID_MAX:
		break;
	default:
		break;
	}
}
