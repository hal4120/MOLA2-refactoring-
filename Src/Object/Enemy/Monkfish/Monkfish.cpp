#include"Monkfish.h"

#include"../../Player/Player.h"

Monkfish::Monkfish(NUMBER num) : EnemyBase(num)
{
}

Monkfish::~Monkfish()
{
}

void Monkfish::Load(void)
{
	EnemyBase::Load();
	imgs_.emplace_back(Utility::LoadImg("Data/Image/Enemy/Monkfish/Monkfish.png"));

	unit_.para_.size.x = SIZE_X;
	unit_.para_.size.y = SIZE_Y;
	unit_.para_.radius = SIZE_Y;

	unit_.para_.speed = MOVE_SPEED;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;
}

void Monkfish::Init(void)
{
	EnemyBase::Init();
	unit_.hp_ = 10;
}

void Monkfish::Update(void)
{

	EnemyBase::Update();
}

void Monkfish::Draw(void)
{

	EnemyBase::Draw();
}

void Monkfish::Release(void)
{

	EnemyBase::Release();
}

void Monkfish::OnCollision(UnitBase* other)
{
	EnemyBase::OnCollision(other);
}