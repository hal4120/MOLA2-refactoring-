#pragma once

class Vector2;


class Vector2F
{
public:
	Vector2F(void);
	Vector2F(float vX,float vY);
	~Vector2F(void);

	float x, y;

	//Vector2�ւ̕ϊ�
	Vector2 ToVector2(void);

private:

};

