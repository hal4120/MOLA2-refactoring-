#pragma once

#include<vector>
#include"Sphere.h"

class SphereShooter
{
public:
	static constexpr int ANIME_NUM = 9;

	SphereShooter(const Vector2& bossPos, const float& bossAngle, const Vector2& playerPos);
	~SphereShooter();

	void Load(void);
	void Update(void);
	void Draw(void);
	void Release(void);
	void On(void);


private:
	std::vector<int> image_;
	std::vector<Sphere*>spheres_;

	const Vector2& bossPos_;
	const float& bossAngle_;
	const Vector2& playerPos_;
};