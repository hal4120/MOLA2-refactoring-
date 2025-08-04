#pragma once
#include"Ikura.h"
#include<vector>

class IkuraShooter
{
public:
	static constexpr int ONE_SHOT_NUM = 5;							//1回で出す個数
	static constexpr int SHOT_NUM = 10;								//打つ回数
	static constexpr int ALL_SHOT_NUM = ONE_SHOT_NUM * SHOT_NUM;	//合計で出す個数

	static constexpr float DEFAULT_ANGLE =  DX_PI_F;
	static constexpr float SHOT_DIFF = 20 * (DX_PI_F / 180.0f);

	static constexpr int SHOT_INTERVAL = 10;	//フレーム

	IkuraShooter(const Vector2& bossPos);
	~IkuraShooter();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void On(void) { shot_ = true; shotCount_ = 0; }
	const bool End(void)const { return !shot_; }

	std::vector<Ikura*>Ikuras(void) { return ikuras_; }

private:
	int img_;
	std::vector<Ikura*>ikuras_;

	const Vector2& bossPos_;

	bool shot_;
	int shotCount_;
	int interval_;
	int searchCount_;
	void Shot(void);
};

