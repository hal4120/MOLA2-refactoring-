#include"TitleScene.h"

#include<DxLib.h>

#include"../SceneManager/SceneManager.h"


TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Load(void)
{
}
void TitleScene::Init(void)
{
}
void TitleScene::Update(void)
{
	if (CheckHitKey(KEY_INPUT_SPACE) == 1) {
		SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
	}
}
void TitleScene::Draw(void)
{
	DrawString(0, 0, "タイトルシーン", 0xffffff);
}
void TitleScene::Release(void)
{
}