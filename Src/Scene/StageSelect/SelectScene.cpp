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
}

void SelectScene::Init(void)
{
	nowBoss_ = BOSS_KINDS::SHARK;

}

void SelectScene::Update(void)
{
	SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
}

void SelectScene::Draw(void)
{

}

void SelectScene::Release(void)
{

}


void SelectScene::Input(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	upKey_.prev = upKey_.now;
	upKey_.now = (
		(CheckHitKey(KEY_INPUT_UP) == 0) &&
		(CheckHitKey(KEY_INPUT_W) == 0) &&
		((input & PAD_INPUT_UP) == 0)
		) ? false : true;
	upKey_.down = (!upKey_.prev && upKey_.now);
	upKey_.up = (upKey_.prev && !upKey_.now);


	downKey_.prev = downKey_.now;
	downKey_.now = (
		(CheckHitKey(KEY_INPUT_DOWN) == 0) &&
		(CheckHitKey(KEY_INPUT_S) == 0) &&
		((input & PAD_INPUT_DOWN) == 0)
		) ? false : true;
	downKey_.down = (!downKey_.prev && downKey_.now);
	downKey_.up = (downKey_.prev && !downKey_.now);


	deciKey_.prev = deciKey_.now;
	deciKey_.now = (
		(CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_RETURN) == 0) &&
		((input & PAD_INPUT_B) == 0) &&
		((input & PAD_INPUT_A) == 0)
		) ? false : true;
	deciKey_.down = (!deciKey_.prev && deciKey_.now);
	deciKey_.up = (deciKey_.prev && !deciKey_.now);
}