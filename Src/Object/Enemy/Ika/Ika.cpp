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

	drawScale_ = 0.2f;

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

void Ika::Respawn(void)
{
	if (++respawnCounter_ >= respawnTime) {
		respawnCounter_ = 0;

		dir_ = (DIR)(GetRand(((int)DIR::MAX)) - 1);

		unit_.pos_ = RES_POS[(int)dir_][number_];

		unit_.isAlive_ = true;

		moveVec_ = MOVE_VEC_TABLE[(int)dir_];

		parry_ = false;
		unit_.para_.colliType = CollisionType::ENEMY;
	}
}
