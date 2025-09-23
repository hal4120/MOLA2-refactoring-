#include "HardSharkTackle.h"

#include"../../../../../Application/Application.h"

#include"../../../../Player/Player.h"

HardSharkTackle::HardSharkTackle() :
	img_(),
	animeCounter_(0),
	animeInterval_(0),
	end_(false),
	angle_(0.0f),
	moveVec_(),
	standByCounter_(0),
	state_(DIR_STATE::NON),
	reverse_(true),
	stateFuncPtr(),
	parry_(false)
{
}

HardSharkTackle::~HardSharkTackle()
{
}

void HardSharkTackle::Load(void)
{
	Utility::LoadArrayImg("Data/Image/Boss/Shark/Special.png", ANIME_NUM, ANIME_NUM, 1, LOAD_SIZE, LOAD_SIZE, img_);


	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.para_.colliShape = CollisionShape::ELLIPSE;
	unit_.para_.size = { (float)SIZE_X,(float)SIZE_Y };

	unit_.para_.speed = MOVE_SPEED;

#define SET_STATE(state, func) stateFuncPtr[(int)(state)] = static_cast<STATEFUNC>(func)
	SET_STATE(DIR_STATE::NON, &HardSharkTackle::Non);
	SET_STATE(DIR_STATE::LEFT, &HardSharkTackle::LeftTackle);
	SET_STATE(DIR_STATE::UP, &HardSharkTackle::UpTackle);
	SET_STATE(DIR_STATE::DOWN, &HardSharkTackle::DownTackle);
	SET_STATE(DIR_STATE::RIGHT, &HardSharkTackle::RightTackle);

}

void HardSharkTackle::Init(void)
{
	state_ = DIR_STATE::NON;

	reverse_ = true;

	parry_ = false;
	end_ = false;
}

void HardSharkTackle::Update(void)
{
	if (state_ == DIR_STATE::NON) { unit_.isAlive_ = false; }
	else { unit_.isAlive_ = true; }

	Move();

	if (parry_) { ParryFunc(); }
	else { (this->*stateFuncPtr[(int)state_])(); }

	Animation();
}

void HardSharkTackle::Draw(void)
{
	if (!unit_.isAlive_) { return; }

	if (standByCounter_ < STAND_BY_TIME) {
		if (standByCounter_ / 10 % 2 == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			switch (state_)
			{
			case HardSharkTackle::DIR_STATE::LEFT:
			case HardSharkTackle::DIR_STATE::RIGHT:
				DrawBoxAA(0, unit_.pos_.y - (unit_.para_.size.y / 2), Application::SCREEN_SIZE_X, unit_.pos_.y + (unit_.para_.size.y / 2), 0xff0000, true);
				break;
			case HardSharkTackle::DIR_STATE::UP:
			case HardSharkTackle::DIR_STATE::DOWN:
				DrawBoxAA(unit_.pos_.x - (unit_.para_.size.x / 2), 0, unit_.pos_.x + (unit_.para_.size.x / 2), Application::SCREEN_SIZE_Y, 0xff0000, true);
				break;
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, DRAW_SCALE, angle_, img_[animeCounter_], true, reverse_);

}

void HardSharkTackle::Release(void)
{
	for (auto& id : img_) { DeleteGraph(id); }
}

void HardSharkTackle::OnCollision(UnitBase* other)
{
	if (!other->GetUnit().isAlive_) { return; }

	if (dynamic_cast<Parry*>(other)) {
		parry_ = true;

		Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
		moveVec_ = vec / sqrtf(vec.x * vec.x + vec.y * vec.y);

		unit_.para_.colliType = CollisionType::ALLY;
	}
}

void HardSharkTackle::Move(void)
{
	if (standByCounter_ < STAND_BY_TIME) {
		standByCounter_++;
	}
	else {
		unit_.pos_ += moveVec_ * unit_.para_.speed;
	}
}


void HardSharkTackle::LeftTackle(void)
{
	if (unit_.pos_.x + unit_.para_.size.x / 2 < 0.0f) {

		state_ = DIR_STATE::UP;
		moveVec_ = { 0.0f,-1.0f };
		standByCounter_ = 0;

		angle_ = Utility::Deg2RadF(90.0f);

		float work = unit_.para_.size.x;
		unit_.para_.size.x = unit_.para_.size.y;
		unit_.para_.size.y = work;

		unit_.pos_.y = Application::SCREEN_SIZE_Y + (unit_.para_.size.y / 2);
		unit_.pos_.x = ((float)GetRand(Application::SCREEN_SIZE_X - (int)(unit_.para_.size.x / 2)) + unit_.para_.size.x / 2);
	}
}

void HardSharkTackle::UpTackle(void)
{
	if (unit_.pos_.y + unit_.para_.size.y / 2 < 0.0f) {

		state_ = DIR_STATE::DOWN;
		moveVec_ = { 0.0f,1.0f };
		standByCounter_ = 0;

		angle_ = -Utility::Deg2RadF(90.0f);


		unit_.pos_.x = ((float)GetRand(Application::SCREEN_SIZE_X - (int)(unit_.para_.size.x / 2)) + unit_.para_.size.x / 2);
	}

}

void HardSharkTackle::DownTackle(void)
{
	if (unit_.pos_.y - unit_.para_.size.x / 2 > Application::SCREEN_SIZE_Y) {

		state_ = DIR_STATE::RIGHT;
		moveVec_ = { 1.0f,0.0f };
		standByCounter_ = 0;

		angle_ = 0.0f;

		reverse_ = false;

		float work = unit_.para_.size.x;
		unit_.para_.size.x = unit_.para_.size.y;
		unit_.para_.size.y = work;

		unit_.pos_.x = -(unit_.para_.size.x / 2);
		unit_.pos_.y = ((float)GetRand(Application::SCREEN_SIZE_Y - (int)(unit_.para_.size.y / 2)) + unit_.para_.size.y / 2);
	}
}

void HardSharkTackle::RightTackle(void)
{
	int x = Application::SCREEN_SIZE_X;

	if (unit_.pos_.x - unit_.para_.size.x / 2 > x) {

		state_ = DIR_STATE::NON;
		standByCounter_ = 0;
		end_ = true;
	}
}

void HardSharkTackle::ParryFunc(void)
{
	int x = Application::SCREEN_SIZE_X;
	int y = Application::SCREEN_SIZE_Y;

	angle_ += Utility::Deg2RadF(10.0f);

	if (unit_.pos_.x + unit_.para_.size.x / 2 < 0.0f ||
		unit_.pos_.x - unit_.para_.size.x / 2 > x ||
		unit_.pos_.y + unit_.para_.size.y / 2 < 0.0f ||
		unit_.pos_.y - unit_.para_.size.y / 2 > y)
	{
		parry_ = false;
		state_ = DIR_STATE::NON;
		standByCounter_ = 0;
		end_ = true;
	}

}

void HardSharkTackle::On(void)
{
	state_ = DIR_STATE::LEFT;
	moveVec_ = { -1.0f,0.0f };

	unit_.para_.size = { (float)SIZE_X,(float)SIZE_Y };

	reverse_ = true;
	standByCounter_ = 0;
	parry_ = false;

	angle_ = 0.0f;

	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.pos_.x = (float)Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2);
	unit_.pos_.y = ((float)GetRand(Application::SCREEN_SIZE_Y - (int)(unit_.para_.size.y / 2)) + unit_.para_.size.y / 2);
}


void HardSharkTackle::Animation(void)
{
	if (++animeInterval_ >= ANIME_INTERVAL) {
		animeInterval_ = 0;
		if (++animeCounter_ >= ANIME_NUM) {
			animeCounter_ = 0;
		}
	}
}