#pragma once

#include "../../../../UnitBase.h"

class Tornado : public UnitBase
{
public:

	Tornado();
	~Tornado() override;

	void Load(void) override;
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

	void OnCollision(UnitBase* other) override;

private:

};