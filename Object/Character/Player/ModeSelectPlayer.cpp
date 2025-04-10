#include<DxLib.h>
#include "ModeSelectPlayer.h"
#include"../Manager/SceneManager.h"

ModeSelectPlayer::ModeSelectPlayer()
{
}

ModeSelectPlayer::~ModeSelectPlayer()
{
}

bool ModeSelectPlayer::SystemInit(void)
{
	image = LoadGraph("image/‚Ü‚Ú.png");
	if (image == -1) {
		return false;
	}
	parry.SystemInit();
	parrysound = LoadSoundMem("sound/ParrySound.mp3");


	return true;
}

void ModeSelectPlayer::GameInit(void)
{
	pos.x = ((SceneManager::SCREEN_SIZE_WID / 2 - ModeSelect::MODE_SELECT_SIZE_X / 2) - SIZE_X * 2) + 5;
	pos.y = (SceneManager::SCREEN_SIZE_HIG - SIZE_Y) / 2;
	parry.GameInit();
}

void ModeSelectPlayer::Update(void)
{
	if (CheckHitKey(KEY_INPUT_W) == 1 || CheckHitKey(KEY_INPUT_UP) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) == 0)) {
		pos.y -= MOVE_SPEED;
	}
	if (pos.y < 0) {
		pos.y = 0;
	}
	if (CheckHitKey(KEY_INPUT_S) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) == 0)) {
		pos.y += MOVE_SPEED;
	}
	if (pos.y > (SceneManager::SCREEN_SIZE_HIG - SIZE_Y)) {
		pos.y = (SceneManager::SCREEN_SIZE_HIG - SIZE_Y);
	}
	

	parry.Update();
	prevparrykey = nowparrykey;
	nowparrykey = CheckHitKey(KEY_INPUT_SPACE);
	if ((prevparrykey == 0 && nowparrykey == 1 && GetParryFlg() == false) || (!((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) == 0)) && GetParryFlg() == false) {
		if (CheckSoundMem(parrysound) == false) {
			PlaySoundMem(parrysound, DX_PLAYTYPE_BACK);
		}
		parry.SetParryFlg(true); 
	}
	if (parry.GetParryFlg()) {
		Vector2 prpos;
		prpos.x = pos.x + SIZE_X;
		prpos.y = pos.y + SIZE_Y / 2 - Parry::SIZE_HIG / 2;
		parry.SetParryPos(prpos);
	}
}

void ModeSelectPlayer::Draw(void)
{
	DrawGraph(pos.x, pos.y, image,true);
	parry.Draw();
}

bool ModeSelectPlayer::Release(void)
{
	parry.Release();
	if(DeleteGraph(image)==-1)return false;

	return true;
}


