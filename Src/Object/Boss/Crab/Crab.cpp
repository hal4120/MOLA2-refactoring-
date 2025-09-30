#include "Crab.h"

#include <DxLib.h>

#include"../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../Scene/SceneManager/SceneManager.h"
#include"../../../Manager/Sound/SoundManager.h"
#include"../../../Scene/Game/GameScene.h"

#include"../../Enemy/EnemyBase.h"
#include"../../Player/Special/PlayerLaser.h"

Crab::Crab(const Vector2& playerPos) :
	BossBase(playerPos),
	moveVec_(),
	deathCou_(0),
	bubble_()
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
	drawCenter_ = REVERSE_DRAW_CENTER_POS;

	maxHP = HP_MAX;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::MOVE, &Crab::Move);
	SET_STATE(STATE::ATTACK, &Crab::Attack);
	SET_STATE(STATE::DAMAGE, &Crab::Damage);
	SET_STATE(STATE::DEATH, &Crab::Death);

#pragma region 攻撃のロード

	bubble_ = new BubbleShooter(unit_.pos_, playerPos_);
	bubble_->Load();

#pragma endregion
}

void Crab::Init(void)
{
	unit_.isAlive_ = true;

	// ボスの初期位置
	unit_.pos_ = DESTINATION[DESTINATION_PLACE::UNDER_RIGHT];
	nextDestPlace_ = DESTINATION_PLACE::UNDER_LEFT;

	state_ = (int)STATE::MOVE;

	moveVec_ = { 0.0f, 0.0f };

	deathCou_ = 0;

	ChangeMotion((int)MOTION::IDLE);

	unit_.hp_ = HP_MAX;

	isReverse(true);

	angle_ = 0.0f;

	end_ = false;

#pragma region 攻撃の初期化
	bubble_->Init();
#pragma endregion
}

void Crab::OnCollision(UnitBase* other)
{
	if (dynamic_cast<EnemyBase*>(other))
	{
		HpDecrease(5);
		return;
	}

	if (dynamic_cast<PlayerLaser*>(other))
	{
		HpDecrease(3);
		unit_.inviciCounter_ = 5;
		return;
	}
}

void Crab::HpDecrease(int damage)
{
	GameScene::Slow(20);
	GameScene::Shake();

	//state_ = (int)STATE::DAMAGE;
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

	for (auto& ins : bubble_->Bubbles()) { ret.emplace_back(ins); }
	return ret;
}

bool Crab::Timer(void)
{
	if (state_ == (int)STATE::DEATH) { return false; }
	return true;
}

void Crab::Move(void)
{	
	Vector2 target = DESTINATION[nextDestPlace_];
	Vector2 dir = { target.x - unit_.pos_.x, target.y - unit_.pos_.y };

	float len = sqrtf(dir.x * dir.x + dir.y * dir.y);

	if (len > 1.0f)
	{
		// 正規化
		dir.x /= len;
		dir.y /= len;

		// 補間で滑らかに方向転換
		moveVec_.x = moveVec_.x * 0.9f + dir.x * 0.1f;
		moveVec_.y = moveVec_.y * 0.9f + dir.y * 0.1f;

		// 移動
		unit_.pos_.x += moveVec_.x * unit_.para_.speed;
		unit_.pos_.y += moveVec_.y * unit_.para_.speed;

		// ★縦移動のときだけ回転
		if ((nextDestPlace_ == DESTINATION_PLACE::TOP_RIGHT) ||
			(nextDestPlace_ == DESTINATION_PLACE::TOP_LEFT) ||
			(nextDestPlace_ == DESTINATION_PLACE::UNDER_RIGHT) ||
			(nextDestPlace_ == DESTINATION_PLACE::UNDER_LEFT))
		{
			// 縦方向の移動範囲
			float bottomY = Application::SCREEN_SIZE_Y - SIZE_Y / 2;
			float topY = SIZE_Y / 2;

			// 進行度 0.0 (下) → 1.0 (上)
			float t = (bottomY - unit_.pos_.y) / (bottomY - topY);
			if (t < 0.0f) t = 0.0f;
			else if (t > 1.0f) t = 1.0f;

			// 下 → 上へ移動中は逆回転（0 → -π）
			angle_ = -DX_PI_F * t;
		}

		ChangeMotion((int)MOTION::MOVE);
	}
	else
	{
		// 到着処理
		unit_.pos_ = target;

		switch (nextDestPlace_)
		{
		case DESTINATION_PLACE::UNDER_RIGHT:
			nextDestPlace_ = DESTINATION_PLACE::UNDER_LEFT;
			isReverse(true);
			angle_ = 0.0f; // 下は通常向き
			break;

		case DESTINATION_PLACE::UNDER_LEFT:
			nextDestPlace_ = DESTINATION_PLACE::UNDER_RIGHT;
			isReverse(false);
			angle_ = 0.0f; // 下は通常向き
			break;

		case DESTINATION_PLACE::TOP_RIGHT:
			nextDestPlace_ = DESTINATION_PLACE::TOP_LEFT;
			isReverse(false);
			angle_ = DX_PI_F; // 上は逆さま
			break;

		case DESTINATION_PLACE::TOP_LEFT:
			nextDestPlace_ = DESTINATION_PLACE::TOP_RIGHT;
			isReverse(true);
			angle_ = DX_PI_F; // 上は逆さま
			break;
		}

		unit_.para_.speed = MOVE_SPEED;
		state_ = (int)STATE::ATTACK;
	}
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
		case Crab::ATTACK_KINDS::BUBBLE:
			bubble_->Init();
			ChangeMotion((int)MOTION::ATTACK3);
			break;
		case Crab::ATTACK_KINDS::MAX:
			break;
		}
	}

	switch (attackState_)
	{
	case Crab::ATTACK_KINDS::NON:
		break;
	case Crab::ATTACK_KINDS::BUBBLE:
		 bubble_->Shot();
    if (bubble_->End()) {
        attackEnd_ = true;
    }
		break;
	case Crab::ATTACK_KINDS::MAX:
		break;
	}

	if (attackEnd_) {
		state_ = (int)STATE::MOVE;
		attackInit_ = false;
	}


	// デバック用処理
	if (CheckHitKey(KEY_INPUT_1)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::UNDER_RIGHT; }
	if (CheckHitKey(KEY_INPUT_2)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::UNDER_LEFT; }
	if (CheckHitKey(KEY_INPUT_3)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::TOP_RIGHT; }
	if (CheckHitKey(KEY_INPUT_4)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::TOP_LEFT; }
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

void Crab::isReverse(bool isReverse)
{
	reverse_ = isReverse;

	if (reverse_)
	{
		drawCenter_ = REVERSE_DRAW_CENTER_POS;
	}
	else
	{
		drawCenter_ = DRAW_CENTER_POS;
	}
}

void Crab::AttackUpdate(void)
{
	bubble_->Update();
}

void Crab::AttackDraw(void)
{
	bubble_->Draw();
}

void Crab::AttackRelease(void)
{
	bubble_->Release();
}
