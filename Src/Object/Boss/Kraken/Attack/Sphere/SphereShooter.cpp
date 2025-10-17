#include"SphereShooter.h"

#include"../../../../../Utility/Utility.h"

SphereShooter::SphereShooter():
	spheres_()
{
}

SphereShooter::~SphereShooter()
{
}

void SphereShooter::Load(void)
{
	spheres_.reserve(5);

	Utility::LoadArrayImg("Data/Image/Boss/Kraken/Sphere.png", ANIME_NUM, ANIME_NUM, 1, 64, 64, image_);
}

void SphereShooter::Init(void)
{
}

void SphereShooter::Update(void)
{
}

void SphereShooter::Draw(void)
{
}

void SphereShooter::Release(void)
{
}

void SphereShooter::On(void)
{
}
