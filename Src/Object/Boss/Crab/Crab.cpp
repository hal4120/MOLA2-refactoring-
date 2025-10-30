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

	mode_ = MODE::NORMAL;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::MOVE, &Crab::Move);
	SET_STATE(STATE::ATTACK, &Crab::Attack);
	SET_STATE(STATE::DAMAGE, &Crab::Damage);
	SET_STATE(STATE::DEATH, &Crab::Death);
	SET_STATE(STATE::IDLE, &Crab::Idle);

#pragma region �U���̃��[�h

	bubble_ = new BubbleShooter(unit_.pos_, playerPos_);
	bubble_->Load();

	scissor_ = new Scissors(unit_.pos_, playerPos_);
	scissor_->Load();

	fire_ = new FireBall(unit_.pos_, playerPos_);
	fire_->Load();

	burst_ = new Burst(playerPos_);
	burst_->Load();

#pragma endregion
}

void Crab::Init(void)
{
	unit_.isAlive_ = true;

	// �{�X�̏����ʒu
	unit_.pos_ = DESTINATION[DESTINATION_PLACE::UNDER_RIGHT];
	nextDestPlace_ = DESTINATION_PLACE::UNDER_LEFT;

	state_ = (int)STATE::IDLE;

	moveVec_ = { 0.0f, 0.0f };

	deathCou_ = 0;

	ChangeMotion((int)MOTION::IDLE);

	unit_.hp_ = HP_MAX;

	WhichDir(DIR::LEFT);

	angle_ = 0.0f;

	end_ = false;

#pragma region �U���̏�����
	bubble_->Init();
	scissor_->Init();
	//fire_->Init();
	//burst_->Init();
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

	if (dynamic_cast<Scissors*>(other)) {
		HpDecrease(7);
	}

	if (dynamic_cast<FireBall*> (other)) {
		HpDecrease(7);
	}

	if (dynamic_cast<Burst*>(other)) {
		HpDecrease(5);
		unit_.inviciCounter_ = 10;
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

void Crab::DestinationLottery(void)
{

}

std::vector<UnitBase*> Crab::AttackIns(void)
{
	std::vector<UnitBase*> ret;

	for (auto& ins : bubble_->Bubbles()) { ret.emplace_back(ins); }
	ret.emplace_back(scissor_);
	ret.emplace_back(fire_);
	ret.emplace_back(burst_);
	return ret;
}

bool Crab::Timer(void)
{
	if (state_ == (int)STATE::DEATH) { return false; }
	return true;
}

void Crab::Idle(void)
{
	static int cnt = 0;

	ChangeMotion((int)MOTION::IDLE);

	cnt++;
	if (cnt > 60) {
		state_ = (int)STATE::MOVE;
		cnt = 0;
	}
}

void Crab::Move(void)
{	
	Vector2 target = DESTINATION[nextDestPlace_];
	Vector2 moveDir = { target.x - unit_.pos_.x, target.y - unit_.pos_.y };

	float len = Utility::Magnitude(moveDir);

	if (len > 1.0f)
	{
		// ���K��
		moveDir /= len;

		// ��ԂŊ��炩�ɕ����]��
		moveVec_ = moveVec_ * 0.9f + moveDir * 0.1f;

		// �ړ�
		unit_.pos_ += moveVec_ * unit_.para_.speed;

		// �c�ړ��̂Ƃ�������]
		if ((nextDestPlace_ == DESTINATION_PLACE::TOP_RIGHT) ||
			(nextDestPlace_ == DESTINATION_PLACE::TOP_LEFT) ||
			(nextDestPlace_ == DESTINATION_PLACE::UNDER_RIGHT) ||
			(nextDestPlace_ == DESTINATION_PLACE::UNDER_LEFT))
		{
			// �c�����̈ړ��͈�
			float bottomY = Application::SCREEN_SIZE_Y - SIZE_Y / 2;
			float topY = SIZE_Y / 2;

			// �i�s�x 0.0 (��) �� 1.0 (��)
			float t = (bottomY - unit_.pos_.y) / (bottomY - topY);

			if (t < 0.0f) {
				t = 0.0f;
			}
			else if (t > 1.0f) {
				t = 1.0f;
			}

			if (moveVec_.y < 0) {
				// ������Ɉړ����i�� �� ��j
				angle_ = DX_PI_F * t;  // �� ���̋t�i�����v���j
			}
			else {
				// �������Ɉړ����i�� �� ���j
				angle_ = -DX_PI_F * t; // �� ���̋t�i���v���j
			}
		}

		ChangeMotion((int)MOTION::MOVE);
	}
	else
	{
		// ��������
		unit_.pos_ = target;

		switch (nextDestPlace_)
		{
		case DESTINATION_PLACE::UNDER_RIGHT:
			nextDestPlace_ = DESTINATION_PLACE::UNDER_LEFT;
			WhichDir(DIR::LEFT);
			angle_ = 0.0f; // ���͒ʏ����
			break;

		case DESTINATION_PLACE::UNDER_LEFT:
			nextDestPlace_ = DESTINATION_PLACE::TOP_LEFT;
			WhichDir(DIR::RIGHT);
			angle_ = 0.0f; // ���͒ʏ����
			break;

		case DESTINATION_PLACE::TOP_RIGHT:
			nextDestPlace_ = DESTINATION_PLACE::UNDER_RIGHT;
			WhichDir(DIR::RIGHT);
			angle_ = DX_PI_F; // ��͋t����
			break;

		case DESTINATION_PLACE::TOP_LEFT:
			nextDestPlace_ = DESTINATION_PLACE::TOP_RIGHT;
			WhichDir(DIR::LEFT);
			angle_ = DX_PI_F; // ��͋t����
			break;
		}

		unit_.para_.speed = MOVE_SPEED;
		state_ = (int)STATE::ATTACK;
	}
}

void Crab::Attack(void)
{

	switch (mode_)
	{
	case Crab::MODE::NORMAL:
		//�U���̏�����
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
			case Crab::ATTACK_KINDS::SCISSOR:
				scissor_->Init();
				ChangeMotion((int)MOTION::ATTACK2);
				break;
			case Crab::ATTACK_KINDS::FIRE:
				fire_->Init();
				ChangeMotion((int)MOTION::ATTACK2);
				break;
			case Crab::ATTACK_KINDS::LIGHTNING:
				burst_->Init();
				break;
			case Crab::ATTACK_KINDS::MAX:
				break;
			}
		}


		//�U���̏I������
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
		case Crab::ATTACK_KINDS::SCISSOR:
			if (scissor_->End()) {
				attackEnd_ = true;
			}
			break;
		case Crab::ATTACK_KINDS::FIRE:
			if (fire_->End()) {
				attackEnd_ = true;
			}
			break;
		case Crab::ATTACK_KINDS::LIGHTNING:
			if (burst_->End()) {
				attackEnd_ = true;
			}
			break;
		case Crab::ATTACK_KINDS::MAX:
			break;
		}

		//�U�����I�������A�C�h���Ɉڍs
		if (attackEnd_) {
			state_ = (int)STATE::IDLE;
			attackInit_ = false;
		}
		break;
	case Crab::MODE::HARD:
		//�U���̏�����
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
				burst_->Init();
				ChangeMotion((int)MOTION::ATTACK3);
				break;
			case Crab::ATTACK_KINDS::SCISSOR:
				fire_->Init();
				bubble_->Init();
				scissor_->Init();
				ChangeMotion((int)MOTION::ATTACK2);
				break;
			case Crab::ATTACK_KINDS::FIRE:
				fire_->Init();
				bubble_->Init();
				ChangeMotion((int)MOTION::ATTACK2);
				break;
				//case Crab::ATTACK_KINDS::LIGHTNING:
				//	burst_->Init();
				//	break;
				//case Crab::ATTACK_KINDS::MAX:
				//	break;
			}
		}
		//�U���̏I������
		switch (attackState_)
		{
		case Crab::ATTACK_KINDS::NON:
			break;
		case Crab::ATTACK_KINDS::BUBBLE:
			bubble_->Shot();
			if (bubble_->End() || burst_->End()) {
				attackEnd_ = true;
			}
			break;
		case Crab::ATTACK_KINDS::SCISSOR:
			bubble_->Shot();
			if (scissor_->End() || fire_->End() || bubble_->End()) {
				attackEnd_ = true;
			}
			break;
		case Crab::ATTACK_KINDS::FIRE:
			if (fire_->End() || bubble_->End()) {
				attackEnd_ = true;
			}
			break;
			//case Crab::ATTACK_KINDS::LIGHTNING:
			//	if (burst_->End()) {
			//		attackEnd_ = true;
			//	}
			//	break;
			//case Crab::ATTACK_KINDS::MAX:
			//	break;
		}

		//�U�����I�������A�C�h���Ɉڍs
		if (attackEnd_) {
			state_ = (int)STATE::IDLE;
			attackInit_ = false;
		}
		break;
	}

}

void Crab::Damage(void)
{
	// �_���[�W���[�V�������I��������Ԃ��߂�
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

// �ǂ̌����������Ă��邩
void Crab::WhichDir(DIR dir)
{
	reverse_ = (int)dir;

	if (reverse_)
	{
		drawCenter_ = REVERSE_DRAW_CENTER_POS;
	}
	else
	{
		drawCenter_ = DRAW_CENTER_POS;
	}

	switch (nextDestPlace_)
	{
	case DESTINATION_PLACE::UNDER_RIGHT:
		angle_ = 0.0f; // ���͒ʏ����
		break;
	case DESTINATION_PLACE::UNDER_LEFT:
		angle_ = 0.0f; // ���͒ʏ����
		break;
	case DESTINATION_PLACE::TOP_RIGHT:
		angle_ = DX_PI_F; // ��͋t����
		break;
	case DESTINATION_PLACE::TOP_LEFT:
		angle_ = DX_PI_F; // ��͋t����
		break;
	}
}

Crab::ATTACK_KINDS Crab::AttackLottery(void)
{
	ATTACK_KINDS ret;

	if (unit_.hp_ > HP_MAX / 3) {
		ret = (ATTACK_KINDS)GetRand((int)ATTACK_KINDS::MAX - 1);
	}
	else {
		ret = (ATTACK_KINDS)GetRand((int)ATTACK_KINDS::MAX - 2);
	}
	//ret = ATTACK_KINDS::LIGHTNING;

	return ret;
}

void Crab::AttackUpdate(void)
{
	if (unit_.hp_ > HP_MAX / 2)
	{
		mode_ = MODE::NORMAL;
	}
	else
	{
		static bool is = false;
		if (!is) {
			is = true;
			attackEnd_ = true;
		}
		mode_ = MODE::HARD;
	}
	bubble_->Update();
	scissor_->Update();
	fire_->Update();
	burst_->Update();
}

void Crab::AttackDraw(void)
{
	bubble_->Draw();
	scissor_->Draw();
	fire_->Draw();
	burst_->Draw();
}

void Crab::AttackRelease(void)
{
	if (bubble_) {
		bubble_->Release();
		delete bubble_;
		bubble_ = nullptr;
	}

	if (scissor_) {
		scissor_->Release();
		delete scissor_;
		scissor_ = nullptr;
	}

	if (fire_) {
		fire_->Release();
		delete fire_;
		fire_ = nullptr;
	}

	if (burst_) {
		burst_->Release();
		delete burst_;
		burst_ = nullptr;
	}
}
