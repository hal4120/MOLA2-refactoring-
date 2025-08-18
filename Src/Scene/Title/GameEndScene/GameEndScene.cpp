#include "GameEndScene.h"

#include<DxLib.h>

#include"../../../Utility/Utility.h"
#include"../../../Application/Application.h"
#include"../../SceneManager/SceneManager.h"

GameEndScene::GameEndScene():
	windowImg_(),
	nowSelect_(),
	upKey_(),
	downKey_(),
	deciKey_()
{
}

GameEndScene::~GameEndScene()
{
}


void GameEndScene::Load(void)
{
	Utility::LoadImg(windowImg_[(int)SELECT::YES], "Data/Image/Title/GameEnd/Yes.png");
	Utility::LoadImg(windowImg_[(int)SELECT::NO], "Data/Image/Title/GameEnd/No.png");
}

void GameEndScene::Init(void)
{
	nowSelect_ = SELECT::NO;

	deciKey_ = {};
	deciKey_.prev = true;
	deciKey_.now = true;
}

void GameEndScene::Update(void)
{
	Input();

	switch (nowSelect_)
	{
	case GameEndScene::SELECT::YES:
		if (downKey_.down) { nowSelect_ = SELECT::NO; }
		break;
	case GameEndScene::SELECT::NO:
		if (upKey_.down) { nowSelect_ = SELECT::YES; }
		break;
	}

	if (deciKey_.down) {
		switch (nowSelect_)
		{
		case GameEndScene::SELECT::YES:
			Application::GetInstance().GameEnd();
			break;
		case GameEndScene::SELECT::NO:
			SceneManager::GetInstance().PopScene();
			break;
		}
	}
}

void GameEndScene::Draw(void)
{
	using app = Application;
	int x = app::SCREEN_SIZE_X / 2;
	int y = app::SCREEN_SIZE_Y / 2;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, x * 2, y * 2, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph(x, y, 1, 0, windowImg_[(int)nowSelect_], true);
}

void GameEndScene::Release(void)
{
	for (auto& id : windowImg_) { DeleteGraph(id); }
}

void GameEndScene::Input(void)
{
	upKey_.prev = upKey_.now;
	upKey_.now = (
		(CheckHitKey(KEY_INPUT_UP) == 0) &&
		(CheckHitKey(KEY_INPUT_W) == 0)
		) ? false : true;
	upKey_.down = (!upKey_.prev && upKey_.now);
	upKey_.up = (upKey_.prev && !upKey_.now);


	downKey_.prev = downKey_.now;
	downKey_.now = (
		(CheckHitKey(KEY_INPUT_DOWN) == 0) &&
		(CheckHitKey(KEY_INPUT_S) == 0)
		) ? false : true;
	downKey_.down = (!downKey_.prev && downKey_.now);
	downKey_.up = (downKey_.prev && !downKey_.now);


	deciKey_.prev = deciKey_.now;
	deciKey_.now = (
		(CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_RETURN) == 0)
		) ? false : true;
	deciKey_.down = (!deciKey_.prev && deciKey_.now);
	deciKey_.up = (deciKey_.prev && !deciKey_.now);
}
