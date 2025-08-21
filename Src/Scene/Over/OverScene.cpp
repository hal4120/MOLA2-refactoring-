#include "OverScene.h"

#include<DxLib.h>

#include"../../Utility/Utility.h"
#include"../../Application/Application.h"
#include"../SceneManager/SceneManager.h"
#include"../../Manager/Sound/SoundManager.h"

OverScene::OverScene():
	img_(-1)
{
}

OverScene::~OverScene()
{
}

void OverScene::Load(void)
{
	Utility::LoadImg(img_, "Data/Image/Over/GameOver.png");
	Smng::GetIns().Load(SOUND::BGM_GAMEOVER);
}

void OverScene::Init(void)
{
	Smng::GetIns().Play(SOUND::BGM_GAMEOVER, true);
}

void OverScene::Update(void)
{
	if (

		(CheckHitKeyAll()) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_B) != 0) ||
		((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_A) != 0)

		) {
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
	}
}

void OverScene::Draw(void)
{
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	DrawExtendGraph(0, 0, xx, yy, img_, true);
}

void OverScene::Release(void)
{
	Smng::GetIns().Delete(SOUND::BGM_GAMEOVER);
	DeleteGraph(img_);
}

