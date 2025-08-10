#include "SharkLaser.h"

#include"../../../../../Manager/BlastEffect/BlastEffectManager.h"

#include"../../Shark.h"

SharkLaser::SharkLaser(const Vector2& bossPos):
	img_(),
	state_(STATE::NON),
	counter_(0),
	countInterval_(0),
	boss_(bossPos)
{
}

SharkLaser::~SharkLaser()
{
}

void SharkLaser::Load(void)
{
	for (int i = 0; i < STATE::MAX; i++) {
		for (int j = 1; j <= IMG_NUM[i]; j++) {
			std::string path = FILE_PATH[i] + std::to_string(j) + ".png";
			img_[i].emplace_back(Utility::LoadImg(path.c_str()));
		}
	}

	unit_.para_.colliShape = CollisionShape::RECTANGLE;
	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.para_.size.x = SIZE_X;
	unit_.para_.size.y = SIZE_Y;

	unit_.para_.center.x = -SIZE_X / 2.0f;
}

void SharkLaser::Init(void)
{
	counter_ = 0;
	countInterval_ = 0;

	state_ = NON;
}

void SharkLaser::Update(void)
{
	if (state_ == STATE::NON) { return; }

	unit_.pos_ = boss_;
	unit_.pos_.x -= Shark::SIZE_X / 2;

	if (++countInterval_ >= ANIM_SPEED) {
		countInterval_ = 0;
		if (++counter_ >= ((state_ == STATE::ACTIVE) ? ACTIVE_TIME : img_[state_].size())) {
			counter_ = 0;
			state_ = (STATE)(state_ + 1);
			if (state_ >= STATE::MAX) { state_ = STATE::NON; }
		}
	}

	if (state_ == STATE::ACTIVE) { unit_.isAlive_ = true; }
	else { unit_.isAlive_ = false; }
}

void SharkLaser::Draw(void)
{
	if (state_ == STATE::NON) { return; }

	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y,SIZE_X, SIZE_Y / 2.0f, 1, 1, 0, img_[state_][counter_ % img_[state_].size()], true);
}

void SharkLaser::Release(void)
{
	for (auto& ids : img_) {
		for (auto& id : ids) { DeleteGraph(id); }
	}
}

void SharkLaser::OnCollision(UnitBase* other)
{
}

