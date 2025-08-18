#include "TitlePlayer.h"

#include"../../../Utility/Utility.h"

TitlePlayer::TitlePlayer() :
	img_(),
	animeCounter_(0),
	animeInterval_(0),
	angle_(0.0f),
	hukidasi_(0)
{
}

TitlePlayer::~TitlePlayer()
{

}


void TitlePlayer::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Player/‚Ü‚Ú.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE_X, LOAD_SIZE_Y, img_);
	Utility::LoadImg(hukidasi_, "Data/Image/Title/‚«o‚µ.png");
}

void TitlePlayer::Init(void)
{
	animeCounter_ = 0;
	animeInterval_ = 0;
	angle_ = 0.0f;
}

void TitlePlayer::Update(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= ANIME_NUM) {
			animeCounter_ = 0;
		}
	}
	angle_ += 0.05f;
}

void TitlePlayer::Draw(void)
{
	DrawRotaGraph(POS_X, POS_Y, DRAW_SCALE, -Utility::Deg2RadF(15.0f) + Utility::Deg2RadF(sinf(angle_) * 10.0f), img_[animeCounter_], true);

	DrawRotaGraph3(POS_X + (SIZE_X / 2), POS_Y, 0, HUKIDASI_LOAD_SIZE_Y / 2,
		HUKIDASI_DRAW_SCALE_X, HUKIDASI_DRAW_SCALE_Y, 0, hukidasi_, true);
}

void TitlePlayer::Release(void)
{
	DeleteGraph(hukidasi_);
	for (auto& id : img_) { DeleteGraph(id); }
}

