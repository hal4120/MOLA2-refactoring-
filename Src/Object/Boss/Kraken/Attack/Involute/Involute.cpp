#include"Involute.h"

Involute::Involute(std::vector<int>image) :
	image_(image),

	parry_(false),

	bossPos_(),

	radius_(0.0f),

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
	unit_.para_.radius = 10.0f;

	angle_ = 0.0f;
}

void Involute::Update(void)
{
	if (unit_.isAlive_ == false) { return; }

	angle_ += Utility::Deg2RadF(1.0f);
	radius_ += 5.0f;

	VECTOR vec = VTransform({ radius_,0.0f,0.0f }, MGetRotZ(angle_));
	unit_.pos_ = bossPos_ + Vector2(vec.x, vec.y);

	if (radius_ > 1500.0f) { unit_.isAlive_ = false; }

	Animation();
}

void Involute::Draw(void)
{
	if (unit_.isAlive_ == false) { return; }

	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, angle_, image_.at(animeCounter_), true);
}

void Involute::Release(void)
{
	image_.clear();
}

void Involute::OnCollision(UnitBase* other)
{
	unit_.isAlive_ = false;
}

void Involute::On(Vector2 bossPos)
{
	bossPos_ = bossPos;
	radius_ = 0.0f;
	angle_ = 0.0f;
	unit_.isAlive_ = true;
}


void Involute::Animation(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= (int)image_.size()) { animeCounter_ = 0; }
	}
}