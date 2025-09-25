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

	moveVec_(),

	deathCou_(0),

	sumi_(nullptr)
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

	maxHP = HP_MAX;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::MOVE, &Kraken::Move);
	SET_STATE(STATE::ATTACK, &Kraken::Attack);
	SET_STATE(STATE::DAMAGE, &Kraken::Damage);
	SET_STATE(STATE::DEATH, &Kraken::Death);

	sumi_ = new SumiShooter(unit_.pos_, playerPos_);
	sumi_->Load();
}

void Kraken::Init(void)
{
	unit_.isAlive_ = true;

	unit_.pos_.x = Application::SCREEN_SIZE_X + SIZE_X;
	unit_.pos_.y = Application::SCREEN_SIZE_Y / 2.0f;

	state_ = (int)STATE::MOVE;

	moveVec_ = { 0.0f,1.0f };

	deathCou_ = 0;

	ChangeMotion((int)MOTION::IDLE);

	unit_.hp_ = HP_MAX;

	reverse_ = false;
	angle_ = 0.0f;

	end_ = false;

	sumi_->Init();
}

void Kraken::OnCollision(UnitBase* other)
{

	if (dynamic_cast<EnemyBase*>(other)) {
		HpDecrease(5);
		return;
	}

}

void Kraken::HpDecrease(int damage)
{
	GameScene::Slow(20);
	GameScene::Shake();

	state_ = (int)STATE::DAMAGE;
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

void Kraken::Move(void)
{
	static int cou = 0;
	if (++cou > 200) {
		cou = 0;
		attackInit_ = false;
		state_ = (int)STATE::ATTACK;
	}
}

void Kraken::Attack(void)
{
#pragma region UŒ‚ó‘Ô‚Ö‘JˆÚŒã ‚P‰ñ–Ú‚Ìˆ—
	if (!attackInit_) {

		attackInterval_ = ATTACK_INTERVAL;
		attackInit_ = true;
		attackEnd_ = false;

		attackState_ = AttackLottery();
		switch (attackState_)
		{
		case Kraken::ATTACK_KINDS::NON:
			attackEnd_ = true;
			break;
		case Kraken::ATTACK_KINDS::SUMI:
			sumi_->On();
			ChangeMotion((int)MOTION::ATTACK1);
			break;
		case Kraken::ATTACK_KINDS::TACKLE:
			break;
		}
	}
#pragma endregion

#pragma region UŒ‚ó‘Ô’†‚Ì‚Ýs‚¤XVˆ— ‚Ü‚½UŒ‚I—¹”»’f
	switch (attackState_)
	{
	case Kraken::ATTACK_KINDS::SUMI:
		sumi_->Shot();
		if (sumi_->End()) { attackEnd_ = true; }
		break;
	case Kraken::ATTACK_KINDS::TACKLE:
		break;
	}
#pragma endregion

#pragma region UŒ‚I—¹ ’Êíó‘Ô‚Ö‘JˆÚ
	if (attackEnd_) {
		attackInterval_ = ATTACK_INTERVAL;
		state_ = (int)STATE::MOVE;
		ChangeMotion((int)MOTION::IDLE);
	}
#pragma endregion
}

void Kraken::Damage(void)
{
	// ƒ_ƒ[ƒWƒ‚[ƒVƒ‡ƒ“‚ªI‚í‚Á‚½‚çó‘Ô‚à–ß‚·
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

void Kraken::AttackUpdate(void)
{
	sumi_->Update();
}

void Kraken::AttackDraw(void)
{
	sumi_->Draw();
}

void Kraken::AttackRelease(void)
{
	if (sumi_) {
		sumi_->Release();
		delete sumi_;
		sumi_ = nullptr;
	}
}

