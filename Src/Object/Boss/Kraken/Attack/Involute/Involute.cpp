#include"Involute.h"

Involute::Involute(std::vector<int>image) :
	image_(image),

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
}

void Involute::Animation(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= (int)image_.size()) { animeCounter_ = 0; }
	}
}