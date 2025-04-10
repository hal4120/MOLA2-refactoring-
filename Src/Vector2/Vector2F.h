#pragma once

class Vector2;


class Vector2F
{
public:
	Vector2F(void);
	Vector2F(float vX,float vY);
	~Vector2F(void);

	float x, y;

	//Vector2‚Ö‚Ì•ÏŠ·
	Vector2 ToVector2(void);

private:

};

