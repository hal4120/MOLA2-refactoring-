#include"Parry.h"

#include<DxLib.h>

#include"../Player.h"

Parry::Parry(const Vector2& playerPos):
	img_(),
	counter_(0),
	countInterval_(0),
	player_(playerPos)
{
}

Parry::~Parry()
{
}

void Parry::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Player/Parry/Parry.png",
		ANIM_NUM_ALL, ANIM_NUM_X, ANIM_NUM_Y,
		LOAD_SIZE_X, LOAD_SIZE_Y, img_);

	unit_.para_.radius_ = LOAD_SIZE_X / 2;
}

void Parry::Init(void)
{
	counter_ = 0;
	countInterval_ = 0;

}

void Parry::Update(void)
{
	if (!unit_.isAlive_) { return; }

	unit_.pos_ = player_;
	unit_.pos_.x += Player::LOAD_SIZE_X / 2;

	if (++countInterval_ >= COUNT_SPEED) {
		countInterval_ = 0;
		if (++counter_ >= ANIM_NUM_ALL) {
			counter_ = 0;
			unit_.isAlive_ = false;
		}
	}
}

void Parry::Draw(void)
{
	if (!unit_.isAlive_) { return; }

	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, 0.0f, unit_.para_.radius_, 1, 1, 0, img_[counter_], true);
}

void Parry::Release(void)
{
	for (auto& id : img_) { DeleteGraph(id); }
}