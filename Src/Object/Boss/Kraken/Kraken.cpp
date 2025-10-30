#include"Kraken.h"

#include<DxLib.h>

#include"../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../Application/Application.h"
#include"../../../Scene/SceneManager/SceneManager.h"
#include"../../../Manager/Sound/SoundManager.h"
#include"../../../Scene/Game/GameScene.h"

#include"../../Enemy/EnemyBase.h"
#include"../../Player/Player.h"

Kraken::Kraken(const Vector2& playerPos) :
	BossBase(playerPos),

	idleTime_(0),

	moveVec_(),
	moveInit_(false),

	attackState_(ATTACK_KINDS::NON),
	attackInit_(false),
	attackEnd_(false),

	deathCou_(0),

	sumi_(nullptr),
	sphere_(nullptr),
	tentacle_(nullptr),
	involute_(nullptr),
	tackle_(nullptr)
{
}

Kraken::~Kraken()
{
}

void Kraken::Load(void)
{
	imgs_.resize((int)MOTION::MAX);
	for (int i = 0; i < (int)MOTION::MAX; i++) {
		Utility::LoadArrayImg(MOTION_PATH[i], MOTION_NUM[i], MOTION_NUM[i], 1, LOAD_SIZE, LOAD_SIZE, imgs_[i]);
	}

	unit_.para_.speed = MOVE_SPEED;

	BossBase::SCALE = this->SCALE;

	unit_.para_.size.x = SIZE_X;
	unit_.para_.size.y = SIZE_Y;
	unit_.para_.radius = SIZE_Y / 2;
	drawCenter_ = { LOAD_SIZE / 3,LOAD_SIZE / 2 };

	ofsetAngle_ = Utility::Deg2RadF(180.0f);

	maxHP = HP_MAX;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::IDLE, &Kraken::Idle);
	SET_STATE(STATE::MOVE, &Kraken::Move);
	SET_STATE(STATE::ATTACK, &Kraken::Attack);
	SET_STATE(STATE::DAMAGE, &Kraken::Damage);
	SET_STATE(STATE::DEATH, &Kraken::Death);

	tentacle_ = new TentacleShooter(playerPos_.x);
	tentacle_->Load();
	sphere_ = new SphereShooter(unit_.pos_, angle_, playerPos_);
	sphere_->Load();
	sumi_ = new SumiShooter(unit_.pos_, angle_, playerPos_);
	sumi_->Load();
	involute_ = new InvoluteShooter(unit_.pos_, angle_);
	involute_->Load();
	tackle_ = new KrakenTackle(unit_.pos_, angle_, playerPos_);
}

void Kraken::Init(void)
{
	unit_.isAlive_ = true;

	unit_.pos_.x = Application::SCREEN_SIZE_X + SIZE_X;
	unit_.pos_.y = Application::SCREEN_SIZE_Y / 2.0f;

	state_ = (int)STATE::MOVE;

	moveInit_ = false;
	moveVec_ = { 0.0f,0.0f };

	deathCou_ = 0;

	ChangeMotion((int)MOTION::IDLE);

	unit_.hp_ = HP_MAX;

	reverse_ = false;
	angle_ = Utility::Deg2RadF(180.0f);

	end_ = false;

	tackle_->Init();
	sumi_->Init();
}

void Kraken::OnCollision(UnitBase* other)
{

	if (dynamic_cast<EnemyBase*>(other)) {
		HpDecrease(5);
		return;
	}

	if (dynamic_cast<PlayerLaser*>(other)) {
		HpDecrease(5);
		return;
	}

	if (dynamic_cast<Sphere*>(other)) {
		HpDecrease(5);
		return;
	}

}

void Kraken::HpDecrease(int damage)
{
	GameScene::Slow(20);
	GameScene::Shake();

	ChangeMotion((int)MOTION::DAMAGE, false);
	animCounter_ = 1;

	Smng::GetIns().Play(SOUND::BLAST, true);

	unit_.hp_ -= damage;
	if (unit_.hp_ <= 0) {
		unit_.hp_ = 0;
		state_ = (int)STATE::DEATH;
		ChangeMotion((int)MOTION::DAMAGE);
		deathCou_ = 0;
	}

	unit_.inviciCounter_ = 10;

	if (enCount_) { state_ = (int)STATE::MOVE; unit_.inviciCounter_ = 10; }
}


std::vector<UnitBase*> Kraken::AttackIns(void)
{
	std::vector<UnitBase*> ret;

	for (auto& ins : sumi_->Sumis()) { ret.emplace_back(ins); }

	return ret;
}

bool Kraken::Timer(void)
{
	if (state_ == (int)STATE::DEATH) { return false; }
	return true;
}

void Kraken::Idle(void)
{
	if (--idleTime_ <= 0) {
		idleTime_ = 0;
		state_ = (int)STATE::MOVE;
	}
}

void Kraken::Move(void)
{
#pragma region à⁄ìÆèÛë‘Ç÷ëJà⁄å„ ÇPâÒñ⁄ÇÃèàóù
	if (!moveInit_) {
		auto destinationRotyly = [&](void)->Vector2 {
			Vector2 ret = {};
			float sub = 100000.0f;

			for (int i = 0; i < DESTINATION_POS_NUM; i++) {
				if (sub > (DESTINATION_TABLE[i] - playerPos_).Length() &&
					destination_ != DESTINATION_TABLE[i]) {
					sub = (DESTINATION_TABLE[i] - playerPos_).Length();
					ret = DESTINATION_TABLE[i];
				}
			}
			return ret;
			};

		destination_ = destinationRotyly();

		moveVec_ = destination_ - unit_.pos_;
		if (moveVec_ != 0.0f) {
			moveVec_ = Utility::Normalize(moveVec_) * unit_.para_.speed;
			angle_ = atan2f(moveVec_.y, moveVec_.x);
		}

		moveInit_ = true;
	}
#pragma endregion
#pragma region à⁄ìÆèàóù
	unit_.pos_ += moveVec_;
	ChangeMotion((int)MOTION::MOVE);
#pragma endregion
#pragma region à⁄ìÆèIóπîªíË çUåÇèÛë‘Ç÷ëJà⁄
	if ((destination_ - unit_.pos_).Abs() <= unit_.para_.speed / 2) {
		state_ = (int)STATE::ATTACK;
		attackInit_ = false;

		ChangeMotion((int)MOTION::IDLE);

		angle_ = Utility::VecToAngle(playerPos_ - unit_.pos_);

		moveInit_ = false;
	}
#pragma endregion
}

void Kraken::Attack(void)
{
#pragma region çUåÇèÛë‘Ç÷ëJà⁄å„ ÇPâÒñ⁄ÇÃèàóù
	if (!attackInit_) {

		idleTime_ = ATTACK_INTERVAL;

		attackInit_ = true;
		attackEnd_ = false;
		
		attackState_ = AttackLottery();
		switch (attackState_)
		{
		case Kraken::ATTACK_KINDS::NON:
			attackEnd_ = true;
			break;
		case Kraken::ATTACK_KINDS::TENTACLE:
			tentacle_->On();
			ChangeMotion((int)MOTION::ATTACK1,false);
			break;
		case Kraken::ATTACK_KINDS::SPHERE:
			sphere_->On();
			break;
		case Kraken::ATTACK_KINDS::SUMI:
			sumi_->On();
			ChangeMotion((int)MOTION::ATTACK1);
			break;
		case Kraken::ATTACK_KINDS::INVOLUTE:
			involute_->On();
			break;
		case Kraken::ATTACK_KINDS::TACKLE:
			tackle_->On();
			ChangeMotion((int)MOTION::SPECIAL);
			break;
		}
	}
#pragma endregion
#pragma region çUåÇèÛë‘íÜÇÃÇ›çsÇ§çXêVèàóù Ç‹ÇΩçUåÇèIóπîªíf
	switch (attackState_)
	{
	case Kraken::ATTACK_KINDS::NON:
		break;
	case Kraken::ATTACK_KINDS::TENTACLE:
		attackEnd_ = tentacle_->End();
		break;
	case Kraken::ATTACK_KINDS::SPHERE:
		attackEnd_ = true;
		break;
	case Kraken::ATTACK_KINDS::SUMI:
		angle_ = Utility::VecToAngle(playerPos_ - unit_.pos_);
		angle_ += Utility::Deg2RadF(180.0f);
		sumi_->Shot();
		if (sumi_->End()) { attackEnd_ = true; }
		break;
	case Kraken::ATTACK_KINDS::INVOLUTE:
		if (involute_->End()) { attackEnd_ = true; }
		break;
	case Kraken::ATTACK_KINDS::TACKLE:
		if (tackle_->GetState() == KrakenTackle::STATE::NON) { attackEnd_ = true; }
		break;
	}
#pragma endregion
#pragma region çUåÇèIóπ í èÌèÛë‘Ç÷ëJà⁄
	if (attackEnd_) {
		idleTime_ = ATTACK_INTERVAL;
		state_ = (int)STATE::IDLE;
		ChangeMotion((int)MOTION::IDLE);
	}
#pragma endregion
}

void Kraken::Damage(void)
{
	// É_ÉÅÅ[ÉWÉÇÅ[ÉVÉáÉìÇ™èIÇÌÇ¡ÇΩÇÁèÛë‘Ç‡ñﬂÇ∑
	if (motion_ != (int)MOTION::DAMAGE) {
		state_ = (int)STATE::MOVE;
	}
}

void Kraken::Death(void)
{
	if (++deathCou_ >= DEATH_PERFOR_TIME) {
		deathCou_ = 0;
		unit_.isAlive_ = false;
		end_ = true;
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
		Smng::GetIns().Play(SOUND::GAME_END);
	}
}

Kraken::ATTACK_KINDS Kraken::AttackLottery(void)
{
	//return ATTACK_KINDS::INVOLUTE;

	ATTACK_KINDS ret = ATTACK_KINDS::NON;

	int maxRand = 10000;
	int rand = GetRand(maxRand);

	int hpDife = 0;

	float hpRaitio = (float)unit_.hp_ / (float)HP_MAX;
	if (hpRaitio > 0.6f) { hpDife = 0; }
	else if (hpRaitio > 0.3f) { hpDife = 1; }
	else { hpDife = 2; }

	auto probaSorty = [&](int i)->int {
		int ret = 0;
		for (; i >= 0; i--) {
			ret += maxRand * ATTACK_PROBABILITY_TABLE[hpDife][i];
		}
		return ret;
		};

	for (int i = 0; i < (int)ATTACK_KINDS::MAX; i++) {
		if (rand <= probaSorty(i)) {
			ret = (ATTACK_KINDS)i;
			break;
		}
	}

	return ret;
}

void Kraken::AttackUpdate(void)
{
	tentacle_->Update();
	sphere_->Update();
	sumi_->Update();
	involute_->Update();
	tackle_->Update();
}

void Kraken::AttackDraw(void)
{
	tentacle_->Draw();
	sphere_->Draw();
	sumi_->Draw();
	involute_->Draw();
	tackle_->Draw();
}

void Kraken::AttackRelease(void)
{
	if (tentacle_) {
		tentacle_->Release();
		delete tentacle_;
		tentacle_ = nullptr;
	}
	if (sphere_) {
		sphere_->Release();
		delete sphere_;
		sphere_ = nullptr;
	}
	if (sumi_) {
		sumi_->Release();
		delete sumi_;
		sumi_ = nullptr;
	}
	if (involute_) {
		involute_->Release();
		delete involute_;
		involute_ = nullptr;
	}
	if (tackle_) {
		delete tackle_;
		tackle_ = nullptr;
	}
}

