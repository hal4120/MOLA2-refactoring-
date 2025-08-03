#pragma once

#include"../../UnitBase.h"

class Shark : public UnitBase
{
public:
	enum STATE { MOVE, ATTACK, MAX };

	Shark();
	~Shark();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	std::vector<std::vector<int>>imgs_;

	STATE state_;

};