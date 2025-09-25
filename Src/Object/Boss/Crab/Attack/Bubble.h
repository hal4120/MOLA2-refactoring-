#pragma once
#include "../../../UnitBase.h"

class Bubble : public UnitBase
{
	static constexpr int SIZE = 20;
	static constexpr float SPEED = 8.0f;

	Bubble(int img);
	~Bubble();

	void Load(void)override;
	void Init(void)override {};
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override {};

	void Shot(Vector2 pos, Vector2 vec) {
		unit_.isAlive_ = true;
		unit_.pos_ = pos;
		moveVec_ = vec;
	}

	void OnCollision(UnitBase* other)override;

private:
	int img_;
	Vector2 moveVec_;
};