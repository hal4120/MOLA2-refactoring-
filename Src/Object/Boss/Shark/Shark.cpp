#include "Shark.h"

#include<DxLib.h>

#include"../../../Application/Application.h"
#include"../../../Scene/Game/GameScene.h"

#include"Attack/Ikura/IkuraShooter.h"

#include"../../Enemy/EnemyBase.h"
#include"../../Player/Player.h"

Shark::Shark():
	moveVec_(),
	attackInterval_(),
	attackInit_(false),
	attackEnd_(false),
	deathCou_(0),
	attackState_(),
	ikura_(nullptr)
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

	ikura_ = new IkuraShooter(unit_.pos_);
	ikura_->Load();
}

void Shark::Init(void)
{
	unit_.isAlive_ = true;

	unit_.pos_.x = Application::SCREEN_SIZE_X - SIZE_X / 2.0f;
	unit_.pos_.y = Application::SCREEN_SIZE_Y / 2.0f;

	state_ = (int)STATE::MOVE;

	moveVec_ = { 0.0f,1.0f };

	attackInterval_ = ATTACK_INTERVAL;
	attackInit_ = false;
	attackEnd_ = false;

	deathCou_ = 0;

	ChangeMotion((int)MOTION::MOVE);

	unit_.hp_ = HP_MAX;

	reverse_ = true;
	angle_ = 0.0f;

	attackState_ = ATTACK_KINDS::NON;

	ikura_->Init();
}

void Shark::OnCollision(UnitBase* other)
{
	if (state_ == (int)STATE::DAMAGE || state_ == (int)STATE::DEATH) { return; }

	if (dynamic_cast<EnemyBase*>(other)) {
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
		return;
	}

	if (dynamic_cast<PlayerLaser*>(other)) {
		GameScene::Slow(20);
		GameScene::Shake();

		state_ = (int)STATE::DAMAGE;
		ChangeMotion((int)MOTION::DAMAGE, false);
		animCounter_ = 1;

		unit_.inviciCounter_ = 10;
		unit_.hp_ -= 5;
		
		if (unit_.hp_ <= 0) {
			state_ = (int)STATE::DEATH;
			ChangeMotion((int)MOTION::DAMAGE);
			deathCou_ = 0;
		}
		return;
	}

}

std::vector<UnitBase*> Shark::AttackIns(void)
{
	std::vector<UnitBase*> ret;

	for (auto& ikura : ikura_->Ikuras()) { ret.emplace_back(ikura); }

	return ret;
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

	if (attackInterval_ > 0) {
		attackInterval_--;
	}
	else
	{
		attackInit_ = false;
		state_ = (int)STATE::ATTACK;
		ChangeMotion((int)MOTION::ATTACK);
	}
}

void Shark::Attack(void)
{
	if (!attackInit_) {
		attackState_ = AttackLottery();
		switch (attackState_)
		{
		case Shark::ATTACK_KINDS::NON:
			break;
		case Shark::ATTACK_KINDS::IKURA:
			ikura_->On();
			break;
		}

		attackInit_ = true;
		attackEnd_ = false;
	}

	switch (attackState_)
	{
	case Shark::ATTACK_KINDS::NON:
		break;
	case Shark::ATTACK_KINDS::IKURA:
		if (ikura_->End()) { attackEnd_ = true; }
		break;
	}


	if (attackEnd_) {
		attackInterval_ = ATTACK_INTERVAL;
		state_ = (int)STATE::MOVE;
		ChangeMotion((int)MOTION::MOVE);
	}
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
	else {
		angle_ += Utility::Deg2RadF(1.0f);
	}
}


Shark::ATTACK_KINDS Shark::AttackLottery(void)
{
	ATTACK_KINDS ret = ATTACK_KINDS::NON;

	int rand = GetRand(10000);

	if (rand <= 2000) {
		ret = ATTACK_KINDS::IKURA;
	}
	else if (rand <= 4000) {
		ret = ATTACK_KINDS::IKURA;
	}
	else if (rand <= 6000) {
		ret = ATTACK_KINDS::IKURA;
	}
	else if (rand <= 8000) {
		ret = ATTACK_KINDS::IKURA;
	}
	else if (rand <= 10000) {
		ret = ATTACK_KINDS::IKURA;
	}

	return ret;
}

void Shark::AttackUpdate(void)
{
	ikura_->Update();
}

void Shark::AttackDraw(void)
{
	ikura_->Draw();
}

void Shark::AttackRelease(void)
{
	ikura_->Release();
}