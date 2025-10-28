#include"InvoluteShooter.h"

#include<string>

InvoluteShooter::InvoluteShooter():
	image_(),
	involute_()
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
	for (auto& i : involute_) { i->Update(); }
}

void InvoluteShooter::Draw(void)
{
	for (auto& i : involute_) { i->Draw(); }
}

void InvoluteShooter::Release(void)
{
	for (auto& id : image_) { DeleteGraph(id); }
}

void InvoluteShooter::On(void)
{
	for (int i = 0; i < ONE_SHOT_NUM; i++) {

		bool recycle = false;

		for (auto& i : involute_) {
			if (i->GetUnit().isAlive_) { continue; }
			recycle = true;

		}

		if (recycle) { continue; }

		involute_.emplace_back(new Involute(image_));
		involute_.back()->Load();
		involute_.back()->Init();

	}
}