#pragma once
#include"../UnitBase.h"
#include<map>
class BossBase : public UnitBase
{
public:
	static constexpr int ANIM_INTERVAL = 5;

	BossBase();
	virtual ~BossBase();

	virtual void Load(void)override = 0;
	virtual void Init(void)override = 0;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;


	virtual std::vector<UnitBase*>AttackIns(void) = 0;

protected:
	int state_;
	using STATEFUNC = void (BossBase::*)(void);
	std::map<int,STATEFUNC>stateFuncPtr;


	std::vector<std::vector<int>>imgs_;
	float SCALE;
	bool reverse_;

	int motion_;
	int animCounter_;
	int animInterval_;
	bool animLoop_;
	void ChangeMotion(int motion, bool loop = true);
	void Animation(void);

	float angle_;


	virtual void AttackUpdate(void) = 0;
	virtual void AttackDraw(void) = 0;
	virtual void AttackRelease(void) = 0;
};
