#pragma once

#include"../BossBase.h"

class IkuraShooter;

class Shark : public BossBase
{
public:
	static constexpr int LOAD_SIZE = 96;
	static constexpr float SCALE = 4.0f;
	static constexpr float SIZE_X = LOAD_SIZE * SCALE;
	static constexpr float SIZE_Y = (LOAD_SIZE * SCALE) / 2.0f;

	enum class MOTION { MOVE, ATTACK, SPECIAL, DAMAGE, DEATH, MAX };
	static constexpr const char* MOTION_PATH[(int)MOTION::MAX] =
	{
		"Data/Image/Boss/Shark/Walk.png",
		"Data/Image/Boss/Shark/Attack1.png",
		"Data/Image/Boss/Shark/Special.png",
		"Data/Image/Boss/Shark/Hurt.png",
		"Data/Image/Boss/Shark/Hurt.png"
	};
	static constexpr int MOTION_NUM[(int)MOTION::MAX] = { 6,6,6,2,2 };


	static constexpr int HP_MAX = 100;

	enum class STATE { MOVE, ATTACK, DAMAGE, DEATH, MAX };

	static constexpr float MOVE_SPEED = 5.0f;

	static constexpr int DEATH_PERFOR_TIME = 180;

	static constexpr int ATTACK_INTERVAL = 300;

	Shark();
	~Shark();

	void Load(void)override;
	void Init(void)override;

	void OnCollision(UnitBase* other)override;

	std::vector<UnitBase*>AttackIns(void)override;

private:
	// èÛë‘ï ä÷êî------------------------------------------
	void Move(void);
	void Attack(void);
	void Damage(void);
	void Death(void);
	//-----------------------------------------------------

	Vector2 moveVec_;

	int attackInterval_;
	bool attackInit_;
	bool attackEnd_;

	int deathCou_;

	enum class ATTACK_KINDS
	{
		NON = -1,
		IKURA,

		MAX
	};
	ATTACK_KINDS attackState_;
	ATTACK_KINDS AttackLottery(void);

	IkuraShooter* ikura_;

	// çUåÇóp-----------------
	void AttackUpdate(void);
	void AttackDraw(void);
	void AttackRelease(void);
	//------------------------
};