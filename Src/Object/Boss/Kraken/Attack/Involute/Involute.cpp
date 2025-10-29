#include"Involute.h"

#include"../../../../../Application/Application.h"

Involute::Involute(std::vector<int>image) :
	image_(image),

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
	if (unit_.isAlive_ == false) { return; }

	if (unit_.para_.colliType == CollisionType::ENEMY) {
		angle_ += Utility::Deg2RadF(2.0f);
		centerDiff_ += 1.0f;

		VECTOR vec = VTransform({ centerDiff_,0.0f,0.0f }, MGetRotZ(angle_));
		unit_.pos_ = centerPos_ + Vector2(vec.x, vec.y);

		if (centerDiff_ > 1500.0f) { unit_.isAlive_ = false; }
	}
	else if (unit_.para_.colliType == CollisionType::ALLY) {

	}

	Animation();
}

void Involute::Draw(void)
{
	if (unit_.isAlive_ == false) { return; }

	VECTOR drawOfset = VTransform(DrawDiff, MGetRotZ(angle_));
	Vector2 drawPos = unit_.pos_ + Vector2(drawOfset.x, drawOfset.y);

	DrawRotaGraphF(drawPos.x, drawPos.y, 2, angle_ + Utility::Deg2RadF(180.0f), image_.at(animeCounter_), true);

	if (Application::GetInstance().IsDebug()) { DrawDebug(); }
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
	centerPos_ = bossPos;
	centerDiff_ = 0.0f;
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