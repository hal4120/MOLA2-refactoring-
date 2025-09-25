#include "Crab.h"

#include <DxLib.h>

#include"../../../Manager/BlastEffect/BlastEffectManager.h"
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
	drawCenter_ = REVERSE_DRAW_CENTER_POS;

	maxHP = HP_MAX;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::MOVE, &Crab::Move);
	SET_STATE(STATE::ATTACK, &Crab::Attack);
	SET_STATE(STATE::DAMAGE, &Crab::Damage);
	SET_STATE(STATE::DEATH, &Crab::Death);

#pragma region �U���̃��[�h



#pragma endregion
}

void Crab::Init(void)
{
	unit_.isAlive_ = true;

	//unit_.pos_.x = Application::SCREEN_SIZE_X + SIZE_X;
	//unit_.pos_.y = Application::SCREEN_SIZE_Y - SIZE_Y / 2;

	// �{�X�̏����ʒu
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

#pragma region �U���̏�����

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
	Vector2 target = DESTINATION[nextDestPlace_];
	Vector2 dir = { target.x - unit_.pos_.x, target.y - unit_.pos_.y };

	float len = sqrtf(dir.x * dir.x + dir.y * dir.y);

	if (len > 1.0f)
	{
		// ���K��
		dir.x /= len;
		dir.y /= len;

		// ��ԂŊ��炩�ɕ����]��
		moveVec_.x = moveVec_.x * 0.9f + dir.x * 0.1f;
		moveVec_.y = moveVec_.y * 0.9f + dir.y * 0.1f;

		// �ړ�
		unit_.pos_.x += moveVec_.x * unit_.para_.speed;
		unit_.pos_.y += moveVec_.y * unit_.para_.speed;

		// ���c�ړ��̂Ƃ�������]
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
			if (t < 0.0f) t = 0.0f;
			else if (t > 1.0f) t = 1.0f;

			// �� �� ��ֈړ����͋t��]�i0 �� -�΁j
			angle_ = -DX_PI_F * t;
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
			isReverse(true);
			angle_ = 0.0f; // ���͒ʏ����
			break;

		case DESTINATION_PLACE::UNDER_LEFT:
			nextDestPlace_ = DESTINATION_PLACE::UNDER_RIGHT;
			isReverse(false);
			angle_ = 0.0f; // ���͒ʏ����
			break;

		case DESTINATION_PLACE::TOP_RIGHT:
			nextDestPlace_ = DESTINATION_PLACE::TOP_LEFT;
			isReverse(false);
			angle_ = DX_PI_F; // ��͋t����
			break;

		case DESTINATION_PLACE::TOP_LEFT:
			nextDestPlace_ = DESTINATION_PLACE::TOP_RIGHT;
			isReverse(true);
			angle_ = DX_PI_F; // ��͋t����
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
		case Crab::ATTACK_KINDS::MAX:
			break;
		}
	}

	// �f�o�b�N�p����
	if (CheckHitKey(KEY_INPUT_1)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::UNDER_RIGHT; }
	if (CheckHitKey(KEY_INPUT_2)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::UNDER_LEFT; }
	if (CheckHitKey(KEY_INPUT_3)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::TOP_RIGHT; }
	if (CheckHitKey(KEY_INPUT_4)) { state_ = (int)STATE::MOVE; nextDestPlace_ = DESTINATION_PLACE::TOP_LEFT; }
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
}

void Crab::AttackDraw(void)
{
}

void Crab::AttackRelease(void)
{
}
