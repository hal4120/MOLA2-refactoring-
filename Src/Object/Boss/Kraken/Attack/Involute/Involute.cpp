#include"Involute.h"

#include"../../../../../Application/Application.h"
#include"../../../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../../../Manager/Sound/SoundManager.h"

#include"../../../../../Scene/Game/GameScene.h"

#include"../../../BossBase.h"
#include"../../../../Player/Player.h"
#include"../../../../Enemy/EnemyBase.h"

Involute::Involute(std::vector<int>image, int arrowImg) :
	image_(image),
	arrowImg_(arrowImg),
	arrowAngle_(0.0f),
	arrow_(false),

	centerPos_(),

	centerDiff_(0.0f),

	animeInterval_(0),
	animeCounter_(0)
{
}

Involute::~Involute()
{
}

void Involute::Load(void)
{
}

void Involute::Init(void)
{
	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.para_.colliShape = CollisionShape::CIRCLE;
	unit_.para_.radius = 25.0f;

	angle_ = 0.0f;
}

void Involute::Update(void)
{
	arrow_ = false;
	if (unit_.isAlive_ == false) { return; }

	if (unit_.para_.colliType == CollisionType::ENEMY) {
		angle_ += Utility::Deg2RadF(2.0f);
		centerDiff_ += 1.0f;

		VECTOR vec = VTransform({ centerDiff_,0.0f,0.0f }, MGetRotZ(angle_));
		unit_.pos_ = centerPos_ + Vector2(vec.x, vec.y);

		if (centerDiff_ > 1500.0f) { unit_.isAlive_ = false; }
	}
	else if (unit_.para_.colliType == CollisionType::ALLY) {
		unit_.pos_ += parryVec_ * PARRY_SPEED;
		if (unit_.pos_.x + unit_.para_.radius < 0.0f ||
			unit_.pos_.x - unit_.para_.radius > Application::SCREEN_SIZE_X ||
			unit_.pos_.y + unit_.para_.radius < 0.0f ||
			unit_.pos_.y - unit_.para_.radius > Application::SCREEN_SIZE_Y)
		{
			unit_.isAlive_ = false;
		}
	}

	Animation();
}

void Involute::Draw(void)
{
	if (unit_.isAlive_ == false) { return; }

	VECTOR drawOfset = VTransform(DrawDiff, MGetRotZ(angle_));
	Vector2 drawPos = unit_.pos_ + Vector2(drawOfset.x, drawOfset.y);

	DrawRotaGraphF(drawPos.x, drawPos.y, 2, angle_ + Utility::Deg2RadF(180.0f), image_.at(animeCounter_), true);
	if (arrow_) { DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, arrowAngle_, arrowImg_, true); }

	if (Application::GetInstance().IsDebug()) { DrawDebug(); }
}

void Involute::Release(void)
{
	image_.clear();
}

void Involute::OnCollision(UnitBase* other)
{
	if (dynamic_cast<Parry*>(other)) {
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		if (other->GetUnit().isAlive_) {
			unit_.para_.colliType = CollisionType::ALLY;
			parryVec_ = vec.Normalize();
			GameScene::HitStop(10);
		}
		else {
			arrow_ = true;
			arrowAngle_ = atan2f(vec.y, vec.x);
		}
		return;
	}
	if ((dynamic_cast<EnemyBase*>(other) || dynamic_cast<Involute*>(other))) {
		unit_.para_.colliType = CollisionType::ALLY;
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		parryVec_ = vec.Normalize();
		GameScene::HitStop(5);
		return;
	}

	if (dynamic_cast<BossBase*>(other) ||
		dynamic_cast<Player*>(other) ||
		dynamic_cast<PlayerLaser*>(other)) {
		BlastEffectManager::On(unit_.pos_);
		angle_ = 0.0f;
		unit_.isAlive_ = false;
		return;
	}
}

void Involute::On(Vector2 bossPos)
{
	centerPos_ = bossPos;
	centerDiff_ = 0.0f;
	angle_ = 0.0f;
	unit_.para_.colliType = CollisionType::ENEMY;
	unit_.isAlive_ = true;

	Smng::GetIns().Play(SOUND::SPHERE_SHOT, true, 150);
}


void Involute::Animation(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= (int)image_.size()) { animeCounter_ = 0; }
	}
}