#include"PlayerLaser.h"

#include<DxLib.h>

#include"../../../Manager/Sound/SoundManager.h"

#include"../Player.h"

PlayerLaser::PlayerLaser(const Vector2& playerPos):
	img_(),
	state_(STATE::NON),
	counter_(0),
	countInterval_(0),
	player_(playerPos)
{
}

PlayerLaser::~PlayerLaser()
{
}

void PlayerLaser::Load(void)
{
	for (int i = 0; i < STATE::MAX;i++) {
		for (int j = 1; j <= IMG_NUM[i]; j++) {
			std::string path = FILE_PATH[i] + std::to_string(j) + ".png";
			img_[i].emplace_back(Utility::LoadImg(path.c_str()));
		}
	}

	unit_.para_.colliShape = CollisionShape::RECTANGLE;
	unit_.para_.colliType = CollisionType::ALLY;

	unit_.para_.size.x = SIZE_X;
	unit_.para_.size.y = SIZE_Y;

	unit_.para_.center.x = SIZE_X / 2.0f;

	Smng::GetIns().Load(SOUND::PLAYER_LASER);
	Smng::GetIns().Load(SOUND::PLAYER_LASER_CHARGE);
}

void PlayerLaser::Init(void)
{
	counter_ = 0;
	countInterval_ = 0;

	state_ = NON;
}

void PlayerLaser::Update(void)
{
	if (state_ == STATE::NON) {
		unit_.isAlive_ = false;
		Smng::GetIns().Stop(SOUND::PLAYER_LASER_CHARGE);
		Smng::GetIns().Stop(SOUND::PLAYER_LASER);
		return;
	}

	unit_.pos_ = player_;
	unit_.pos_.x += Player::LOAD_SIZE_X / 2;

	if (++countInterval_ >= ANIM_SPEED) {
		countInterval_ = 0;
		if (++counter_ >= ((state_ == STATE::ACTIVE) ? ACTIVE_TIME : img_[state_].size())) {
			counter_ = 0;
			state_ = (STATE)(state_ + 1);
			if (state_ >= STATE::MAX) { state_ = STATE::NON; }
		}
	}

	if (state_ == STATE::CHARGE) { Smng::GetIns().Play(SOUND::PLAYER_LASER_CHARGE, false, 255, true); }
	else { Smng::GetIns().Stop(SOUND::PLAYER_LASER_CHARGE); }

	if (state_ == STATE::ACTIVE) {
		unit_.isAlive_ = true;
		Smng::GetIns().Play(SOUND::PLAYER_LASER, false, 255, true);
	}
	else {
		unit_.isAlive_ = false; 
		Smng::GetIns().Stop(SOUND::PLAYER_LASER);
	}
}

void PlayerLaser::Draw(void)
{
	if (state_ == STATE::NON) { return; }

	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, 0.0f, SIZE_Y / 2.0f, 1, 1, 0, img_[state_][counter_ % img_[state_].size()], true);
}

void PlayerLaser::Release(void)
{
	Smng::GetIns().Delete(SOUND::PLAYER_LASER);
	Smng::GetIns().Delete(SOUND::PLAYER_LASER_CHARGE);

	for (auto& ids : img_) {
		for (auto& id : ids) { DeleteGraph(id); }
	}
}

void PlayerLaser::OnCollision(UnitBase* other)
{

}