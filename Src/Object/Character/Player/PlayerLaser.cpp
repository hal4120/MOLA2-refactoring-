//-------------------------------------------------------------------
// ゲーム制作：shooting
// 氏名　　　：2416081　山本 悠
//-------------------------------------------------------------------
#include <DxLib.h>
#include"PlayerLaser.h"

PlayerLaser::PlayerLaser()
{
	image = -1;

}

PlayerLaser::~PlayerLaser()
{
}

bool PlayerLaser::SystemInit(void)
{
	int err = -1;
	err = LoadDivGraph("Data/image/PlayerYobiLaser.png", CHARGE_MAX,
		1, CHARGE_MAX,
		SIZE_WID, SIZE_HIG, chargeimage);
	if (err == -1) {
		return false;
	}

	image = LoadGraph("Data/image/PlayerLaser.png");
	if (image == -1) return false;

	ChargeSound = LoadSoundMem("Data/sound/laserCharge.mp3");
	if (ChargeSound == -1)return false;

	LaserSound = LoadSoundMem("Data/sound/laser.mp3");
	if (LaserSound == -1)return false;

	return true;
}

void PlayerLaser::GameInit(void)
{
	pos.x = pos.y = 0;
	chargecounter = 0;
	chargeflg = false;
	laserflg = false;
	counter = 0;
	hantei = 0;
}

void PlayerLaser::Update(void)
{
	if (chargeflg) {
		counter++;
		if (CheckSoundMem(ChargeSound) == 0) {
			PlaySoundMem(ChargeSound, DX_PLAYTYPE_BACK, true);
		}
		if (counter > 5) {
			counter = 0;
			chargecounter++;
			if (chargecounter >= CHARGE_MAX) {
				chargecounter = 0;
				chargeflg = false;
				laserflg = true;
				if (CheckSoundMem(ChargeSound) == 1) {
					StopSoundMem(ChargeSound);
				}
			}
		}
	}

	if (laserflg) {
		if (CheckSoundMem(LaserSound) == 0) {
			PlaySoundMem(LaserSound, DX_PLAYTYPE_BACK, true);
		}
		counter++;
		if (counter > 120) {
			laserflg = false;
		}
	}

	if (hantei > 0)hantei--;
}

void PlayerLaser::Draw(void)
{
	if (chargeflg) {
		DrawGraph(pos.x, pos.y, chargeimage[chargecounter], true);
	}
	if (laserflg) {
		DrawGraph(pos.x, pos.y, image, true);
	}
}

bool PlayerLaser::Release(void)
{
	if (DeleteSoundMem(LaserSound) == -1)return false;
	if (DeleteSoundMem(ChargeSound) == -1)return false;

	if (DeleteGraph(image) == -1)return false;
	for (int ii = CHARGE_MAX - 1; ii >= 0; ii--) {
		if (DeleteGraph(chargeimage[ii]) == -1)return false;
	}

	return true;
}

Vector2 PlayerLaser::Getpos(void) { return pos; }
void PlayerLaser::Setpos(Vector2 ppos) { pos = ppos; }
bool PlayerLaser::Getflg(void) { return laserflg; }
bool PlayerLaser::Getchargeflg(void) { return chargeflg; }
void PlayerLaser::Setflg(bool flg) { laserflg = flg; }
void PlayerLaser::Setchargeflg(bool flg) { chargeflg = flg; }

void PlayerLaser::Setchargecounter(int counter) { chargecounter = counter; }
