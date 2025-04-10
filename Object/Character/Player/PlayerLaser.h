#pragma once
#include"../Vector2/Vector2.h"

class PlayerLaser
{
public:
	static constexpr int SIZE_WID= 1000;
	static constexpr int SIZE_HIG = 100;
	static constexpr int CHARGE_MAX = 9;
	static constexpr int HANTEI_INTERVAL = 5;

	PlayerLaser();
	~PlayerLaser();

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	Vector2 Getpos(void);
	void Setpos(Vector2 ppos);
	bool Getflg(void);
	bool Getchargeflg(void);
	void Setflg(bool flg);
	void Setchargeflg(bool flg);
	void Setchargecounter(int counter);

	int GetHantei(void) { return hantei; }
	void SetHantei(void) { hantei = HANTEI_INTERVAL; }

	void stopSound(void) { StopSoundMem(ChargeSound); StopSoundMem(LaserSound); }


private:
	int image;
	int chargeimage[CHARGE_MAX];

	int ChargeSound;
	int LaserSound;

	Vector2 pos;

	int chargecounter;

	bool chargeflg;
	bool laserflg;

	int counter;

	int hantei;

};

