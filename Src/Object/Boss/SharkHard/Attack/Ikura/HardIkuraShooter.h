#pragma once
#include"HardIkura.h"
#include<vector>

class HardIkuraShooter
{
public:
	static constexpr int ONE_SHOT_NUM = 9;							//1回で出す個数
	static constexpr int SHOT_NUM = 20;								//打つ回数
	static constexpr int ALL_SHOT_NUM = ONE_SHOT_NUM * SHOT_NUM;	//合計で出す個数

	static constexpr float DEFAULT_ANGLE =  DX_PI_F;
	static constexpr float SHOT_DIFF = 15 * (DX_PI_F / 180.0f);

	static constexpr int SHOT_INTERVAL = 10;	//フレーム

	HardIkuraShooter(const Vector2& bossPos);
	~HardIkuraShooter();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void On(void) { shot_ = true; shotCount_ = 0; }
	const bool End(void)const { return !shot_; }

	std::vector<HardIkura*>Ikuras(void) { return ikuras_; }

	void Shot(void);
private:
	int img_;
	std::vector<HardIkura*>ikuras_;

	const Vector2& bossPos_;

	bool shot_;
	int shotCount_;
	int interval_;
	int searchCount_;
};

