#pragma once

#include"../../../../UnitBase.h"

class Tentacle : public UnitBase
{
public:
	Tentacle();
	~Tentacle();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	const Base& GetUnit(void)const { return unit_; }

	void OnCollision(UnitBase* other)override;
private:



};