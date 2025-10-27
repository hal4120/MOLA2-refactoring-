#include"SphereShooter.h"

#include"../../../../../Utility/Utility.h"

#include"../../../../../Manager/Collision/Collision.h"

SphereShooter::SphereShooter(const Vector2& bossPos, const float& bossAngle, const Vector2& playerPos) :
	bossPos_(bossPos),
	bossAngle_(bossAngle),
	playerPos_(playerPos),

	spheres_()
{
}

SphereShooter::~SphereShooter()
{
}

void SphereShooter::Load(void)
{
	spheres_.reserve(5);

	int load[ANIME_NUM];
	Utility::LoadArrayImg("Data/Image/Boss/Kraken/Attack/Sphere/Csphere.png", ANIME_NUM, ANIME_NUM, 1, 60, 60, load);
	image_.insert(image_.end(), load, load + ANIME_NUM);

}

void SphereShooter::Update(void)
{
	for (auto& s : spheres_) { s->Update(); }
}

void SphereShooter::Draw(void)
{
	for (auto& s : spheres_) { s->Draw(); }
}

void SphereShooter::Release(void)
{
	for (auto& s : spheres_) {
		if (!s) { continue; }
		s->Release();
		delete s;
	}
	spheres_.clear();

	for (auto& id : image_) { DeleteGraph(id); }
}

void SphereShooter::On(void)
{
	bool recycle = false;

	for (auto& s : spheres_) {
		if (s->GetUnit().isAlive_ == false) {
			s->On();
			recycle = true;
			break;
		}
	}

	if (recycle) { return; }

	spheres_.emplace_back(new Sphere(image_, bossPos_, bossAngle_, playerPos_));
	spheres_.back()->Load();
	spheres_.back()->Init();
	spheres_.back()->On();
	Collision::Add(spheres_.back());
}
