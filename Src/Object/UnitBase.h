#pragma once

#include"../Common/Vector2.h"

#include"../Utility/Utility.h"

struct Base
{
	//パラメーター
	struct {
		enum CollisionPara { NON = -1, CIRCLE, RECT, ELLIPSE, CAPSULE, MAX };
		CollisionPara colliType_ = CollisionPara::NON;	//当たり判定の属性
		Vector2 size = { -1.0f,-1.0f };					//サイズ
		float radius_ = -1.0f;							//半径
		Vector2 center = { 0.0f,0.0f };					//中心
		float speed_ = -1;								//スピード
	}para_;

	// 生存フラグ
	bool isAlive_ = false;

	// 座標
	Vector2 pos_ = { -1.0f,-1.0f };

	// ヒットポイント
	int hp_ = -1;

	// 無敵判定
	bool isInvici_ = false;
	int inviciCounter_ = 0;
};

class UnitBase
{
public:
	UnitBase();
	virtual ~UnitBase();

	virtual void Load(void) = 0;
	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;

	const Base GetUnit(void)const { return unit_; }

protected:
	Base unit_;
};

