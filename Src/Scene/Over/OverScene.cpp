#include "OverScene.h"

#include<DxLib.h>

#include"../../Utility/Utility.h"
#include"../../Application/Application.h"
#include"../SceneManager/SceneManager.h"

#include"../../Manager/Input/InputManager.h"

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
}

void OverScene::Init(void)
{

}

void OverScene::Update(void)
{
	if (InputManager::GetInstance().IsTrgDown(KEY_INPUT_SPACE)) {
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
	DeleteGraph(img_);
}

