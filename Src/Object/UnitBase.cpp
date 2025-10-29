#include "UnitBase.h"

#include<DxLib.h>

UnitBase::UnitBase()
{
	
}

UnitBase::~UnitBase()
{
}

void UnitBase::Invi(void)
{
	if (unit_.inviciCounter_ > 0) {
		unit_.inviciCounter_--; 
	}
}

void UnitBase::DrawDebug(void)
{
	int color = (unit_.para_.colliType == CollisionType::ALLY) ? 0xffffff : 0xff0000;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
	Vector2 pos = unit_.pos_ + unit_.para_.center;
	switch (unit_.para_.colliShape)
	{
	case CollisionShape::CIRCLE:
		DrawCircleAA(pos.x, pos.y, unit_.para_.radius, 30, color);
		break;
	case CollisionShape::RECTANGLE:
		DrawBoxAA(
			pos.x - unit_.para_.size.x / 2,
			pos.y - unit_.para_.size.y / 2,
			pos.x + unit_.para_.size.x / 2,
			pos.y + unit_.para_.size.y / 2,
			color, true);
		break;
	case CollisionShape::ELLIPSE:
		DrawOvalAA(pos.x, pos.y, unit_.para_.size.x / 2, unit_.para_.size.y / 2, 30, color, true);
		break;
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
};
