#pragma once

class Vector2F;

class Vector2
{
public:
	Vector2();
	Vector2(int vX, int vY);
	Vector2(Vector2F val);
	~Vector2();

	int x, y;

	//Vector2F‚Ö‚Ì•ÏŠ·
	Vector2F ToVector2F(void);

private:

};

