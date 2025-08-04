#include"IkuraShooter.h"

#include"../../Shark.h"

IkuraShooter::IkuraShooter(const Vector2& bossPos):
	bossPos_(bossPos),
	img_(),
	ikuras_(),
	shot_(false),
	shotCount_(0),
	interval_(),
	searchCount_()
{
}

IkuraShooter::~IkuraShooter()
{
}

void IkuraShooter::Load(void)
{
	Utility::LoadImg(img_, "Data/Image/Boss/Shark/Attack/Ikura/Ikura.png");
	ikuras_.reserve(ALL_SHOT_NUM);
	for (int i = 0; i < ALL_SHOT_NUM; i++) {
		ikuras_.emplace_back(new Ikura(img_));
		ikuras_[ikuras_.size() - 1]->Load();
	}
}

void IkuraShooter::Init(void)
{
	shot_ = false;
	shotCount_ = 0;
	interval_ = 0;
	searchCount_ = 0;
}


void IkuraShooter::Update(void)
{
	Shot();
	for (auto& ikura : ikuras_) { ikura->Update(); }
}

void IkuraShooter::Draw(void)
{
	for (auto& ikura : ikuras_) { ikura->Draw(); }
}

void IkuraShooter::Release(void)
{
	for (auto& ikura : ikuras_) { delete ikura; ikura = nullptr; }
	ikuras_.clear();
	DeleteGraph(img_);
}

void IkuraShooter::Shot(void)
{
	if (!shot_) { return; }

	if (interval_ > 0) { interval_--; return; }

	searchCount_ = 0;
	for (auto& ikura : ikuras_) {
		if (ikura->GetUnit().isAlive_) { continue; }
		searchCount_++;
	}
	if (searchCount_ < ONE_SHOT_NUM) { shot_ = false; return; }


	Vector2 position = bossPos_;
	position.x -= Shark::SIZE_X / 2.0f;

	float angle = DEFAULT_ANGLE;
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