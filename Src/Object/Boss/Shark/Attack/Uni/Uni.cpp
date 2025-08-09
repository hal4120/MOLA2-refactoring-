#include "Uni.h"

#include"../../../../../Application/Application.h"
#include"../../../../../Manager/BlastEffect/BlastEffectManager.h"

#include"../../../../../Scene/Game/GameScene.h"

#include"../../../BossBase.h"
#include"../../../../Player/Player.h"
#include"../../../../Enemy/EnemyBase.h"

Uni::Uni(int* img,int arrowImg) :
	img_(),
	arrowImg_(arrowImg),
	imgState_(IMG_NUM::SUMMON),
	state_(STATE::NON),
	target_(),
	moveVec_(),
	stateFuncPtr(),
	angle_(0.0f),
	counter_(0),
	arrowAngle_(0.0f),
	arrow_(false)
{
	img_[(int)IMG_NUM::SUMMON] = img[(int)IMG_NUM::SUMMON];
	img_[(int)IMG_NUM::UNI] = img[(int)IMG_NUM::UNI];
}

Uni::~Uni()
{
}

void Uni::Load(void)
{
	unit_.para_.radius = SIZE / 2.0f;
	unit_.para_.colliShape = CollisionShape::CIRCLE;
	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.para_.speed = SPEED;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<void (Uni::*)(void)>(func)
	SET_STATE(STATE::SUMMON, &Uni::Summon);
	SET_STATE(STATE::THROWN, &Uni::Thrown);
	SET_STATE(STATE::REFLECTION, &Uni::Reflection);
	SET_STATE(STATE::BLAST, &Uni::Blast);
}

void Uni::Update(void)
{
	arrow_ = false;
	if (state_ == STATE::NON) { return; }
	(this->*stateFuncPtr[state_])();
}

void Uni::Draw(void)
{
	if (state_ == STATE::NON || state_ == STATE::BLAST) { return; }
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, SCALE, angle_, img_[(int)imgState_], true);
	if (arrow_) { DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, arrowAngle_, arrowImg_, true); }
}

void Uni::OnCollision(UnitBase* other)
{
	if (state_ == STATE::NON || state_ == STATE::BLAST) { return; }

	if (dynamic_cast<Parry*>(other)) {
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		if (other->GetUnit().isAlive_) {
			state_ = STATE::REFLECTION;
			unit_.para_.colliType = CollisionType::ALLY;
			unit_.isAlive_ = true;
			moveVec_ = vec / sqrtf(vec.x * vec.x + vec.y * vec.y);
			GameScene::HitStop(10);
		}
		else {
			arrow_ = true;
			arrowAngle_ = atan2f(vec.y, vec.x);
		}
		return;
	}
	if ((dynamic_cast<EnemyBase*>(other) || dynamic_cast<Uni*>(other))
		&& unit_.para_.colliType == CollisionType::ENEMY) {
		state_ = STATE::REFLECTION;
		unit_.para_.colliType = CollisionType::ALLY;
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		moveVec_ = vec / sqrtf(vec.x * vec.x + vec.y * vec.y);
		GameScene::HitStop(10);
		return;
	}

	if (dynamic_cast<BossBase*>(other) ||
		dynamic_cast<Player*>(other)||
		dynamic_cast<PlayerLaser*>(other)) {
		BlastEffectManager::On(unit_.pos_);
		angle_ = 0.0f;
		unit_.isAlive_ = false;
		state_ = STATE::NON;
		return;
	}
}

void Uni::Summon(void)
{
	angle_ -= Utility::Deg2RadF(15.0f);
	if (++counter_ >= SUMMON_TIME) {
		counter_ = 0;
		angle_ = 0.0f;
		unit_.isAlive_ = true;
		state_ = STATE::THROWN;
	}
	imgState_ = IMG_NUM::SUMMON;
}

void Uni::Thrown(void)
{
	angle_ -= Utility::Deg2RadF(5.0f);
	unit_.pos_ += moveVec_ * unit_.para_.speed;
	Vector2 vec = target_ - unit_.pos_;
	float dif = sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (dif <= unit_.para_.speed) {
		BlastEffectManager::On(unit_.pos_);
		angle_ = 0.0f;
		state_ = STATE::BLAST;
	}
	imgState_ = IMG_NUM::UNI;
}

void Uni::Reflection(void)
{
	angle_ += Utility::Deg2RadF(10.0f);
	unit_.pos_ += moveVec_ * REFLECTION_SPEED;
	if (unit_.pos_.x + unit_.para_.radius < 0.0f ||
		unit_.pos_.x - unit_.para_.radius > Application::SCREEN_SIZE_X ||
		unit_.pos_.y + unit_.para_.radius < 0.0f ||
		unit_.pos_.y - unit_.para_.radius > Application::SCREEN_SIZE_Y)
	{
		state_ = STATE::NON;
		unit_.isAlive_ = false;
	}
	imgState_ = IMG_NUM::UNI;
}

void Uni::Blast(void)
{
	if (++counter_ >= BLAST_TIME) {
		counter_ = 0;
		state_ = STATE::NON;
		unit_.isAlive_ = false;
	}
}


void Uni::On(Vector2 pos, Vector2 target)
{
	state_ = STATE::SUMMON;

	angle_ = 0.0f;
	counter_ = 0;

	unit_.pos_ = pos;
	target_ = target;

	moveVec_ = target_ - unit_.pos_;
	moveVec_ /= sqrtf(moveVec_.x * moveVec_.x + moveVec_.y * moveVec_.y);

	unit_.para_.colliType = CollisionType::ENEMY;
}