#include"Tentacle.h"

#include"../../../../../Application/Application.h"
#include"../../../../../Scene/Game/GameScene.h"

Tentacle::Tentacle(int image, const float& playerPosX) :
	image_(image),
	playerPosX(playerPosX),

	stateFuncPtr(),
	
	warningCounter_(0),
	stretchIdleCou_(0)
{
}

Tentacle::~Tentacle()
{
}

void Tentacle::Load(void)
{
#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::NON, &Tentacle::Non);
	SET_STATE(STATE::WARNING, &Tentacle::Warning);
	SET_STATE(STATE::STRETCH, &Tentacle::Stretch);
	SET_STATE(STATE::RETURN, &Tentacle::Return);
}

void Tentacle::Init(void)
{
	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.para_.colliShape = CollisionShape::RECTANGLE;
	unit_.para_.size = { SIZE_X * 0.75f,SIZE_Y * 0.9f };

	unit_.para_.center = { 0.0f,SIZE_Y / 2 };

	unit_.para_.speed = 30.0f;
}

void Tentacle::Update(void)
{
	(this->*stateFuncPtr[(int)state_])();
}

void Tentacle::Draw(void)
{
	if (unit_.isAlive_ == false) { return; }

	if (state_ == STATE::WARNING && (warningCounter_ / 10 % 2) == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawBoxAA(unit_.pos_.x - unit_.para_.size.x / 2, 0.0f, unit_.pos_.x + unit_.para_.size.x / 2, Application::SCREEN_SIZE_Y, 0xff0000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, SIZE_X / 2, 0.0f, 1, 1, 0, image_, true);
}

void Tentacle::Release(void)
{
}

void Tentacle::OnCollision(UnitBase* other)
{
}

void Tentacle::On(void)
{
	unit_.pos_ = { playerPosX,START_POS_Y };
	state_ = STATE::WARNING;
	warningCounter_ = WARNING_TIME;
	stretchIdleCou_ = STRETCH_IDLE_TIME;

	unit_.isAlive_ = true;

	end_ = false;
}

void Tentacle::Warning(void)
{
	if (--warningCounter_ <= 0) {
		warningCounter_ = 0;
		state_ = STATE::STRETCH;
	}
}

void Tentacle::Stretch(void)
{
	if (unit_.pos_.y < 0) {
		unit_.pos_.y += unit_.para_.speed;
		if (unit_.pos_.y >= 0) { GameScene::Shake(); end_ = true; }
	}
	else {
		if (--stretchIdleCou_ <= 0) {
			stretchIdleCou_ = 0;
			state_ = STATE::RETURN;
		}
	}
}

void Tentacle::Return(void)
{
	unit_.pos_.y -= unit_.para_.speed * 0.5f;
	if (unit_.pos_.y < START_POS_Y) {
		unit_.isAlive_ = false;
		state_ = STATE::NON;
	}
}
