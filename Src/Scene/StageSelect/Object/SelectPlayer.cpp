#include "SelectPlayer.h"

#include<DxLib.h>

#include"../../../Utility/Utility.h"

SelectPlayer::SelectPlayer():
	img_(),
	animeCounter_(0),
	animeInterval_(0),
	
	parryImg_(),
	isParry_(false),
	parryAnimeCounter_(0),
	parryAnimeInterval_(0),

	parryKey_()
{
}

SelectPlayer::~SelectPlayer()
{
}

void SelectPlayer::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Player/‚Ü‚Ú.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE_X, LOAD_SIZE_Y, img_);

	Utility::LoadArrayImg("Data/Image/Player/Parry/Parry.png",
		PARRY_ANIME_NUM, PARRY_ANIME_NUM, 1,
		PARRY_LOAD_SIZE_X, PARRY_LOAD_SIZE_Y, parryImg_);
}

void SelectPlayer::Init(void)
{
	animeCounter_ = 0;
	animeInterval_ = 0;

	parryAnimeCounter_ = 0;
	parryAnimeInterval_ = 0;
}

void SelectPlayer::Update(void)
{
	Input();


	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= ANIME_NUM) {
			animeCounter_ = 0;
		}
	}

	if (isParry_) {
		if (++parryAnimeInterval_ >= PARRY_ANIME_INTERVAL) {
			parryAnimeInterval_ = 0;
			if (++parryAnimeCounter_ >= PARRY_ANIME_NUM) {
				parryAnimeCounter_ = 0;
				isParry_ = false;
			}
		}
	}
	else {
		if (parryKey_.down) { isParry_ = true; }
	}
}

void SelectPlayer::Draw(void)
{
	DrawRotaGraph(POS_X, POS_Y, DRAW_SCALE, 0, img_[animeCounter_], true);

	if (isParry_) { DrawRotaGraph3(POS_X + SIZE_X / 2, POS_Y, 0, PARRY_LOAD_SIZE_Y / 2, PARRY_DRAW_SCALE, PARRY_DRAW_SCALE, 0, parryImg_[parryAnimeCounter_], true); }

}

void SelectPlayer::Release(void)
{
	for (auto& id : img_) { DeleteGraph(id); }
	for (auto& id : parryImg_) { DeleteGraph(id); }
}

bool SelectPlayer::Parry(void)
{
	if (!isParry_) { return false; }

	if (parryAnimeCounter_ > PARRY_ANIME_NUM / 2) { return true; }

	return false;
}

void SelectPlayer::Input(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);

	parryKey_.prev = parryKey_.now;
	parryKey_.now = (
		(CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_RETURN) == 0) &&
		((input & PAD_INPUT_B) == 0) &&
		((input & PAD_INPUT_A) == 0)
		) ? false : true;
	parryKey_.down = (!parryKey_.prev && parryKey_.now);
	parryKey_.up = (parryKey_.prev && !parryKey_.now);
}
