#pragma once

#include"../../../../UnitBase.h"

class Tentacle : public UnitBase
{
public:
	static constexpr int SIZE_X = 210;
	static constexpr int SIZE_Y = 1380;

	Tentacle(int image,const float& playerPosX);
	~Tentacle();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other)override;

	bool End(void) { return end_; }

	void On(void);

	enum class STATE { NON, WARNING, STRETCH, RETURN, MAX };
private:
	int image_;

	STATE state_;

	using STATEFUNC = void (Tentacle::*)(void);
	STATEFUNC stateFuncPtr[(int)STATE::MAX];

	void Non(void) {}
	void Warning(void);
	void Stretch(void);
	void Return(void);

	const int WARNING_TIME = 120;
	int warningCounter_;

	const int STRETCH_IDLE_TIME = 50;
	int stretchIdleCou_;

	bool end_;

	const float START_POS_Y = -SIZE_Y;
	const float& playerPosX;
};