#pragma once
#include"../../../Vector2/Vector2.h"
#include"PlayerLaser.h"
#include"Parry.h"

class Player {
public:
	static constexpr int PLAYER_SIZE_WID = 50;
	static constexpr int PLAYER_SIZE_HIG = 66;

	static constexpr int NUM_SIZE = 32;

	static constexpr int PLAYER_MOVE_SPEED_X = 6;
	static constexpr int PLAYER_MOVE_SPEED_Y = 6;
	static constexpr int PLAYER_SLOW_SPEED = 4;

	static constexpr int PLAYER_RESPORN_TIME = 120;		//点滅時間

	static constexpr int PLAYER_MAX_NUM = 5;
	static constexpr int PLAYER_NUM_DISP_Y = 640 - NUM_SIZE;
	static constexpr int PLAYER_NUM_DISP_X = 0;

	static constexpr int LASER_CHARGE_MAX = 20;
	static constexpr int LASER_CHARGE_DISP_X = 30;
	static constexpr int LASER_CHARGE_DISP_Y = 300;

	static constexpr int PARRY_PENA_MAX = 120;


	static constexpr int ATTACK_RANGE_SIZE_X = 32;
	static constexpr int ATTACK_RANGE_SIZE_Y = 64;
	static constexpr int ATTACK_RANGE_MAX = 11;
		
	Player(void);
	~Player(void);

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	Vector2 GetPlayerpos(void);

	bool GetPlayerFlg(void);
	void SetPlayerFlg(bool flg);
	void SetPlayerreFlg(bool reflg);
	bool GetPlayernum(void);
	void SetPlayernum(void);
	void Charge();
	void Sound();

	bool GetLaserflg(void);
	Vector2 GetLaserpos(void);



	//ゲームモード
	void Setmode(MODE_ID id) { nowmode = id;	parry.SetMode(nowmode); }

	//パリィ----------------------------------------------------
	bool GetParryFlg(void);
	int GetAnimCounter(void);
	Vector2 GetParryPos(void);

	void penariset(void);


	//拡大倍率
	float GetBigParry(void) { return parry.GetBigParry(); }
	void SetBigParry(void) { parry.SetBigParry(); parry.Setsizeuppos(pos); }
	void ReSetBigParry(void) { parry.ReSetBigParry(); }
	int GetdbigParry(void) { return parry.Getdbigparry(); }


	//弾道予測矢印
	void SetArrowFlg(bool flg) { parry.SetArrowFlg(flg); }
	void SetArrowPos(Vector2 pos) { parry.SetArrowPos(pos); }
	void SetArrowkkd(float kkd) { parry.SetArrowkkd(kkd); }

	//--------------------------------------------------------

	int GetLaserHantei(void) { return laser.GetHantei(); }
	void SetLaserHantei(void) { laser.SetHantei(); }

	void StopSound(void) { laser.stopSound(); }

private:
	int image;			//自機の画像のハンドル番号
	int parrysound;
	int zanki;
	int chargeimage[LASER_CHARGE_MAX+1];
	int Vpush;
	Vector2 pos;
	bool exFlg;			//プレイヤーの機体の表示管理フラグ
	int respawncount;
	int respawncontrolcount;
	bool reexFlg;
	bool slowmoveflg;
	bool ParrySoundflg;

	int num;

	PlayerLaser laser;
	int charge;
	int nowlaserkey, prevlaserkey;

	Parry parry;
	int prevparrykey;
	int	nowparrykey;

	int parrypenacounter;

	int attackrangeimage[ATTACK_RANGE_MAX];


	MODE_ID nowmode;

};
