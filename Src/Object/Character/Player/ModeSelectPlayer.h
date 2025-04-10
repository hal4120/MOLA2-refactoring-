#pragma once
#include"../Vector2/Vector2.h"
#include"Parry.h"

class ModeSelectPlayer
{
public:
	static constexpr int SIZE_X = 50;
	static constexpr int SIZE_Y = 66;

	static constexpr int MOVE_SPEED = 10;

	ModeSelectPlayer();
	~ModeSelectPlayer();

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	Vector2 GetPlayerPos(void) { return pos; }
	bool GetParryFlg(void) { return parry.GetParryFlg(); }
	Vector2 GetParryPos(void) { return parry.GetParryPos(); }


private:
	int image;
	int parrysound;
	Vector2 pos;
	Parry parry;
	int prevparrykey, nowparrykey;
	bool ParrySoundflg;
};

