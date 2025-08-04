#include "Shark.h"

#include<DxLib.h>

#include"../../../Application/Application.h"
#include"../../../Scene/Game/GameScene.h"

#include"../../Enemy/EnemyBase.h"

Shark::Shark():
	state_(),
	stateFuncPtr(),
	moveVec_(),
	imgs_(),
	motion_(),
	animCounter_(0),
	animInterval_(0),
	animLoop_(true)
{
}

Shark::~Shark()
{
}

void Shark::Load(void)
{
	for (int i = 0; i < (int)MOTION::MAX; i++) {
		Utility::LoadArrayImg(MOTION_PATH[i], MOTION_NUM[i], MOTION_NUM[i], 1, LOAD_SIZE, LOAD_SIZE, imgs_[i]);
	}

	unit_.para_.speed = MOVE_SPEED;

	unit_.para_.size.y = SIZE_Y;
	unit_.para_.size.x = SIZE_X;
	unit_.para_.radius = SIZE_Y;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

	stateFuncPtr[(int)STATE::MOVE] = &Shark::Move;
	stateFuncPtr[(int)STATE::ATTACK] = &Shark::Attack;
	stateFuncPtr[(int)STATE::DAMAGE] = &Shark::Damage;
	stateFuncPtr[(int)STATE::DEATH] = &Shark::Death;

}

void Shark::Init(void)
{
	unit_.isAlive_ = true;

	unit_.pos_.x = Application::SCREEN_SIZE_X - SIZE_X / 2.0f;
	unit_.pos_.y = Application::SCREEN_SIZE_Y / 2.0f;

	state_ = STATE::MOVE;

	moveVec_ = { 0.0f,1.0f };

	ChangeMotion(MOTION::MOVE);

	unit_.hp_ = HP_MAX;
}

void Shark::Update(void)
{
	Invi();

	(this->*stateFuncPtr[(int)state_])();

	Animation();
}

void Shark::Draw(void)
{
	if (!unit_.isAlive_) { return; }
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, SCALE, 0, imgs_[(int)motion_][animCounter_], true, true);
}

void Shark::Release(void)
{
	for (auto& imgs : imgs_) {
		for (auto& img : imgs) { DeleteGraph(img); }
	}
}

void Shark::OnCollision(UnitBase* other)
{
	if (state_ == STATE::DAMAGE || state_ == STATE::DEATH) { return; }

	if (dynamic_cast<EnemyBase*>(other)) {
		if (dynamic_cast<EnemyBase*>(other)->GetParry()) {
			GameScene::Slow(20);
			GameScene::Shake();

			state_ = STATE::DAMAGE;

			ChangeMotion(MOTION::DAMAGE, false);
			animCounter_ = 1;
		
			unit_.hp_ -= 10;
			if (unit_.hp_ <= 0) {
				state_ = STATE::DEATH;
				ChangeMotion(MOTION::DAMAGE);
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
	if (motion_ != MOTION::DAMAGE) {
		state_ = STATE::MOVE;
	}
}

void Shark::Death(void)
{
	static int deathCou = 0;
	if (++deathCou >= 180) {
		unit_.isAlive_ = false;
	}
}



void Shark::ChangeMotion(MOTION motion, bool loop)
{
	motion_ = motion;
	animLoop_ = loop;
	animCounter_ = 0;
	animInterval_ = 0;
}

void Shark::Animation(void)
{
	if (++animInterval_ >= ANIM_INTERVAL) {
		animInterval_ = 0;
		if (++animCounter_ >= imgs_[(int)motion_].size()) {
			if (animLoop_) {
				animCounter_ = 0;
			}
			else {
				ChangeMotion(MOTION::MOVE);
			}
		}
	}
}