#pragma once

#include"../../UnitBase.h"

class Shark : public UnitBase
{
public:
	static constexpr int LOAD_SIZE = 96;
	static constexpr float SCALE = 4.0f;
	static constexpr float SIZE_X = LOAD_SIZE * SCALE;
	static constexpr float SIZE_Y = (LOAD_SIZE * SCALE) / 2.0f;

	enum class MOTION { MOVE, ATTACK, SPECIAL, DAMAGE, DEATH, MAX };
	const std::string MOTION_PATH[(int)MOTION::MAX] =
	{
		"Data/Image/Boss/Shark/Walk.png",
		"Data/Image/Boss/Shark/Attack1png",
		"Data/Image/Boss/Shark/Special.png",
		"Data/Image/Boss/Shark/Hurt.png",
		"Data/Image/Boss/Shark/Hurt.png"
	};
	static constexpr int MOTION_NUM[(int)MOTION::MAX] = { 6,6,6,2,2 };

	static constexpr int ANIM_INTERVAL = 5;

	static constexpr int HP_MAX = 100;

	enum class STATE { MOVE, ATTACK, DAMAGE, DEATH, MAX };

	static constexpr float MOVE_SPEED = 5.0f;

	Shark();
	~Shark();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other);

private:
	// èÛë‘ä÷åW--------------------------------------------
	STATE state_;
	void(Shark::* stateFuncPtr[(int)STATE::MAX])(void);
	void Move(void);
	void Attack(void);
	void Damage(void);
	void Death(void);
	//-----------------------------------------------------

	Vector2 moveVec_;

	// ÉÇÅ[ÉVÉáÉìä÷åW-------------------------------------
	std::vector<int>imgs_[(int)MOTION::MAX];
	MOTION motion_;
	int animCounter_;
	int animInterval_;
	bool animLoop_;
	void ChangeMotion(MOTION motion, bool loop = true);
	void Animation(void);
	//-----------------------------------------------------
};