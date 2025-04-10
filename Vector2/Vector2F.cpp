#include<DxLib.h>
#include<time.h>
#include"Vector2F.h"
#include"../Application.h"

Vector2F::Vector2F()
{
	x = y = 0.0f;
}

Vector2F::Vector2F(float vX, float vY)
{
	x = vX;
	y = vY;
}

Vector2F::~Vector2F()
{
}

Vector2 Vector2F::ToVector2(void)
{
	Vector2 rvec;
	rvec.x = Application::Round(x);
	rvec.y = Application::Round(y);
	return rvec;
}
