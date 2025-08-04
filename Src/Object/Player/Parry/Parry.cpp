#include"Parry.h"

#include<DxLib.h>

#include"../Player.h"

#include"../../Enemy/EnemyBase.h"

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

	unit_.para_.radius = LOAD_SIZE_X;

	unit_.para_.colliShape = CollisionShape::CIRCLE;

	unit_.isInvici_ = false;
	unit_.aliveCollision_ = false;

}

void Parry::Init(void)
{
	counter_ = 0;
	countInterval_ = 0;

	mag_ = DEFAULT_MAG;
}

void Parry::Update(void)
{
	unit_.pos_ = player_;
	unit_.pos_.x += Player::LOAD_SIZE_X / 2;

	if (!unit_.isAlive_) { return; }

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

	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, 0.0f, LOAD_SIZE_Y / 2.0f, mag_, mag_, 0, img_[counter_], true);
}

void Parry::Release(void)
{
	for (auto& id : img_) { DeleteGraph(id); }
}

void Parry::OnCollision(UnitBase* other)
{
	if (!unit_.isAlive_) { return; }

	if (dynamic_cast<EnemyBase*>(other)) {
		if (!dynamic_cast<EnemyBase*>(other)->GetParry()) {
			mag_ += MAG_ONE_SIZE_UP;
			if (mag_ > MAX_MAG) { mag_ = MAX_MAG; }
			unit_.para_.radius = LOAD_SIZE_X * mag_;
		}
	}
}