#include"KrakenTackle.h"

#include"../../Kraken.h"
#include"../../../../Player/Player.h"

KrakenTackle::KrakenTackle(Vector2& pos, float& angle, const Vector2& playerPos):
	pos(pos),
	angle(angle),
	playerPos(playerPos),

	state_(STATE::NON),
	stateFuncPtr(),

	attackCount_(0)
{
}

KrakenTackle::~KrakenTackle()
{
}

void KrakenTackle::Init(void)
{
#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(STATE::NON, &KrakenTackle::Non);
	SET_STATE(STATE::RUNUP, &KrakenTackle::RunUp);
	SET_STATE(STATE::RUN, &KrakenTackle::Run);
	
	state_ = STATE::NON;
}

void KrakenTackle::Update(void)
{
	if (state_ == STATE::NON) { return; }

	(this->*stateFuncPtr[(int)state_])();
}

void KrakenTackle::Draw(void)
{
	if (state_ == STATE::NON) { return; }

	if (state_ == STATE::RUNUP && (runUpCounter_ / 10 % 2) == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		Vector2 pos1 = pos + (Vector2(sinf(angle), cosf(angle)).Vertical().Normalize() * 50.0f);
		Vector2 pos2 = pos + (-Vector2(sinf(angle), cosf(angle)).Vertical().Normalize() * 50.0f);
		Vector2 pos3 = targetPos_ + (-Vector2(sinf(angle), cosf(angle)).Vertical().Normalize() * 50.0f);
		Vector2 pos4 = targetPos_ + (Vector2(sinf(angle), cosf(angle)).Vertical().Normalize() * 50.0f);
		DrawQuadrangleAA(
			pos1.x, pos1.y,
			pos2.x, pos2.y,
			pos3.x, pos3.y,
			pos4.x, pos4.y,
			0xff0000, true);
		DrawCircleAA(targetPos_.x, targetPos_.y, 50, 20, 0xff0000);
		DrawCircleAA(pos.x, pos.y, 50, 20, 0xff0000);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}


void KrakenTackle::RunUp(void)
{
	if (++runUpCounter_ > RUN_UP_TIME) {
		runUpCounter_ = 0;
		state_ = STATE::RUN;
	}
}

void KrakenTackle::Run(void)
{
	Vector2 vec = targetPos_ - pos;
	pos += (vec.Normalize() * TACKLE_SPEED);

	// –Ú•W“ž’…
	if ((targetPos_ - pos).Length() < TACKLE_SPEED) {
		if (++attackCount_ < ATTACK_NUM) {
			// Œp‘±
			Set();
		}
		else {
			// I—¹
			state_ = STATE::NON;
		}
	}
}

void KrakenTackle::On(void)
{
	attackCount_ = 0;
	Set();
}
void KrakenTackle::Set(void)
{
	runUpCounter_ = 0;

	targetPos_ = playerPos;
	Vector2 vec = targetPos_ - pos;
	vec.Normalized();
	angle = Utility::VecToAngle(vec);

	state_ = STATE::RUNUP;
}
