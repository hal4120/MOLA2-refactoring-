#include"BlastEffect.h"

#include<DxLib.h>

BlastEffect::BlastEffect():
	isAlive_(),
	animeCounter_(),
	animeInterval_()
{
}

BlastEffect::~BlastEffect()
{
}

void BlastEffect::Load(std::vector<int> image)
{
	this->image_ = image;
}

void BlastEffect::On(Vector2 pos)
{
	this->pos_ = pos;
	this->isAlive_ = true;
	this->animeCounter_ = 0;
	this->animeInterval_ = 0;
}

void BlastEffect::Update(void)
{
	if (++animeInterval_ > ANIME_SPEED) {
		animeInterval_ = 0;
		if (++animeCounter_ >= image_.size()) {
			isAlive_ = false;
			animeCounter_ = 0;
		}
	}
}

void BlastEffect::Draw(void)
{
	DrawRotaGraphF(pos_.x, pos_.y, 0.5, 0, image_[animeCounter_], true);
}

void BlastEffect::Release(void)
{
}
