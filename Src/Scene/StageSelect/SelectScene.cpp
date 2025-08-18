#include "SelectScene.h"

#include<DxLib.h>

#include"../SceneManager/SceneManager.h"

BOSS_KINDS SelectScene::nowBoss_ = BOSS_KINDS::NON;

SelectScene::SelectScene()
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Load(void)
{
	nowBoss_ = BOSS_KINDS::SHARK;
	SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
}

void SelectScene::Init(void)
{

}

void SelectScene::Update(void)
{

}

void SelectScene::Draw(void)
{

}

void SelectScene::Release(void)
{

}