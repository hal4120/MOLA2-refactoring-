#include"SumiShooter.h"

#include"../../Kraken.h"

#include"../../../../../Manager/Sound/SoundManager.h"

SumiShooter::SumiShooter(const Vector2& bossPos, const float& bossAngle, const Vector2& playerPos) :
	bossPos_(bossPos),
	bossAngle_(bossAngle),
	playerPos_(playerPos),
	img_(),
	ikuras_(),
	shot_(false),
	shotCount_(0),
	interval_(),
	searchCount_()
{
}

SumiShooter::~SumiShooter()
{
}

void SumiShooter::Load(void)
{
	Utility::LoadImg(img_, "Data/Image/Boss/Kraken/Attack/Sumi/Sumi.png");
	ikuras_.reserve(ALL_SHOT_NUM);
	for (int i = 0; i < ALL_SHOT_NUM; i++) {
		ikuras_.emplace_back(new Sumi(img_));
		ikuras_[ikuras_.size() - 1]->Load();
	}

	Smng::GetIns().Load(SOUND::IKURA);
}

void SumiShooter::Init(void)
{
	shot_ = false;
	shotCount_ = 0;
	interval_ = 0;
	searchCount_ = 0;
}


void SumiShooter::Update(void)
{
	for (auto& ikura : ikuras_) { ikura->Update(); }
}

void SumiShooter::Draw(void)
{
	for (auto& ikura : ikuras_) { ikura->Draw(); }
}

void SumiShooter::Release(void)
{
	Smng::GetIns().Delete(SOUND::IKURA);
	for (auto& ikura : ikuras_) { delete ikura; ikura = nullptr; }
	ikuras_.clear();
	DeleteGraph(img_);
}

void SumiShooter::Shot(void)
{
	if (!shot_) { return; }

	if (interval_ > 0) { interval_--; return; }

	searchCount_ = 0;
	for (auto& ikura : ikuras_) {
		if (ikura->GetUnit().isAlive_) { continue; }
		searchCount_++;
	}
	if (searchCount_ < ONE_SHOT_NUM) { shot_ = false; return; }


	MATRIX mat = MGetIdent();
	mat = MMult(mat, MGetRotZ(bossAngle_));
	VECTOR ofset = VTransform({ -Kraken::SIZE_X / 2.0f,0.0f,0.0f }, mat);
	Vector2 position = bossPos_ + Vector2(ofset.x, ofset.y);

	Vector2 vec = playerPos_ - position;

	float angle = atan2f(vec.y, vec.x);
	angle += SHOT_DIFF * (ONE_SHOT_NUM / 2);

	for (int i = 0; i < ONE_SHOT_NUM; i++) {
		for (auto& ikura : ikuras_) {
			if (ikura->GetUnit().isAlive_) { continue; }
			ikura->Shot(position, { cosf(angle), sinf(angle) });
			shotCount_++;
			break;
		}
		angle -= SHOT_DIFF;
	}
	interval_ = SHOT_INTERVAL;

	if (shotCount_ >= ALL_SHOT_NUM) { shot_ = false; }
}