#pragma once

#include "../UnitBase.h"

#include"../../Application/Application.h"

class EnemyBase : public UnitBase
{
public:
	enum class DIR { UP, DOWN, LEFT, RIGHT, MAX };
	enum NUMBER { ONE, TWO, THREE, FOUR, FIVE, MAX };

	const Vector2 RES_POS[(int)DIR::MAX][NUMBER::MAX] =
	{
		{
			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 1 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			0.0f - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 2 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			0.0f - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 3 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			0.0f - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 4 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			0.0f - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 5 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			0.0f - (unit_.para_.size.y / 2.0f)},
		},
		{
			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 1 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			Application::SCREEN_SIZE_Y - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 2 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			Application::SCREEN_SIZE_Y - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 3 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			Application::SCREEN_SIZE_Y - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 4 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			Application::SCREEN_SIZE_Y - (unit_.para_.size.y / 2.0f)},

			{(Application::SCREEN_SIZE_X / NUMBER::MAX) * 5 - (Application::SCREEN_SIZE_X / NUMBER::MAX / 2),
			Application::SCREEN_SIZE_Y - (unit_.para_.size.y / 2.0f)},
		},
		{
			{0.0f - (unit_.para_.size.x / 2.0f),
			(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 1 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)	},

			{0.0f - (unit_.para_.size.x / 2.0f),
			(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 2 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)	},

			{0.0f - (unit_.para_.size.x / 2.0f),
			(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 3 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)	},

			{0.0f - (unit_.para_.size.x / 2.0f),
			(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 4 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)	},

			{0.0f - (unit_.para_.size.x / 2.0f),
			(Application::SCREEN_SIZE_Y / NUMBER::MAX) * 5 - (Application::SCREEN_SIZE_Y / NUMBER::MAX / 2)}
		},
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
		}
	};

	const Vector2 MOVE_VEC_TABLE[(int)DIR::MAX] =
	{
		{0.0f,1.0f},
		{0.0f,-1.0f},
		{1.0f,0.0f},
		{-1.0f,0.0f}
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
	// 画像
	std::vector<int>imgs_;

	// 画像表示倍率
	float drawScale_;

	// 番号
	NUMBER number_;

	DIR dir_;

	// アニメーション関係
	int animSpeed;
	int animCounter_;
	int animInterval_;
	void Animation(void);

	// リスポーン関係
	int respawnCounter_;
	int respawnTime;
	virtual void Respawn(void);

	// 移動
	Vector2 moveVec_;
	virtual void Move(void);

	// パリィ予測矢印関係
	int arrowImg_;
	float arrowAngle_;
	bool arrow_;

	// パリィされているかどうか
	bool parry_;

};

using NUMBER = EnemyBase::NUMBER;