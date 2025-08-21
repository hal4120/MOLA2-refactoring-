#include"Parry.h"

#include<DxLib.h>

#include"../../../Manager/Sound/SoundManager.h"

#include"../Player.h"

#include"../../Enemy/EnemyBase.h"
#include"../../Boss/Shark/Shark.h"
#include"../../Boss/SharkHard/SharkHard.h"

Parry::Parry(const Vector2& playerPos):
	img_(),
	counter_(0),
	countInterval_(0),
	mag_(1.0f),
	coolTime_(0),
	player_(playerPos)
{
}

Parry::~Parry()
{
}

void Parry::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Player/Parry/Parry.png",
		ANIM_NUM_ALL, ANIM_NUM_X, ANIM_NUM_Y,
		LOAD_SIZE_X, LOAD_SIZE_Y, img_);

	unit_.para_.radius = LOAD_SIZE_X;

	unit_.para_.colliShape = CollisionShape::CIRCLE;
	unit_.para_.colliType = CollisionType::ALLY;

	unit_.isInvici_ = false;
	unit_.aliveCollision_ = false;

	Smng::GetIns().Load(SOUND::PLAYER_ATTACK);
	Smng::GetIns().Load(SOUND::PARRY);
}

void Parry::Init(void)
{
	counter_ = 0;
	countInterval_ = 0;

	mag_ = DEFAULT_MAG;
}

void Parry::Update(void)
{
	if (coolTime_ > 0) { coolTime_--; }

	unit_.pos_ = player_;
	unit_.pos_.x += Player::LOAD_SIZE_X / 2;

	if (!unit_.isAlive_) { return; }

	if (++countInterval_ >= COUNT_SPEED) {
		countInterval_ = 0;
		if (++counter_ >= ANIM_NUM_ALL) {
			counter_ = 0;
			unit_.isAlive_ = false;
		}
	}
}

void Parry::Draw(void)
{
	if (coolTime_ > 0) {
		Vector2 oneSize = Vector2((float)Player::LOAD_SIZE_X / (float)COOL_TIME, COOL_TIME_DRAW_SIZE_Y);
		Vector2 sPos = player_ - Vector2(Player::LOAD_SIZE_X / 2.0f, (Player::LOAD_SIZE_Y / 2.0f) + oneSize.y);
		DrawBoxAA(sPos.x, sPos.y, sPos.x + Player::LOAD_SIZE_X, sPos.y + oneSize.y, 0x000000, true);
		DrawBoxAA(sPos.x, sPos.y, sPos.x + (coolTime_ * oneSize.x), sPos.y + oneSize.y, 0x00ffff, true);
	}
	if (!unit_.isAlive_) { return; }
	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, 0.0f, LOAD_SIZE_Y / 2.0f, mag_, mag_, 0, img_[counter_], true);
}

void Parry::Release(void)
{
	Smng::GetIns().Delete(SOUND::PLAYER_ATTACK);
	for (auto& id : img_) { DeleteGraph(id); }
}

void Parry::On(void)
{
	if (coolTime_ > 0 || unit_.isAlive_) { return; }
	coolTime_ = COOL_TIME;
	counter_ = 0;
	countInterval_ = 0;
	unit_.isAlive_ = true;
	Smng::GetIns().Play(SOUND::PLAYER_ATTACK,true);
}

void Parry::OnCollision(UnitBase* other)
{
	if (!unit_.isAlive_) { return; }

	coolTime_ = 0;

	if (dynamic_cast<EnemyBase*>(other) ||
		dynamic_cast<Uni*>(other) ||
		dynamic_cast<Mizu*>(other) ||
		dynamic_cast<SharkTackle*>(other) ||
		dynamic_cast<HardUni*>(other) ||
		dynamic_cast<HardMizu*>(other) ||
		dynamic_cast<HardSharkTackle*>(other)
		) {


		mag_ += MAG_ONE_SIZE_UP;
		if (mag_ > MAX_MAG) { mag_ = MAX_MAG; }
		unit_.para_.radius = LOAD_SIZE_X * mag_;

		spChargeFunPtr_();

		Smng::GetIns().Play(SOUND::PARRY, true);
	}
}