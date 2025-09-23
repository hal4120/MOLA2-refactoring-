#pragma once

#include "../UnitBase.h"

#include"../../Application/Application.h"

class EnemyBase : public UnitBase
{
public:
	enum NUMBER { ONE, TWO, THREE, FOUR, FIVE, MAX };

	const Vector2 RES_POS[NUMBER::MAX] =
	{
		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 1 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 2 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 3 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 4 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)},

		{Application::SCREEN_SIZE_X + (unit_.para_.size.x / 2.0f),
		(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 5 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)}
	};

	static constexpr float PARRY_SPEED = 20.0f;

	EnemyBase(NUMBER num);
	virtual ~EnemyBase() {};

	virtual void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	virtual void OnCollision(UnitBase* other)override;

	bool GetParry(void) { return parry_; }

protected:
	// �摜
	std::vector<int>imgs_;

	// �摜�\���{��
	float drawScale_;

	// �ԍ�
	NUMBER number_;

	// �A�j���[�V�����֌W
	int animSpeed;
	int animCounter_;
	int animInterval_;
	void Animation(void);

	// ���X�|�[���֌W
	int respawnCounter_;
	int respawnTime;
	void Respawn(void);

	// �ړ�
	Vector2 moveVec_;
	virtual void Move(void);

	// �p���B�\�����֌W
	int arrowImg_;
	float arrowAngle_;
	bool arrow_;

	// �p���B����Ă��邩�ǂ���
	bool parry_;

};

using NUMBER = EnemyBase::NUMBER;