#include "TitleShark.h"

#include"../../../Utility/Utility.h"

TitleShark::TitleShark(): 
	animeCounter_(0),
    animeInterval_(0),
    laserCounter_(0),
    laserInterval_(0)
{
    for (int i = 0; i < ANIME_NUM; ++i) {
        img_[i] = 0;
    }

    // Initialize laserImg_ array
    for (int i = 0; i < LASER_ANIME_NUM; ++i) {
        laserImg_[i] = 0;
    }
}

TitleShark::~TitleShark()
{
}

void TitleShark::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Boss/Shark/Attack1.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE, LOAD_SIZE, img_);

	for (int i = 0; i < LASER_ANIME_NUM; i++) {
		std::string path = "Data/Image/Boss/Shark/Attack/Laser/Active/" + std::to_string(i + 1) + ".png";
		Utility::LoadImg(laserImg_[i], path.c_str());
	}
}

void TitleShark::Init(void)
{
	animeCounter_ = 0;
	animeInterval_ = 0;

	laserCounter_ = 0;
	laserInterval_ = 0;
}

void TitleShark::Update(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= ANIME_NUM) {
			animeCounter_ = 0;
		}
	}

	if (++laserInterval_ >= LASER_ANIME_INTERVAL) {
		laserInterval_ = 0;
		if (++laserCounter_ >= LASER_ANIME_NUM) {
			laserCounter_ = 0;
		}
	}
}

void TitleShark::Draw(void)
{
	DrawRotaGraph(POS_X, POS_Y, DRAW_SCALE, -Utility::Deg2RadF(10.0f), img_[animeCounter_], true,true);
	DrawRotaGraph3(LASER_POS_X, LASER_POS_Y, LASER_LOAD_SIZE_X, LASER_LOAD_SIZE_Y/2,
		LASER_DRAW_SCALE, LASER_DRAW_SCALE, -Utility::Deg2RadF(10.0f),
		laserImg_[laserCounter_], true);
}

void TitleShark::Release(void)
{
	for (auto& id : laserImg_) { DeleteGraph(id); }
	for (auto& id : img_) { DeleteGraph(id); }
}

