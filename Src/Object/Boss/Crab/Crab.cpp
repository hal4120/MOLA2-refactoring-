#include "Crab.h"

#include <DxLib.h>

#include"../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../Application/Application.h"
#include"../../../Scene/SceneManager/SceneManager.h"
#include"../../../Manager/Sound/SoundManager.h"
#include"../../../Scene/Game/GameScene.h"

#include"../../Enemy/EnemyBase.h"

Crab::Crab(const Vector2& playerPos) :
	BossBase(playerPos),
	moveVec_(),
	deathCou_(0)
{
}

Crab::~Crab()
{
}

void Crab::Load(void)
{
	imgs_.resize((int)MOTION::MAX);
	for (int i = 0; i < (int)MOTION::MAX; i++) {
		Utility::LoadArrayImg(MOTION_PATH[i], MOTION_NUM[i], MOTION_NUM[i], 1, LOAD_SIZE, LOAD_SIZE, imgs_[i]);
	}

	unit_.para_.speed = MOVE_SPEED;

	BossBase::SCALE = this->SCALE;

	unit_.para_.size.x = SIZE_X;
	unit_.para_.size.y = SIZE_Y;
	unit_.para_.radius = SIZE_X;
	drawCenter_ = DRAW_CENTER_POS;

	maxHP = HP_MAX;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::MOVE, &Crab::Move);
	SET_STATE(STATE::ATTACK, &Crab::Attack);
	SET_STATE(STATE::DAMAGE, &Crab::Damage);
	SET_STATE(STATE::DEATH, &Crab::Death);

#pragma region 攻撃のロード



#pragma endregion
}

void Crab::Init(void)
{
	unit_.isAlive_ = true;

	unit_.pos_.x = Application::SCREEN_SIZE_X + SIZE_X;
	unit_.pos_.y = Application::SCREEN_SIZE_Y - SIZE_Y / 2;

	state_ = (int)STATE::MOVE;

	moveVec_ = { 0.0f, 0.0f };

	deathCou_ = 0;

	ChangeMotion((int)MOTION::ATTACK4);

	unit_.hp_ = HP_MAX;

	reverse_ = true;
	angle_ = 0.0f;

	end_ = false;

#pragma region 攻撃の初期化

#pragma endregion
}

void Crab::OnCollision(UnitBase* other)
{
	if (dynamic_cast<EnemyBase*>(other))
	{
		HpDecrease(5);
		return;
	}
}

void Crab::HpDecrease(int damage)
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
		ChangeMotion((int)MOTION::DEATH);
		deathCou_ = 0;
	}

	if (enCount_) 
	{ 
		state_ = (int)STATE::MOVE; unit_.inviciCounter_ = 10;
	}
}

std::vector<UnitBase*> Crab::AttackIns(void)
{
	std::vector<UnitBase*> ret;

	//for (auto& ins : sumi_->Sumis()) { ret.emplace_back(ins); }

	return ret;
}

bool Crab::Timer(void)
{
	if (state_ == (int)STATE::DEATH) { return false; }
	return true;
}

void Crab::Move(void)
{
}

void Crab::Attack(void)
{
	if (!attackInit_)
	{
		attackInterval_ = ATTACK_INTERVAL;
		attackInit_ = true;
		attackEnd_ = false;

		attackState_ = AttackLottery();

		switch (attackState_)
		{
		case Crab::ATTACK_KINDS::NON:
			break;
		case Crab::ATTACK_KINDS::MAX:
			break;
		}
	}
}

void Crab::Damage(void)
{
	// ダメージモーションが終わったら状態も戻す
	if (motion_ != (int)MOTION::DAMAGE) {
		state_ = (int)STATE::MOVE;
	}
}

void Crab::Death(void)
{

}
void Crab::AttackUpdate(void)
{
}

void Crab::AttackDraw(void)
{
}

void Crab::AttackRelease(void)
{
}
