#include"Sphere.h"

#include<DxLib.h>

#include"../../../../../Application/Application.h"
#include"../../../../../Utility/Utility.h"

#include"../../../../../Scene/Game/GameScene.h"

#include"../../Kraken.h"

#include"../../../../Player/Player.h"

Sphere::Sphere(const Vector2& bossPos, const float& bossAngle, const Vector2& playerPos):
	bossPos_(bossPos),
	bossAngle_(bossAngle),
	playerPos_(playerPos),

	img_(),
	animeCounter_(0),
	animeInterval_(0),

	lockOnInterval_(0),

	end_(true),

	moveVec_()
{
}

Sphere::~Sphere()
{
}

void Sphere::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Boss/Kraken/Attack/Sphere/Csphere.png", ANIME_NUM, ANIME_NUM, 1, RADIUS * 2, RADIUS * 2, img_);
	Utility::LoadImg(arrowImg_, "Data/Image/Effect/Arrow.png");

	unit_.para_.colliShape = CollisionShape::CIRCLE;
	unit_.para_.colliType = CollisionType::ENEMY;
	unit_.para_.radius = RADIUS * 3;

	unit_.para_.speed = 2.0f;

}

void Sphere::Init(void)
{
}

void Sphere::Update(void)
{
	if (!unit_.isAlive_) { return; }

	arrow_ = false;

	if (--lockOnInterval_ <= 0) {
		lockOnInterval_ = LOCK_ON_INTERVAL;
		Vector2 vec = playerPos_ - unit_.pos_;
		moveVec_ = (vec / vec.length()) * unit_.para_.speed;
	}

	unit_.pos_ += moveVec_;
	if (
		(unit_.pos_.x + (unit_.para_.radius) < 0.0f) ||
		(unit_.pos_.y + (unit_.para_.radius) < 0.0f) ||
		(unit_.pos_.x - (unit_.para_.radius) > Application::SCREEN_SIZE_X) ||
		(unit_.pos_.y - (unit_.para_.radius) > Application::SCREEN_SIZE_Y)
		) {
		unit_.isAlive_ = false;
	}

	if (++animeInterval_ >= 10) {
		animeInterval_ = 0;
		if (++animeCounter_ >= ANIME_NUM) {
			animeCounter_ = 0;
		}
	}
}

void Sphere::Draw(void)
{
	if (!unit_.isAlive_) { return; }

	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 3, 0, img_[animeCounter_], true);
	if (arrow_) {
		DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, arrowAngle_, arrowImg_, true);
	}
}


void Sphere::Release(void)
{
	DeleteGraph(arrowImg_);
	for (auto& id : img_) { DeleteGraph(id); }
}

void Sphere::OnCollision(UnitBase* other)
{
	if (dynamic_cast<Parry*>(other)) {
		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		if (other->GetUnit().isAlive_) { 
			unit_.para_.colliType = CollisionType::ALLY;
			moveVec_ = (vec / vec.length()) * (unit_.para_.speed * 2.0f);
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

	if (dynamic_cast<BossBase*>(other)) {
		unit_.isAlive_ = false;
	}
}

void Sphere::On(void)
{
	if (unit_.isAlive_) { return; }

	unit_.para_.colliType = CollisionType::ENEMY;

	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetRotZ(bossAngle_));
	VECTOR ofset = VTransform({ -Kraken::SIZE_X / 2.0f,0.0f,0.0f }, mat);

	unit_.pos_ = bossPos_ + Vector2(ofset.x, ofset.y);

	lockOnInterval_ = LOCK_ON_INTERVAL;
	Vector2 vec = playerPos_ - unit_.pos_;
	moveVec_ = (vec / vec.length()) * unit_.para_.speed;

	unit_.isAlive_ = true;
}
