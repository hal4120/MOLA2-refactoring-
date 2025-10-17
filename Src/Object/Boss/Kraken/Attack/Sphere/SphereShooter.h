#pragma once

#include<vector>
#include"Sphere.h"

class SphereShooter
{
public:
	static constexpr int ANIME_NUM = 9;

	SphereShooter();
	~SphereShooter();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void On(void);

private:
	int image_[ANIME_NUM];
	std::vector<Sphere*>spheres_;
};