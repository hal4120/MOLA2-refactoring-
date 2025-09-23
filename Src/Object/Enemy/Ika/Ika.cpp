#include"Ika.h"

#include"../../Player/Player.h"

Ika::Ika(NUMBER num) : EnemyBase(num)
{
}

Ika::~Ika()
{
}

void Ika::Load(void)
{
	EnemyBase::Load();
	imgs_.emplace_back(Utility::LoadImg("Data/Image/Enemy/Ika/Ika.png"));

	drawScale_ = 0.12f;

	unit_.para_.size.x = SIZE_X;
	unit_.para_.size.y = SIZE_Y;
	unit_.para_.radius = SIZE_Y;

	unit_.para_.speed = MOVE_SPEED;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

	respawnTime = RESPAWN_TIME;
}

void Ika::OnCollision(UnitBase* other)
{
	EnemyBase::OnCollision(other);
}

void Ika::Move(void)
{
	EnemyBase::Move();

	if (parry_) { return; }

}