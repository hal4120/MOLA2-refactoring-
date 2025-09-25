#pragma once
#include"../UnitBase.h"
#include<map>
class BossBase : public UnitBase
{
public:
	static constexpr int ANIM_INTERVAL = 5;

	BossBase(const Vector2& playerPos);
	virtual ~BossBase();

	virtual void Load(void)override = 0;
	virtual void Init(void)override = 0;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	bool End(void) { return end_; }

	virtual std::vector<UnitBase*>AttackIns(void) = 0;

	void DrawHp(unsigned int mainColor, unsigned int backColor, unsigned int frameColor);

	const int GetState(void)const { return state_; }

	virtual bool Timer(void) = 0;

	const bool GetEnCount(void)const { return enCount_; }

protected:
	int state_;
	using STATEFUNC = void (BossBase::*)(void);
	std::map<int,STATEFUNC>stateFuncPtr;

	const Vector2& playerPos_;

	std::vector<std::vector<int>>imgs_;
	float SCALE;
	bool reverse_;

	Vector2 drawCenter_;

	int motion_;
	int animCounter_;
	int animInterval_;
	bool animLoop_;
	void ChangeMotion(int motion, bool loop = true);
	void Animation(void);


	bool enCount_;
	void EnCount(void);

	int maxHP;

	float angle_;

	bool end_;

	virtual void AttackUpdate(void) = 0;
	virtual void AttackDraw(void) = 0;
	virtual void AttackRelease(void) = 0;
};
