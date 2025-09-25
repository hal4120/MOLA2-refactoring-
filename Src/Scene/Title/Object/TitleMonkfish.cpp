#include "TitleMonkfish.h"

#include"../../../Utility/Utility.h"

TitleMonkfish::TitleMonkfish() :
	img_(-1),
	angle_()
{
}

TitleMonkfish::~TitleMonkfish()
{
}

void TitleMonkfish::Load(void)
{
	Utility::LoadImg(img_, "Data/Image/Enemy/Monkfish/Monkfish.png");
}

void TitleMonkfish::Init(void)
{
	for (int i = 0; i < NUM; i++) { angle_[i] = (float)i; }
}

void TitleMonkfish::Update(void)
{
	for (int i = 0; i < NUM; i++) { angle_[i] += 0.05f; }
}

void TitleMonkfish::Draw(void)
{
	for (int i = 0; i < NUM; i++) {
		DrawRotaGraph(POS[i].x, POS[i].y, 2, Utility::Deg2RadF(165.0f) + Utility::Deg2RadF(sinf(angle_[i]) * 15.0f), img_, true);
	}
}

void TitleMonkfish::Release(void)
{
	DeleteGraph(img_);
}