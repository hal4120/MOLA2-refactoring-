#include<DxLib.h>
#include<time.h>
#include"Vector2.h"
#include"../Application.h"

Vector2::Vector2()
{

	x = y = 0;
}

Vector2::Vector2(int vX, int vY)
{
	x = vX;
	y = vY;
}

Vector2::Vector2(Vector2F val)
{
	x = Application::Round(val.x);
	y = Application::Round(val.y);
}

Vector2::~Vector2()
{
}

Vector2F Vector2::ToVector2F(void)
{
	Vector2F rvecf;
	rvecf.x = static_cast<float>(x);
	rvecf.y = static_cast<float>(y);

	return rvecf;
}
