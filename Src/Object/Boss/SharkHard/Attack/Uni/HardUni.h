#pragma once
#include"../../../../UnitBase.h"

class HardUni : public UnitBase
{
public:
	static constexpr float SCALE = 0.2f;
	static constexpr int LOAD_SIZE = 320;
	static constexpr int SIZE = (int)(LOAD_SIZE * SCALE);

	static constexpr float SPEED = 5.0f;
	static constexpr float REFLECTION_SPEED = 20.0f;

	static constexpr int SUMMON_TIME = 100;
	static constexpr int BLAST_TIME = 10;

	enum class IMG_NUM {
		SUMMON,
		UNI,

		MAX
	};
	enum STATE {
		NON=-1,
		SUMMON,
		THROWN,
		REFLECTION,
		BLAST,

		MAX
	};


	HardUni(int* img,int arrowImg);
	~HardUni();

	void Load(void)override;
	void Init(void)override {};
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override {};

	void On(Vector2 pos, Vector2 target);

	void OnCollision(UnitBase* other)override;

	const STATE GetState(void)const { return state_; }
private:
	int img_[(int)IMG_NUM::MAX];
	IMG_NUM imgState_;

	STATE state_;
	void (HardUni::* stateFuncPtr[STATE::MAX])(void);
	void Non(void) {};
	void Summon(void);
	void Thrown(void);
	void Reflection(void);
	void Blast(void);

	Vector2 target_;
	Vector2 moveVec_;

	float angle_;

	int counter_;

	int arrowImg_;
	float arrowAngle_;
	bool arrow_;

};