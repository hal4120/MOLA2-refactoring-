#include"InvoluteShooter.h"

#include<string>

#include"../../../../../Manager/Collision/Collision.h"

InvoluteShooter::InvoluteShooter(const Vector2& bossPos, const float& bossAngle):
	bossPos(bossPos),
	bossAngle(bossAngle),

	image_(),
	involute_(),

	shotCount_(0),
	shotInterval_(0)
{
}

InvoluteShooter::~InvoluteShooter()
{
}

void InvoluteShooter::Load(void)
{
	std::string path = "Data/Image/Boss/Kraken/Attack/Involute/";
	for (int i = 1; i <= ANIME_NUM; i++) {
		image_.emplace_back(Utility::LoadImg((path + std::to_string(i)).c_str()));
	}
}

void InvoluteShooter::Update(void)
{
	if (shotCount_ > 0) { Shot(); }
	for (auto& i : involute_) { i->Update(); }
}

void InvoluteShooter::Draw(void)
{
	for (auto& i : involute_) { i->Draw(); }
}

void InvoluteShooter::Release(void)
{
	for (auto& i : involute_) {
		if (!i) { continue; }
		i->Release();
		delete i;
		i = nullptr;
	}
	involute_.clear();

	for (auto& id : image_) { DeleteGraph(id); }
}

void InvoluteShooter::Shot(void)
{
	if (++shotInterval_ > SHOT_INTERVAL) {
		shotInterval_ = 0;

		if (--shotCount_ < 0) { shotCount_ = 0; }

		bool recycle = false;

		for (auto& i : involute_) {
			if (i->GetUnit().isAlive_) { continue; }
			recycle = true;

		}

		if (recycle) { return; }

		involute_.emplace_back(new Involute(image_));
		involute_.back()->Load();
		involute_.back()->Init();

		Collision::Add(involute_.back());
	}
}
