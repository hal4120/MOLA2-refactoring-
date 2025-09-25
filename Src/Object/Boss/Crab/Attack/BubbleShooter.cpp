#include "BubbleShooter.h"

BubbleShooter::BubbleShooter(const Vector2& bossPos, const Vector2& playerPos):
	bossPos_(bossPos),
	playerPos_(playerPos),
	img_(),
	bubbles_(),
	shot_(false)
{
}

BubbleShooter::~BubbleShooter()
{
	//Utility::LoadImg(img_, "")
	bubbles_.reserve(BUBBLE_NUM);
	for (int i = 0; i < BUBBLE_NUM; i++) {
		//bubbles_.emplace_back(new Bubble(img_));
	}
}

void BubbleShooter::Load(void)
{
}

void BubbleShooter::Init(void)
{
}

void BubbleShooter::Update(void)
{
}

void BubbleShooter::Draw(void)
{
}

void BubbleShooter::Release(void)
{
}
