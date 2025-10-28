#pragma once

#include"../../../../../Common/Vector2.h"

class KrakenTackle
{
public:
	static constexpr float TACKLE_SPEED = 15.0f;

	KrakenTackle(Vector2& pos,float& angle, const Vector2& playerPos);
	~KrakenTackle();

	void Init(void);
	void Update(void);
	void Draw(void);

	void On(void);

	enum class STATE
	{
		NON,
		RUNUP,
		RUN,

		MAX
	};

	STATE GetState(void) { return state_; }

private:
	STATE state_;

	using STATEFUNC = void (KrakenTackle::*)(void);
	STATEFUNC stateFuncPtr[(int)STATE::MAX];

	void Non(void) {}
	void RunUp(void);
	void Run(void);

	Vector2 targetPos_;

	const int ATTACK_NUM = 3;
	int attackCount_;

	const int RUN_UP_TIME = 60;
	int runUpCounter_;

	void Set(void);

	Vector2& pos;
	float& angle;
	const Vector2& playerPos;
};