#pragma once
#include"Sumi.h"
#include<vector>

class SumiShooter
{
public:
	static constexpr int ONE_SHOT_NUM = 3;							//1回で出す個数
	static constexpr int SHOT_NUM = 10;								//打つ回数
	static constexpr int ALL_SHOT_NUM = ONE_SHOT_NUM * SHOT_NUM;	//合計で出す個数

	static constexpr float DEFAULT_ANGLE = DX_PI_F;
	static constexpr float SHOT_DIFF = 15 * (DX_PI_F / 180.0f);

	static constexpr int SHOT_INTERVAL = 10;	//フレーム

	SumiShooter(const Vector2& bossPos, const float& bossAngle, const Vector2& playerPos);
	~SumiShooter();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void On(void) { shot_ = true; shotCount_ = 0; }
	const bool End(void)const { return !shot_; }

	std::vector<Sumi*>Sumis(void) { return ikuras_; }

	void Shot(void);
private:
	int img_;
	std::vector<Sumi*>ikuras_;

	const Vector2& bossPos_;
	const float& bossAngle_;
	const Vector2& playerPos_;

	bool shot_;
	int shotCount_;
	int interval_;
	int searchCount_;
};
