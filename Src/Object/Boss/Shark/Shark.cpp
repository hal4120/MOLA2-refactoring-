#include "Shark.h"

#include<DxLib.h>

#include"../../../Application/Application.h"
#include"../../../Scene/Game/GameScene.h"

#include"../../Enemy/EnemyBase.h"

Shark::Shark():
	moveVec_(),
	deathCou_(0)
{
}

Shark::~Shark()
{
}


void Shark::Load(void)
{
	imgs_.resize((int)MOTION::MAX);
	for (int i = 0; i < (int)MOTION::MAX; i++) {
		Utility::LoadArrayImg(MOTION_PATH[i], MOTION_NUM[i], MOTION_NUM[i], 1, LOAD_SIZE, LOAD_SIZE, imgs_[i]);
	}

	unit_.para_.speed = MOVE_SPEED;

	BossBase::SCALE = this->SCALE;

	unit_.para_.size.y = SIZE_Y;
	unit_.para_.size.x = SIZE_X;
	unit_.para_.radius = SIZE_Y;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;
	
#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::MOVE, &Shark::Move);
	SET_STATE(STATE::ATTACK, &Shark::Attack);
	SET_STATE(STATE::DAMAGE, &Shark::Damage);
	SET_STATE(STATE::DEATH, &Shark::Death);
}

void Shark::Init(void)
{
	unit_.isAlive_ = true;

	unit_.pos_.x = Application::SCREEN_SIZE_X - SIZE_X / 2.0f;
	unit_.pos_.y = Application::SCREEN_SIZE_Y / 2.0f;

	state_ = (int)STATE::MOVE;

	moveVec_ = { 0.0f,1.0f };

	deathCou_ = 0;

	ChangeMotion((int)MOTION::MOVE);

	unit_.hp_ = HP_MAX;

	reverse_ = true;
}

void Shark::OnCollision(UnitBase* other)
{
	if (state_ == (int)STATE::DAMAGE || state_ == (int)STATE::DEATH) { return; }

	if (dynamic_cast<EnemyBase*>(other)) {
		if (dynamic_cast<EnemyBase*>(other)->GetParry()) {
			GameScene::Slow(20);
			GameScene::Shake();

			state_ = (int)STATE::DAMAGE;

			ChangeMotion((int)MOTION::DAMAGE, false);
			animCounter_ = 1;
		
			unit_.hp_ -= 10;
			if (unit_.hp_ <= 0) {
				state_ = (int)STATE::DEATH;
				ChangeMotion((int)MOTION::DAMAGE);
				deathCou_ = 0;
			}
		}
		return;
	}
}


void Shark::Move(void)
{
	unit_.pos_ += moveVec_ * unit_.para_.speed;

	if (unit_.pos_.y - (unit_.para_.size.y / 2.0f) < 0.0f ||
		unit_.pos_.y + (unit_.para_.size.y / 2.0f) > Application::SCREEN_SIZE_Y) {
		moveVec_.y *= -1;
		unit_.pos_ += moveVec_ * unit_.para_.speed;
	}

	if (unit_.pos_.x < Application::SCREEN_SIZE_X - unit_.para_.size.x / 2.0f) {
		moveVec_.x = 1.0f;
	} else {
		moveVec_.x = 0.0f;
	}
}

void Shark::Attack(void)
{
}

void Shark::Damage(void)
{
	// ダメージモーションが終わったら状態も戻す
	if (motion_ != (int)MOTION::DAMAGE) {
		state_ = (int)STATE::MOVE;
	}
}

void Shark::Death(void)
{
	if (++deathCou_ >= DEATH_PERFOR_TIME) {
		deathCou_ = 0;
		unit_.isAlive_ = false;
	}
}


void Shark::AttackUpdate(void)
{
}

void Shark::AttackDraw(void)
{
}

void Shark::AttackRelease(void)
{
}