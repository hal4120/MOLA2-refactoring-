#pragma once

#include"../../../Common/Vector2.h"
class TitleMonkfish
{
public:
	static constexpr int NUM = 5;

	TitleMonkfish();
	~TitleMonkfish();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:
	int img_;

	const Vector2I POS[NUM] =
	{
		{200,150},
		{400,200},
		{600,600},
		{1200,100},
		{1200,600}
	};

	float angle_[NUM];
};