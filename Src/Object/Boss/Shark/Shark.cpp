#include "Shark.h"

#include<DxLib.h>

#include"../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../Application/Application.h"
#include"../../../Scene/SceneManager/SceneManager.h"
#include"../../../Scene/Game/GameScene.h"

#include"../../Enemy/EnemyBase.h"
#include"../../Player/Player.h"

Shark::Shark(const Vector2& playerPos):
	BossBase(playerPos),
	moveVec_(),
	attackInterval_(),
	attackInit_(false),
	attackEnd_(false),
	deathCou_(0),
	attackState_(),
	ikura_(nullptr),
	uni_(nullptr),
	mizu_(nullptr),
	laser_(nullptr)
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
	uni_ = new UniShooter();
	uni_->Load();
	mizu_ = new Mizu(unit_.pos_, playerPos_);
	mizu_->Load();
	laser_ = new SharkLaser(unit_.pos_);
	laser_->Load();
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
	uni_->Init();
	mizu_->Init();
	laser_->Init();
}

void Shark::OnCollision(UnitBase* other)
{
	if (state_ == (int)STATE::DAMAGE || state_ == (int)STATE::DEATH) { return; }

	if (dynamic_cast<EnemyBase*>(other)) {
		GameScene::Slow(20);
		GameScene::Shake();

		HpDecrease(10);
		return;
	}

	if (dynamic_cast<Uni*>(other)) {
		GameScene::Slow(20);
		GameScene::Shake();

		HpDecrease(10);
		return;
	}
	if (dynamic_cast<Mizu*>(other)) {
		GameScene::Slow(20);
		GameScene::Shake();

		HpDecrease(5);
		return;
	}

	if (dynamic_cast<PlayerLaser*>(other)) {
		GameScene::Slow(20);
		GameScene::Shake();

		HpDecrease(5);
		return;
	}

}

std::vector<UnitBase*> Shark::AttackIns(void)
{
	std::vector<UnitBase*> ret;

	for (auto& ikura : ikura_->Ikuras()) { ret.emplace_back(ikura); }
	for (auto& uni : uni_->Unis()) { ret.emplace_back(uni); }
	ret.emplace_back(mizu_);
	ret.emplace_back(laser_);

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
		attackInterval_ = ATTACK_INTERVAL;
		attackInit_ = false;
		state_ = (int)STATE::ATTACK;
		ChangeMotion((int)MOTION::ATTACK);
	}
}

void Shark::Attack(void)
{
	// UŒ‚ó‘Ô‚Ö‘JˆÚŒãA‚P‰ñ–Ú‚Ìˆ—```````
	if (!attackInit_) {

		attackInit_ = true;
		attackEnd_ = false;

		attackState_ = AttackLottery();
		switch (attackState_)
		{
		case Shark::ATTACK_KINDS::NON:
			attackEnd_ = true;
			break;
		case Shark::ATTACK_KINDS::IKURA:
			ikura_->On();
			break;
		case Shark::ATTACK_KINDS::UNI:
  			uni_->Shot(playerPos_);
			break;
		case Shark::ATTACK_KINDS::MIZU:
			mizu_->On();
			break;
		case Shark::ATTACK_KINDS::LASER:
			laser_->On();
			break;
		}
	}
	//```````````````````````

	// UŒ‚ó‘Ô’†‚Ì‚Ýs‚¤XVˆ—A‚Ü‚½UŒ‚I—¹”»’f
	switch (attackState_)
	{
	case Shark::ATTACK_KINDS::IKURA:
		ikura_->Shot();
		if (ikura_->End()) { attackEnd_ = true; }
		break;
	case Shark::ATTACK_KINDS::UNI:
		if (uni_->End()) { attackEnd_ = true; }
		break;
	case Shark::ATTACK_KINDS::MIZU:
		if (mizu_->End()) { attackEnd_ = true; }
		break;
	case Shark::ATTACK_KINDS::LASER:
		if (laser_->End()) { attackEnd_ = true; }
		break;
	}
	//```````````````````````

	// UŒ‚I—¹A’Êíó‘Ô‚Ö‘JˆÚ````````
	if (attackEnd_) {
		attackInterval_ = ATTACK_INTERVAL;
		state_ = (int)STATE::MOVE;
		ChangeMotion((int)MOTION::MOVE);
	}
	//`````````````````````
}

void Shark::Damage(void)
{
	// ƒ_ƒ[ƒWƒ‚[ƒVƒ‡ƒ“‚ªI‚í‚Á‚½‚çó‘Ô‚à–ß‚·
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
		if (deathCou_ % 10 == 0) {
			Vector2 point = unit_.pos_;
			point += Vector2(
				(float)(GetRand((int)(unit_.para_.size.x)) - unit_.para_.size.x / 2.0f),
				(float)(GetRand((int)(unit_.para_.size.y)) - unit_.para_.size.y / 2.0f)
			);
			BlastEffectManager::On(point);
		}
	}
}


void Shark::HpDecrease(int damage)
{
	state_ = (int)STATE::DAMAGE;
	ChangeMotion((int)MOTION::DAMAGE, false);
	animCounter_ = 1;

	laser_->Off();

	unit_.hp_ -= damage;
	if (unit_.hp_ <= 0) {
		state_ = (int)STATE::DEATH;
		ChangeMotion((int)MOTION::DAMAGE);
		deathCou_ = 0;
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
		ret = ATTACK_KINDS::UNI;
	}
	else if (rand <= 6000) {
		ret = ATTACK_KINDS::MIZU;
	}
	else if (rand <= 8000) {
		ret = ATTACK_KINDS::LASER;
	}
	else if (rand <= 10000) {
		ret = ATTACK_KINDS::UNI;
	}
	return ret;
}

void Shark::AttackUpdate(void)
{
	ikura_->Update();
	uni_->Update();
	mizu_->Update();
	laser_->Update();
}

void Shark::AttackDraw(void)
{
	ikura_->Draw();
	uni_->Draw();
	mizu_->Draw();
	laser_->Draw();
}

void Shark::AttackRelease(void)
{
	if (ikura_) {
		ikura_->Release();
		delete ikura_;
		ikura_ = nullptr;
	}
	if (uni_) {
		uni_->Release();
		delete uni_;
		uni_ = nullptr;
	}
	if (mizu_) {
		mizu_->Release();
		delete mizu_;
		mizu_ = nullptr;
	}
	if (laser_) {
		laser_->Release();
		delete laser_;
		laser_ = nullptr;
	}
}