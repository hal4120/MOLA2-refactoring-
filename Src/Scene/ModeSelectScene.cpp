#include<DxLib.h>
#include"ModeSelectScene.h"
#include"../Manager/SceneManager.h"
#include"../Application.h"


ModeSelect::ModeSelect()
{
}

ModeSelect::~ModeSelect()
{
}

bool ModeSelect::SystemInit(void)
{
	haikeiimage = LoadGraph("Data/image/GameModeSelect.png");
	if (haikeiimage == -1)return false;
	normalimage = LoadGraph("Data/image/NormalMode.png");
	if (normalimage == -1)return false;
	hardimage = LoadGraph("Data/image/HardMode.png");
	if (hardimage == -1)return false;
	nowselectimage = LoadGraph("Data/image/NowSelect.png");
	if(nowselectimage==-1)return false;
//	if (plInst.SystemInit() == -1)return false;
	parryhitsound = LoadSoundMem("Data/sound/K.O..mp3");

	return true;
}

void ModeSelect::GameInit(void)
{
	nowmode = MODE_ID::MODE_NON;
	normalpos.x = hardpos.x = Application::SCREEN_SIZE_WID / 2 - MODE_SELECT_SIZE_X / 2;
	normalpos.y = (Application::SCREEN_SIZE_HIG / 9) * 2;
	hardpos.y= (Application::SCREEN_SIZE_HIG / 6) * 4;
	
	normalflg = normalparry = hardflg = hardparry = false;

	nextSceneID = E_SCENE_ID::E_SCENE_MODESELECT;

//	plInst.GameInit();
}

void ModeSelect::Update(void)
{
/*	plInst.Update();
	Vector2 ppos = plInst.GetPlayerPos();
	if (ppos.y > normalpos.y - (Parry::SIZE_HIG / 2)&&
		ppos.y < normalpos.y + MODE_SELECT_SIZE_Y) {
		normalflg = true;
	}
	else { normalflg = false; }

	if (ppos.y > hardpos.y - (Parry::SIZE_HIG / 2) &&
		ppos.y < hardpos.y + MODE_SELECT_SIZE_Y) {
		hardflg = true;
	}
	else { hardflg = false; }

	if (normalflg) {
		if (plInst.GetParryFlg()) {
			normalparry = true;
			PlaySoundMem(parryhitsound, DX_PLAYTYPE_BACK);
		}
	}
	if (hardflg) {
		if (plInst.GetParryFlg()) {
			hardparry = true;
			PlaySoundMem(parryhitsound, DX_PLAYTYPE_BACK);
		}
	}
*/	
	if (normalparry) {
		normalflg = true;
		normalpos.x += PARRY_SPEED;
	}
	if (normalpos.x > Application::SCREEN_SIZE_WID) {
		normalparry = false;
		normalflg = false;
		nowmode = MODE_ID::MODE_NORMAL;
		nextSceneID = E_SCENE_GAME;
	}

	if (hardparry) {
		hardflg = true;
		hardpos.x += PARRY_SPEED;
	}
	if (hardpos.x > Application::SCREEN_SIZE_WID) {
		hardparry = false;
		hardparry = false;
		nowmode = MODE_ID::MODE_HARD;
		nextSceneID = E_SCENE_GAME;
	}
}

void ModeSelect::Draw(void)
{
	DrawGraph(0, 0, haikeiimage, true);
	if (normalflg) {
		DrawGraph(normalpos.x - 10, normalpos.y - 10, nowselectimage, true);
	}
	if (hardflg) {
		DrawGraph(hardpos.x - 10, hardpos.y - 10, nowselectimage, true);
	}
	DrawGraph(normalpos.x, normalpos.y, normalimage, true);
	DrawGraph(hardpos.x, hardpos.y, hardimage, true);
//	plInst.Draw();
}

bool ModeSelect::Release(void)
{
//	if (plInst.Release() == -1)return false;
	if (DeleteGraph(nowselectimage) == -1)return false;
	if (DeleteGraph(hardimage) == -1)return false;
	if (DeleteGraph(normalimage) == -1)return false;
	if (DeleteGraph(haikeiimage) == -1)return false;

	return true;
}
