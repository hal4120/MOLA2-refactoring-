#include<DxLib.h>
#include<sstream>
#include"Parry.h"

#define PI 3.1415926535897932384626433832795f

Parry::Parry()
{

}

Parry::~Parry()
{
}

bool Parry::SystemInit(void)
{
	int err = -1;
	err = LoadDivGraph("image/Parry.png", ANIM_MAX, ANIM_MAX, 1, SIZE_WID, SIZE_HIG, image);
	if (err == -1)return false;

	arrowimage = LoadGraph("image/矢印.png");
	if (arrowimage == -1)return false;

	sizeupimage = LoadGraph("image/sizeup.png");
	if (sizeupimage == -1)return false;

	return true;
}


void Parry::GameInit(void)
{
	animCounter = 0;
	pos.x = pos.y = 0;
	flg = false;

	bigparry = 1.0f;
	dbig = 0;

	//弾道予測矢印
	arrowflg = false;
	
	//サイズアップ
	sizeuppos.x = sizeuppos.y = 0;
	sizeupcounter = 0;
}

void Parry::Update(void)
{
	if (flg) {
		animCounter++;
		if (animCounter >= ANIM_MAX) {
			animCounter = 0;
			flg = false;
		}
	}


	if (sizeupcounter > 0) {
		sizeuppos.y -= 0.1;
		sizeupcounter--;
	}
}

void Parry::Draw(void)
{
	float big;
	big = (SIZE_HIG * bigparry) - SIZE_HIG;
	dbig = static_cast<int>(round(big));

	if (flg) {
		DrawExtendGraph(pos.x, pos.y - dbig / 2, pos.x + SIZE_WID * bigparry, (pos.y - dbig / 2) + (SIZE_HIG * bigparry), image[animCounter], true);
	}

	if (arrowflg) {
		DrawRotaGraph(arrowpos.x, arrowpos.y, 1.0, arrowkkd, arrowimage, true);
	}

	if (sizeupcounter > 100) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, sizeupcounter);
		DrawGraph(sizeuppos.x, sizeuppos.y, sizeupimage, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

bool Parry::Release(void)
{

	for (int ii = ANIM_MAX - 1; ii >= 0; ii--) {
		if (DeleteGraph(image[ii]) == -1)return false;
	}
		
	return true;
}

bool Parry::GetParryFlg(void) { return flg; }
int Parry::GetAnimCounter(void) { return animCounter; }
Vector2 Parry::GetParryPos(void) { return pos; }
void Parry::SetParryPos(Vector2 ppos) { pos = ppos; }
void Parry::SetParryFlg(bool f) { flg = f; }

void Parry::SetBigParry(void)
{
	switch (nowmode)
	{
	case MODE_NORMAL:
		if (bigparry < BIG_PARRY_MAX_NORMAL) {
			bigparry += 0.2f;
			sizeupcounter = 150;
		}
		break;
	case MODE_HARD:
		if (bigparry < BiG_PARRY_MAX_HARD) {
			bigparry += 0.1f;
			sizeupcounter = 150;
		}
		break;
	}
}
