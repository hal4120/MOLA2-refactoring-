#include"BossBase.h"

#include<DxLib.h>

#include"../../Application/Application.h"

#include"../../Manager/Sound/SoundManager.h"

BossBase::BossBase(const Vector2& playerPos) :
	playerPos_(playerPos),
	state_(0),
	stateFuncPtr(),
	SCALE(1.0f),
	reverse_(false),

	drawCenter_(0.0f,0.0f),

	motion_(),
	animCounter_(),
	animInterval_(),
	animLoop_(),
	enCount_(true),

	totalAngle_(0.0f),
	angle_(0.0f),
	ofsetAngle_(0.0f),

	maxHP(-1),
	end_(false)
{
	unit_.para_.colliType = CollisionType::ENEMY;
}

BossBase::~BossBase()
{
}


void BossBase::Update(void)
{
	AttackUpdate();

	Invi();
	if (enCount_) { EnCount(); }
	else { (this->*stateFuncPtr[state_])(); }
	totalAngle_ = angle_ + ofsetAngle_;

	Animation();
}

void BossBase::Draw(void)
{
	AttackDraw();

	if (!unit_.isAlive_) { return; }
	DrawRotaGraph3F(unit_.pos_.x, unit_.pos_.y, drawCenter_.x, drawCenter_.y, SCALE, SCALE, totalAngle_, imgs_.at((int)motion_).at(animCounter_), true, reverse_);


	// “–‚½‚è”»’è‚Ì•`‰æ‚Ìƒ‰ƒ€ƒ_ŠÖ”
	auto DrawDebug = [&](void)->void {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		switch (unit_.para_.colliShape)
		{
		case CollisionShape::CIRCLE:
			DrawCircleAA(unit_.pos_.x, unit_.pos_.y, unit_.para_.radius, 30, 0xffffff);
			break;
		case CollisionShape::RECTANGLE:
			DrawBoxAA(unit_.pos_.x - unit_.para_.size.x / 2, unit_.pos_.y - unit_.para_.size.y / 2, unit_.pos_.x + unit_.para_.size.x / 2, unit_.pos_.y + unit_.para_.size.y / 2, 0xffffff, true);
			break;
		case CollisionShape::ELLIPSE:
			DrawOvalAA(unit_.pos_.x, unit_.pos_.y, unit_.para_.size.x / 2, unit_.para_.size.y / 2, 30, 0xffffff, true);
			break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		};
	// “–‚½‚è”»’è‚Ì•`‰æ
	DrawDebug();

}

void BossBase::Release(void)
{
	AttackRelease();

	for (auto& imgs : imgs_) {
		for (auto& img : imgs) { DeleteGraph(img); }
	}
}

void BossBase::ChangeMotion(int motion, bool loop)
{
	animLoop_ = loop;
	if (loop && motion_ == motion) { return; }
	motion_ = motion;
	animCounter_ = 0;
	animInterval_ = 0;
}

void BossBase::Animation(void)
{
	if (++animInterval_ >= ANIM_INTERVAL) {
		animInterval_ = 0;
		if (++animCounter_ >= imgs_[motion_].size()) {
			if (animLoop_) {
				animCounter_ = 0;
			}
			else {
				ChangeMotion(0);
			}
		}
	}
}

void BossBase::EnCount(void)
{
	unit_.pos_.x -= 2.0f;

	Smng::GetIns().Play(SOUND::WARNING, false, 200, true);

	if (unit_.para_.radius != -1) {
		if (unit_.pos_.x + unit_.para_.radius <= Application::SCREEN_SIZE_X) {
			enCount_ = false; 
			Smng::GetIns().Stop(SOUND::WARNING);
			Smng::GetIns().Play(SOUND::BGM_BOSS, true, 150, true);
		}
	}

	if (unit_.para_.size.x != -1) {
		if (unit_.pos_.x + unit_.para_.size.x / 2 <= Application::SCREEN_SIZE_X) {
			enCount_ = false; 
			Smng::GetIns().Stop(SOUND::WARNING);
			Smng::GetIns().Play(SOUND::BGM_BOSS, true, 150, true);
		}
	}
}

void BossBase::DrawHp(unsigned int mainColor, unsigned int backColor, unsigned int frameColor)
{
	const Vector2I screen = { Application::SCREEN_SIZE_X,Application::SCREEN_SIZE_Y };
	Vector2 size = { 800.0f,50.0f };
	Vector2 sPos = { screen.x - (size.x + 5.0f),5.0f };

	DrawBoxAA(sPos.x, sPos.y, sPos.x + size.x, sPos.y + size.y, frameColor, true);

	float frameSize = 3.0f;

	size -= frameSize * 2.0f;
	sPos += frameSize;

	float oneSize = size.x / maxHP;

	DrawBoxAA(sPos.x, sPos.y, sPos.x + size.x, sPos.y + size.y, backColor, true);
	DrawBoxAA(sPos.x, sPos.y, sPos.x + (oneSize * unit_.hp_), sPos.y + size.y, mainColor, true);
}
