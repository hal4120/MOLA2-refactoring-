#include "HardSharkLaser.h"

#include"../../../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../../../Manager/Sound/SoundManager.h"

#include"../../SharkHard.h"

#include"../../../../Player/Parry/Parry.h"

HardSharkLaser::HardSharkLaser(const Vector2& bossPos):
	img_(),
	state_(STATE::NON),
	counter_(0),
	countInterval_(0),
	boss_(bossPos)
{
}

HardSharkLaser::~HardSharkLaser()
{
}

void HardSharkLaser::Load(void)
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
	unit_.para_.size.y = SIZE_Y * 2.4f;

	unit_.para_.center.x = -(SIZE_X / 2.0f);

	Smng::GetIns().Load(SOUND::BOSS_LASER);
	Smng::GetIns().Load(SOUND::BOSS_LASER_CHARGE);
}

void HardSharkLaser::Init(void)
{
	counter_ = 0;
	countInterval_ = 0;

	state_ = NON;
}

void HardSharkLaser::Update(void)
{
	if (state_ == STATE::NON) {
		unit_.isAlive_ = false;
		Smng::GetIns().Stop(SOUND::BOSS_LASER_CHARGE);
		Smng::GetIns().Stop(SOUND::BOSS_LASER);
		return; 
	}

	unit_.pos_ = boss_;
	unit_.pos_.x -= SharkHard::SIZE_X / 2;

	if (++countInterval_ >= ANIM_SPEED) {
		countInterval_ = 0;
		if (++counter_ >= ((state_ == STATE::ACTIVE) ? ACTIVE_TIME : img_[state_].size())) {
			counter_ = 0;
			state_ = (STATE)(state_ + 1);
			if (state_ >= STATE::MAX) { state_ = STATE::NON; }
		}
	}

	if (state_ == STATE::CHARGE) { Smng::GetIns().Play(SOUND::BOSS_LASER_CHARGE, false, 200, true); }
	else { Smng::GetIns().Stop(SOUND::BOSS_LASER_CHARGE); }

	if (state_ == STATE::ACTIVE) {
		unit_.isAlive_ = true;
		Smng::GetIns().Play(SOUND::BOSS_LASER, false, 150, true);
	} else {
		unit_.isAlive_ = false;
		Smng::GetIns().Stop(SOUND::BOSS_LASER);
	}
}

void HardSharkLaser::Draw(void)
{
	if (state_ == STATE::NON) { return; }

	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, SIZE_X, SIZE_Y / 2.0f, 1, 4, 0, img_[state_][counter_ % img_[state_].size()], true);
}

void HardSharkLaser::Release(void)
{
	Smng::GetIns().Delete(SOUND::BOSS_LASER);
	Smng::GetIns().Delete(SOUND::BOSS_LASER_CHARGE);

	for (auto& ids : img_) {
		for (auto& id : ids) { DeleteGraph(id); }
	}
}

void HardSharkLaser::OnCollision(UnitBase* other)
{
	if (!other->GetUnit().isAlive_ || other->GetUnit().inviciCounter_ > 0) { return; }

	if (dynamic_cast<Parry*>(other)) { return; }

	BlastEffectManager::On(other->GetUnit().pos_);
}