#include "ClearPlayer.h"

#include"../../../Utility/Utility.h"

ClearPlayer::ClearPlayer():
	img_(),
	animeCounter_(0),
	animeInterval_(0),
	angle_(0.0f)
{
}

ClearPlayer::~ClearPlayer()
{
}

void ClearPlayer::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Player/‚Ü‚Ú.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE_X, LOAD_SIZE_Y, img_);
}

void ClearPlayer::Init(void)
{
	animeCounter_ = 0;
	animeInterval_ = 0;

	angle_ = 0.0f;
}

void ClearPlayer::Update(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= ANIME_NUM) {
			animeCounter_ = 0;
		}
	}
	angle_ += 0.05f;
}

void ClearPlayer::Draw(void)
{
	for (int i = 0; i < PLAYER_NUM; i++) {
		DrawRotaGraph(POS_X[i], POS_Y, 5, DEFAULT_ANGLE[i] + (Utility::Deg2RadF(sinf(angle_) * 15.0f) * (i * 2 - 1)), img_[animeCounter_], true, i);
	}
}

void ClearPlayer::Release(void)
{
	for (auto& id : img_) { DeleteGraph(id); }
}

