#pragma once
#include<vector>
#include"HardUni.h"

class HardUniShooter
{
public:
	static constexpr int NUM = 7;

	HardUniShooter();
	~HardUniShooter();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	std::vector<HardUni*>Unis(void) { return unis_; }

	void Shot(Vector2 target);

	bool End(void) {
		bool ret = true;
		for (auto& uni : unis_) {
			if (uni->GetState() == HardUni::STATE::SUMMON) { ret = false; break; }
		}
		return ret;
	}

private:
	std::vector<HardUni*>unis_;

	int img_[(int)HardUni::IMG_NUM::MAX];

	Vector2 target_;

	int reticleImg_;
	bool isReticle_;
	float reticleFloat_;

	int arrowImg_;
	
	const Vector2 POINT[NUM] = {
		{1000.0f,100.0f},
		{1000.0f,480.0f},
		{1000.0f,860.0f},
		{200.0f,100.0f},
		{200.0f,860.0f},
		{600.0f,100.0f},
		{600.0f,860.0f}
	};
};
