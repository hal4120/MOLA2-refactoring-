#include "EnemyBase.h"

#include"../../Scene/Game/GameScene.h"
#include"../../Manager/BlastEffect/BlastEffectManager.h"

#include"../Player/Player.h"
#include"../Boss/Shark/Shark.h"

EnemyBase::EnemyBase(NUMBER num):
	number_(num),
	imgs_(),
	animSpeed(),
	animCounter_(),
	animInterval_(),
	respawnCounter_(),
	respawnTime(),
	moveVec_(),
	arrowImg_(-1),
	arrowAngle_(0.0f),
	arrow_(false),
	parry_(false)
{
}

void EnemyBase::Load(void)
{
	Utility::LoadImg(arrowImg_, "Data/Image/Enemy/Arrow.png");
}


void EnemyBase::Init(void)
{
	unit_.pos_ = RES_POS[number_];
	unit_.isAlive_ = true;
	moveVec_ = { -1.0f,0.0f };
	parry_ = false;
}

void EnemyBase::Update(void)
{
	arrow_ = false;
	if (!unit_.isAlive_) {
		Respawn();
		return; 
	}

	Move();
	Animation();
}

void EnemyBase::Draw(void)
{
	if (!unit_.isAlive_) { return; }
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, (parry_) ? Utility::Deg2RadF(180.0f) : 0.0f, imgs_[animCounter_], true);
	if (arrow_) {
		DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, arrowAngle_, arrowImg_, true);
	}
}

void EnemyBase::Release(void)
{
	for (auto& img : imgs_) { DeleteGraph(img); }
	imgs_.clear();
	DeleteGraph(arrowImg_);
}

void EnemyBase::OnCollision(UnitBase* other)
{
	if (dynamic_cast<PlayerLaser*>(other)) {
		GameScene::Shake();
		unit_.isAlive_ = false;
		return;
	}

	if (dynamic_cast<Parry*>(other)) {
		if (parry_) { return; }
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;

		if (other->GetUnit().isAlive_) {
			parry_ = true;
			moveVec_ = vec / sqrtf(vec.x * vec.x + vec.y * vec.y);
			GameScene::HitStop(10);
		}
		else {
			arrow_ = true;
			arrowAngle_ = atan2f(vec.y, vec.x);
		}
		return;
	}

	if (dynamic_cast<Player*>(other)) {
		unit_.isAlive_ = false;
		return;
	}

	if (dynamic_cast<Shark*>(other)) {
		if (parry_) {
			unit_.isAlive_ = false;
			BlastEffectManager::On(unit_.pos_);
		}
		return;
	}

	//if (dynamic_cast<EnemyBase*>(other)) {
	//	if (!dynamic_cast<EnemyBase*>(other)->GetParry()) { return; }
	//	unit_.isAlive_ = false;
	//}
}

void EnemyBase::Move(void)
{
	unit_.pos_ += moveVec_ * ((parry_) ? PARRY_SPEED : unit_.para_.speed);
	if ((unit_.pos_.x + (unit_.para_.size.x / 2.0f) < 0.0f) ||
		unit_.pos_.x - (unit_.para_.size.x / 2.0f) > Application::SCREEN_SIZE_X) {
		unit_.isAlive_ = false;
	}
}

void EnemyBase::Respawn(void)
{
	if (++respawnCounter_ >= respawnTime) {
		respawnCounter_ = 0;
		unit_.pos_ = RES_POS[number_];
		unit_.isAlive_ = true;
		moveVec_ = { -1.0f,0.0f };
		parry_ = false;
	}
}

void EnemyBase::Animation(void)
{
	if (++animInterval_ >= animSpeed) {
		animInterval_ = 0;
		if (++animCounter_ >= imgs_.size()) {
			animCounter_ = 0;
		}
	}
}