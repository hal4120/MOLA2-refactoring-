//-------------------------------------------------------------------
// ゲーム制作：shooting
// 氏名　　　：2416081　山本 悠
//-------------------------------------------------------------------
#include <DxLib.h>
#include"Player.h"
#include"../../../Application.h"
Player::Player(void)
{
	image = -1;
	Vpush = -1;
}

Player::~Player(void)
{

}

bool Player::SystemInit(void)
{
	image = LoadGraph("Data/image/まぼ.png");
	if (image == -1) {
		return false;	
	}

	zanki = LoadGraph("Data/image/ミニまぼ.png");
	if (zanki == -1) {
		return false;
	}

	int err = -1;
	err = LoadDivGraph("Data/image/charge.png", 21,
		21, 1, LASER_CHARGE_DISP_X, LASER_CHARGE_DISP_Y, chargeimage);
	if (err == -1)return false;
	Vpush = LoadGraph("Data/image/Vpush.png");
	if (Vpush == -1)return false;


	err = LoadDivGraph("Data/image/AttackRange.png", ATTACK_RANGE_MAX,
		ATTACK_RANGE_MAX, 1, ATTACK_RANGE_SIZE_X, ATTACK_RANGE_SIZE_Y, attackrangeimage);
	if (err == -1)return false;


	parrysound = LoadSoundMem("Data/sound/ParrySound.mp3");

	laser.SystemInit();
	parry.SystemInit();

	return true;
}

void Player::GameInit(void)
{
	pos.x = PLAYER_SIZE_WID * 2;
	pos.y = Application::SCREEN_SIZE_HIG / 2 - PLAYER_SIZE_HIG / 2;

	exFlg = true;
	reexFlg = true;
	slowmoveflg = false;

	respawncount = respawncontrolcount = 0;
	num = PLAYER_MAX_NUM;
	
	laser.GameInit();
	charge = 0;
	nowlaserkey = prevlaserkey = 0;

	parry.GameInit();

	parrypenacounter = 0;

}

void Player::Update(void)
{
	

	if(CheckHitKey(KEY_INPUT_P))charge = LASER_CHARGE_MAX;
	if (CheckHitKey(KEY_INPUT_O))charge = 0;
	// プレイヤーが非表示になっているので、再表示する
	if (exFlg == false) {
		respawncount++;
		if (respawncount == 1) {
			parry.SetParryFlg(false);
			parrypenacounter = 0;
				pos.x = PLAYER_SIZE_WID * 2;
				pos.y = Application::SCREEN_SIZE_HIG / 2 - PLAYER_SIZE_HIG / 2;
		}

		if (respawncount > 120) {
			exFlg = true;
			reexFlg = exFlg;
			respawncount = 0;
		} else {
			if (respawncount > 15) {
				if (reexFlg == true) {
					respawncontrolcount++;
					if (respawncontrolcount > 10) {
						reexFlg = false;
						respawncontrolcount = 0;
					}
				}
				else {
					respawncontrolcount++;
					if (respawncontrolcount > 10) {
						reexFlg = true;
						respawncontrolcount = 0;
					}
				}
			}
		}

	}

	if (CheckHitKey(KEY_INPUT_LSHIFT) == 1) {

		slowmoveflg = true;
	}
	else {
		slowmoveflg = false;
	}

	//レーザーチャージ中は移動処理を無効
	if (laser.Getchargeflg() == false) {
		//プレイヤー移動処理
		if (CheckHitKey(KEY_INPUT_D) == 1 || CheckHitKey(KEY_INPUT_RIGHT) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_RIGHT) == 0)) {
			if (slowmoveflg == false) {
				// 右キーが押されているので、機体を右に移動させる
				pos.x += PLAYER_MOVE_SPEED_X;
			}
			else {
				pos.x = pos.x + PLAYER_SLOW_SPEED;
			}
		}
		if (CheckHitKey(KEY_INPUT_A) == 1 || CheckHitKey(KEY_INPUT_LEFT) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_LEFT) == 0)) {
			if (slowmoveflg == false) {
				// 左キーが押されているので、機体を左に移動させる
				pos.x = pos.x - PLAYER_MOVE_SPEED_X;
			}
			else {
				pos.x = pos.x - PLAYER_SLOW_SPEED;
			}
		}
		if (CheckHitKey(KEY_INPUT_W) == 1 || CheckHitKey(KEY_INPUT_UP) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_UP) == 0)) {
			if (slowmoveflg == false) {
				// 上キーが押されているので、機体を上に移動させる
				pos.y = pos.y - PLAYER_MOVE_SPEED_Y;
			}
			else {
					pos.y = pos.y - PLAYER_SLOW_SPEED;
			}
		}
		if (CheckHitKey(KEY_INPUT_S) == 1 || CheckHitKey(KEY_INPUT_DOWN) == 1 || !((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_DOWN) == 0)) {
			if (slowmoveflg == false) {
				// 下キーが押されているので、機体下に移動させる
				pos.y = pos.y + PLAYER_MOVE_SPEED_Y;
			}
			else {
				pos.y = pos.y + PLAYER_SLOW_SPEED;
			}
		}
	}

	

	// 自機の現在位置がウィンドウ外に飛び出していないかのチェックを行う。
	// 左端のチェック
	if (pos.x < NUM_SIZE) {
		pos.x = NUM_SIZE;
	}
	// 右端のチェック
	if (pos.x > (Application::SCREEN_SIZE_WID - PLAYER_SIZE_WID)) {
		pos.x = (Application::SCREEN_SIZE_WID - PLAYER_SIZE_WID);
	}
	// 上端のチェック
	if (pos.y < 0) {
		pos.y = 0;
	}
	// 下端のチェック
	if (pos.y > (Application::SCREEN_SIZE_HIG - PLAYER_SIZE_HIG)) {
		pos.y = (Application::SCREEN_SIZE_HIG - PLAYER_SIZE_HIG);
	}

	//レーザー処理
	prevlaserkey = nowlaserkey;
	nowlaserkey = CheckHitKey(KEY_INPUT_V);

	if (exFlg) {
		if (prevlaserkey == 0 && nowlaserkey == 1&&charge==LASER_CHARGE_MAX&&
			laser.Getchargeflg()==false&&laser.Getflg()==false) {
			laser.Setchargeflg(true);
			laser.Setchargecounter(0);
			charge = 0;
		}
		if (!((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_4) == 0) && charge == LASER_CHARGE_MAX &&
			laser.Getchargeflg() == false && laser.Getflg() == false) {
			laser.Setchargeflg(true);
			laser.Setchargecounter(0);
			charge = 0;
		}

		Vector2 ppos = pos;
		ppos.x = ppos.x + PLAYER_SIZE_WID; 
		ppos.y = (ppos.y + PLAYER_SIZE_HIG / 2) - (PlayerLaser::SIZE_HIG / 2);
		laser.Setpos(ppos);
		laser.Update();
	}
	else {
		laser.Setflg(false);
		laser.Setchargeflg(false);
	}

	//パリィ処理
	prevparrykey = nowparrykey;
	nowparrykey = CheckHitKey(KEY_INPUT_SPACE);
	if (reexFlg || respawncount > 0) {
		Vector2 prpos;
		if (parrypenacounter <= 0) {
			if ((prevparrykey == 0 && nowparrykey == 1 && GetParryFlg() == false) || (!((GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2) == 0))&& GetParryFlg() == false) {
				if (CheckSoundMem(parrysound) == false) {
					PlaySoundMem(parrysound, DX_PLAYTYPE_BACK);
				}
				parry.SetParryFlg(true);
				parrypenacounter = PARRY_PENA_MAX;
			}
		}
		prpos.x = pos.x + PLAYER_SIZE_WID;
		prpos.y = pos.y + PLAYER_SIZE_HIG / 2 - Parry::SIZE_HIG / 2;
		parry.SetParryPos(prpos);
		parry.Update();
	}

	//パリィミスのペナルティ時間
	if (parrypenacounter > 0) { parrypenacounter -= 2; }

}

void Player::SetPlayernum(void) { num--; }

void Player::Charge() { if (charge < LASER_CHARGE_MAX) charge++; }



void Player::Draw(void)
{
	if (reexFlg) {
		DrawGraph(pos.x, pos.y, image, true);
	}

	if (reexFlg || respawncount > 0) {
		laser.Draw();
		parry.Draw();
		if (parry.GetParryFlg() == false && parrypenacounter > 0) {
			for (int ii = parrypenacounter; ii > 0; ii--) {
				DrawBox(pos.x + 0.4 * (PARRY_PENA_MAX - ii), pos.y, pos.x + 0.4 * (PARRY_PENA_MAX - ii) + 0.3, pos.y - 4, RGB(255, 255, 0), true);
			}
		}
	}

	//残機表示
	for (int ii = num - 1; ii > 0; ii--) {
		DrawGraph(0, Application::SCREEN_SIZE_HIG - NUM_SIZE * ii, zanki, true);
	}


	//特殊攻撃チャージ
	DrawGraph(1, 5, chargeimage[charge], true);

	if (charge == LASER_CHARGE_MAX) {
		DrawGraph(1, 5 + LASER_CHARGE_DISP_Y, Vpush, true);
	}


	//パリィ攻撃範囲
	int attackrangecount = static_cast<int>((parry.GetBigParry() * 10) - 10);

	DrawGraph(0, 5 + LASER_CHARGE_DISP_Y + 35, attackrangeimage[attackrangecount], true);
	

}


bool Player::Release(void)
{
	parry.Release();
	laser.Release();

	DeleteSoundMem(parrysound);

	if (DeleteGraph(Vpush) == -1)return false;
	for (int ii = LASER_CHARGE_MAX; ii >= 0; ii--) {
		if (DeleteGraph(charge) == -1)return false;
	}
	DeleteGraph(image);

	return true;
}

Vector2 Player::GetPlayerpos(void) { return pos; }
bool Player::GetPlayerFlg(void) { return exFlg; }
void Player::SetPlayerFlg(bool flg) { exFlg = flg; }
void Player::SetPlayerreFlg(bool reflg) { reexFlg = reflg; }
bool Player::GetPlayernum(void) { return num; }

bool Player::GetLaserflg(void) { return laser.Getflg(); }
Vector2 Player::GetLaserpos(void) { return laser.Getpos(); }

bool Player::GetParryFlg(void) { return parry.GetParryFlg(); }
int Player::GetAnimCounter(void) { return parry.GetAnimCounter(); }
Vector2 Player::GetParryPos(void) { return parry.GetParryPos(); }

void Player::penariset(void) { parrypenacounter = 0; }