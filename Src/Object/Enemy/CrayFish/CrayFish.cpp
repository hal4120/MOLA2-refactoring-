#include"CrayFish.h"

#include"../../Player/Player.h"

CrayFish::CrayFish(NUMBER num) : EnemyBase(num)
{
}

CrayFish::~CrayFish()
{
}

void CrayFish::Load(void)
{
	EnemyBase::Load();
	imgs_.emplace_back(Utility::LoadImg("Data/Image/Enemy/CrayFish/CrayFish.png"));

	unit_.para_.size.x = SIZE_X;
	unit_.para_.size.y = SIZE_Y;
	unit_.para_.radius = SIZE_Y;

	unit_.para_.speed = MOVE_SPEED;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

	respawnTime = RESPAWN_TIME;
}

void CrayFish::OnCollision(UnitBase* other)
{
	EnemyBase::OnCollision(other);
}

void CrayFish::Move(void)
{
	static float wave_ = 0.0f;

	// 前進
	unit_.pos_ += moveVec_ * ((parry_) ? PARRY_SPEED : unit_.para_.speed);

	// 上下にふわふわ
	wave_ += 0.01f;
	unit_.pos_.y += sinf(wave_) * 4.0f;

	// 画面外チェック
	if (
		(unit_.pos_.x + (unit_.para_.size.x / 2.0f) < 0.0f) ||
		(unit_.pos_.y + (unit_.para_.size.y / 2.0f) < 0.0f) ||
		(unit_.pos_.x - (unit_.para_.size.x / 2.0f) > Application::SCREEN_SIZE_X) ||
		(unit_.pos_.y - (unit_.para_.size.y / 2.0f) > Application::SCREEN_SIZE_Y)
		)
	{
		unit_.isAlive_ = false;
	}

	if (parry_) { return; }
}
