#include"BossBase.h"

#include<DxLib.h>

BossBase::BossBase(const Vector2& playerPos) :
	playerPos_(playerPos),
	state_(0),
	stateFuncPtr(),
	SCALE(1.0f),
	reverse_(false),
	motion_(),
	animCounter_(),
	animInterval_(),
	animLoop_(),
	angle_(0.0f)
{
	unit_.para_.colliType = CollisionType::ENEMY;
}

BossBase::~BossBase()
{
}


void BossBase::Update(void)
{
	AttackUpdate();

	Invi();
	(this->*stateFuncPtr[state_])();
	Animation();
}

void BossBase::Draw(void)
{
	AttackDraw();

	if (!unit_.isAlive_) { return; }
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, SCALE, angle_, imgs_.at((int)motion_).at(animCounter_), true, reverse_);
}

void BossBase::Release(void)
{
	AttackRelease();

	for (auto& imgs : imgs_) {
		for (auto& img : imgs) { DeleteGraph(img); }
	}
}

void BossBase::ChangeMotion(int motion, bool loop)
{
	motion_ = motion;
	animLoop_ = loop;
	animCounter_ = 0;
	animInterval_ = 0;
}

void BossBase::Animation(void)
{
	if (++animInterval_ >= ANIM_INTERVAL) {
		animInterval_ = 0;
		if (++animCounter_ >= imgs_[motion_].size()) {
			if (animLoop_) {
				animCounter_ = 0;
			}
			else {
				ChangeMotion(0);
			}
		}
	}
}