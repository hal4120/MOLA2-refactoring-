#pragma once
#include"../StDefineData.h"
#include"../Vector2/Vector2.h"
//#include"../Player/ModeSelectPlayer.h"

class ModeSelect
{
public:
	static constexpr int MODE_SELECT_SIZE_X = 400;
	static constexpr int MODE_SELECT_SIZE_Y = 100;

	static constexpr int PARRY_SPEED = 15;

	ModeSelect();
	~ModeSelect();

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

	MODE_ID Getnowmode(void) { return nowmode; }

private:
//	ModeSelectPlayer plInst;
	int normalimage, hardimage, haikeiimage, nowselectimage;
	Vector2 normalpos, hardpos;
	bool normalflg, normalparry, hardflg, hardparry;
	MODE_ID nowmode;

	int parryhitsound;

	E_SCENE_ID nextSceneID;
};

