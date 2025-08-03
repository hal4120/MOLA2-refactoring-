#include "StageBase.h"

#include<DxLib.h>

#include"../../Application/Application.h"

StageBase::StageBase() :
	backSizeX(),
	backSizeY(),
	backScrollSpeed(),
	backImg_(),
	backDecorationImg_(),
	poss_(),

	object1SizeX(),
	object1SizeY(),
	object1Num(),
	object1MaxSpeed(),
	object1Img_(),
	object1Info_(),

	object2SizeX(),
	object2SizeY(),
	object2Num(),
	object2MaxSpeed(),
	object2Img_(),
	object2Info_(),

	moveVec_(),

	gimics_()
{
}

StageBase::~StageBase()
{
}

void StageBase::Init()
{
	Vector2I screen = { Application::SCREEN_SIZE_X,Application::SCREEN_SIZE_Y };

	moveVec_ = { (float)(-backSizeX),(float)(backSizeY) };
	moveVec_ /= sqrtf(moveVec_.x * moveVec_.x + moveVec_.y * moveVec_.y);

	poss_[CENTER1] = { backSizeX / 2.0f,screen.y - backSizeY / 2.0f };
	poss_[CENTER2] = poss_[CENTER1] + Vector2(backSizeX, -backSizeY);
	poss_[LEFT] = poss_[CENTER1] + Vector2(0.0f, -backSizeY);
	poss_[RIGHT] = poss_[CENTER1] + Vector2(backSizeX, 0.0f);

	object1Info_.resize(object1Num);
	for (auto& pInfo : object1Info_) {
		pInfo.pos = { (float)GetRand(backSizeX),(float)GetRand(backSizeY) };
		pInfo.move = moveVec_ * (GetRand(object1MaxSpeed) + 1.0f);
	}

	object2Info_.resize(object2Num);
	for (auto& pInfo : object2Info_) {
		pInfo.pos = { (float)GetRand(backSizeX),(float)GetRand(backSizeY) };
		pInfo.move = moveVec_ * (GetRand(object2MaxSpeed) + 1.0f);
	}

	for (auto& gimic : gimics_) { gimic->Init(); }
}
void StageBase::Update()
{
	for (auto& pos : poss_) { pos += (moveVec_ * backScrollSpeed); }

	Vector2I screen = { Application::SCREEN_SIZE_X,Application::SCREEN_SIZE_Y };

	for (int i = 0; i < CENTER_NUM; i++) {
		if (poss_[i].x + backSizeX / 2.0f < 0.0f || poss_[i].y - backSizeY / 2.0f > screen.y) {
			int reverse = (i * -1) + 1;
			poss_[i] = poss_[reverse] + Vector2(backSizeX, -backSizeY);
			break;
		}
	}
	if (poss_[LEFT].x + backSizeX / 2.0f < 0.0f) {
		poss_[LEFT] += Vector2(backSizeX, -backSizeY);
	}
	if (poss_[RIGHT].y - backSizeY / 2.0f > screen.y) {
		poss_[RIGHT] += Vector2(backSizeX, -backSizeY);
	}

	for (auto& pInfo : object1Info_) {
		pInfo.pos += pInfo.move;
		if (pInfo.pos.x + object1SizeX / 2.0f < 0.0f || pInfo.pos.y - object1SizeY / 2.0f > screen.y) {
			pInfo.pos.x = (screen.x + object1SizeX / 2.0f) + GetRand(backSizeX);
			pInfo.pos.y = -(screen.y + object1SizeY / 2.0f) + GetRand(backSizeY);
			pInfo.move = moveVec_ * (GetRand(object1MaxSpeed) + 1.0f);
		}
	}

	for (auto& pInfo : object2Info_) {
		pInfo.pos += pInfo.move;
		if (pInfo.pos.x + object2SizeX / 2.0f < 0.0f || pInfo.pos.y - object2SizeY / 2.0f > screen.y) {
			pInfo.pos.x = (screen.x + object2SizeX / 2.0f) + GetRand(backSizeX);
			pInfo.pos.y = -(screen.y + object2SizeY / 2.0f) + GetRand(backSizeY);
			pInfo.move = moveVec_ * (GetRand(object2MaxSpeed) + 1.0f);
		}
	}

	for (auto& gimic : gimics_) { gimic->Update(); }
}
void StageBase::Draw()
{
	for (auto& pos : poss_) {
		DrawRotaGraph(pos.x, pos.y, 1, 0, backImg_, true);
		DrawRotaGraph(pos.x, pos.y, 1, 0, backDecorationImg_, true);
	}
	for (auto& pInfo : object1Info_) {
		DrawRotaGraph(pInfo.pos.x, pInfo.pos.y, 1, 0, object1Img_, true);
	}
	for (auto& pInfo : object2Info_) {
		DrawRotaGraph(pInfo.pos.x, pInfo.pos.y, 1, 0, object2Img_, true);
	}

	for (auto& gimic : gimics_) { gimic->Draw(); }
}
void StageBase::Release()
{
	for (auto& ins : gimics_) {
		if (ins == nullptr) { continue; }
		ins->Release();
		delete ins;
		ins = nullptr;
	}
	gimics_.clear();

	object1Info_.clear();
	object2Info_.clear();

	DeleteGraph(backImg_);
	DeleteGraph(backDecorationImg_);
	DeleteGraph(object1Img_);
	DeleteGraph(object2Img_);
}
