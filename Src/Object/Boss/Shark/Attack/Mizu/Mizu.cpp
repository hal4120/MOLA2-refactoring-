#include"Mizu.h"

#include"../../../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../../../Scene/Game/GameScene.h"

#include"../../Shark.h"
#include"../../../BossBase.h"
#include"../../../../Enemy/EnemyBase.h"
#include"../../../../Player/Player.h"

Mizu::Mizu(const Vector2& bossPos, const Vector2& playerPos):
	bossPos_(bossPos),
	playerPos_(playerPos),
	img_(-1),
	moveVec_(),
	angle_(0.0f),
	counter_(0),
	shot_(false),
	arrowImg_(-1),
	arrowAngle_(0.0f),
	arrow_(false)
{
}

Mizu::~Mizu()
{
}

void Mizu::Load(void)
{
	Utility::LoadImg(img_, "Data/Image/Boss/Shark/Attack/Mizu/Mizu.png");
	Utility::LoadImg(arrowImg_, "Data/Image/Effect/Arrow.png");

	unit_.para_.radius = SIZE / 2;

	unit_.para_.colliShape = CollisionShape::CIRCLE;
	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.para_.speed = SPEED;
}

void Mizu::Init(void)
{
	shot_ = false;
}

void Mizu::Update(void)
{
	arrow_ = false;
	if (!unit_.isAlive_) {
		if (!shot_) { return; }

		if (++counter_ >= SHOT_TIME) {
			counter_ = 0;
			shot_ = false;
		}
		return;
	}

	if (unit_.para_.colliType == CollisionType::ALLY) {
		unit_.pos_ += moveVec_ * PARRY_SPEED;
		if (unit_.pos_.x + unit_.para_.radius < 0.0f ||
			unit_.pos_.x - unit_.para_.radius > Application::SCREEN_SIZE_X ||
			unit_.pos_.y + unit_.para_.radius < 0.0f ||
			unit_.pos_.y - unit_.para_.radius > Application::SCREEN_SIZE_Y)
		{
			unit_.isAlive_ = false;
		}
		return;
	}

	Vector2 vec = playerPos_ - unit_.pos_;
	float dif = sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (dif <= unit_.para_.speed) { unit_.isAlive_ = false; }
	vec /= dif;
	unit_.pos_ += vec * unit_.para_.speed;

	angle_ = atan2f(vec.y, vec.x);
}

void Mizu::Draw(void)
{
	if (!unit_.isAlive_) { return; }
	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, CENTER_X, CENTER_Y, SCALE, SCALE, angle_, img_, true);
	if (arrow_) { DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, arrowAngle_, arrowImg_, true); }
}

void Mizu::Release(void)
{
	DeleteGraph(img_);
}

void Mizu::OnCollision(UnitBase* other)
{
	if (dynamic_cast<Player*>(other)) {
		BlastEffectManager::On(unit_.pos_);
		unit_.isAlive_ = false;
		return;
	}
	if (dynamic_cast<Parry*>(other)) {
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		if (other->GetUnit().isAlive_) {
			unit_.para_.colliType = CollisionType::ALLY;
			
			moveVec_ = vec / sqrtf(vec.x * vec.x + vec.y * vec.y);
			angle_ = atan2f(moveVec_.y, moveVec_.x);

			GameScene::HitStop(10);
		} else {
			arrow_ = true;
			arrowAngle_ = atan2f(vec.y, vec.x);
		}
		return;
	}

	if (dynamic_cast<EnemyBase*>(other)) {
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		unit_.para_.colliType = CollisionType::ALLY;

		moveVec_ = vec / sqrtf(vec.x * vec.x + vec.y * vec.y);
		angle_ = atan2f(moveVec_.y, moveVec_.x);

		GameScene::HitStop(10);
	}
}

void Mizu::On(void)
{
	unit_.isAlive_ = false;
	shot_ = true;
	counter_ = 0;
}

bool Mizu::End(void) 
{
	if (shot_) { return false; }
	unit_.pos_ = bossPos_;
	unit_.pos_.x -= Shark::SIZE_X / 2;
	unit_.para_.colliType = CollisionType::ENEMY;
	unit_.isAlive_ = true;
	return true;
}
