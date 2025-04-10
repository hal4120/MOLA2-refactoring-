#pragma once
#include"../../../Vector2/Vector2.h"
#include"../../../Vector2/Vector2F.h"
#include"../../../StDefineData.h"

class Parry
{
public:

	static constexpr int SIZE_WID = 75;
	static constexpr int SIZE_HIG = 100;
	static constexpr int ANIM_MAX = 11;
	
	static constexpr float BIG_PARRY_MAX_NORMAL = 2.0f;
	static constexpr float BiG_PARRY_MAX_HARD = 1.5f;

	Parry();
	~Parry();

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	bool GetParryFlg(void);
	int GetAnimCounter(void);
	Vector2 GetParryPos(void);
	void SetParryPos(Vector2 ppos);
	void SetParryFlg(bool f);

	float GetBigParry(void) { return bigparry; }

	void SetBigParry(void);
	void ReSetBigParry(void) { bigparry = 1.0f; }

	int Getdbigparry(void) { return dbig; }


	void SetMode(MODE_ID id) { nowmode = id; }


	//弾道予測矢印
	void SetArrowFlg(bool flg) { arrowflg = flg; }
	void SetArrowPos(Vector2 pos) { arrowpos = pos; }
	void SetArrowkkd(float kkd) { arrowkkd = kkd; }

	//サイズアップ
	void Setsizeuppos(Vector2 p) { sizeuppos = p; }

private:
	int image[ANIM_MAX];

	Vector2 pos;

	bool flg;
	int animCounter;

	float bigparry;

	int dbig;


	MODE_ID nowmode;


	//弾道予測矢印
	int arrowimage;
	bool arrowflg;
	Vector2 arrowpos;
	float arrowkkd;

	//サイズアップ
	int sizeupimage;
	Vector2 sizeuppos;
	int sizeupcounter;

};

