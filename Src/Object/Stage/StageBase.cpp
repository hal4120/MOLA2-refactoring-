#include "StageBase.h"

#include<DxLib.h>

#include"../../Application/Application.h"

StageBase::StageBase() :
	backSizeX(),
	backSizeY(),
	backScrollSpeed(),
	backDecorationScrollSpeed(),
	backImg_(),
	backDecorationImg_(),
	poss_(),
	backDecorationPoss_(),

	objects_(),

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
	poss_[CENTER2] = poss_[CENTER1] + Vector2((float)backSizeX, (float)-backSizeY);
	poss_[LEFT] = poss_[CENTER1] + Vector2(0.0f, (float)-backSizeY);
	poss_[RIGHT] = poss_[CENTER1] + Vector2((float)backSizeX, 0.0f);
	for (int i = 0; i < ARRANGEMENT::MAX; i++) { backDecorationPoss_[i] = poss_[i]; }

	for (auto& obj : objects_) {
		obj.info.resize(obj.objectNum);
		for (auto& info : obj.info) {
			info.pos = { (float)GetRand(backSizeX),(float)GetRand(backSizeY) };
			info.move = moveVec_ * (GetRand((int)obj.objectMaxSpeed) + 1.0f);
		}
	}

	for (auto& gimic : gimics_) { gimic->Init(); }
}
void StageBase::Update()
{
	BackScroll(poss_, backScrollSpeed);
	BackScroll(backDecorationPoss_, backDecorationScrollSpeed);

	ObjectScroll();

	for (auto& gimic : gimics_) { gimic->Update(); }
}
void StageBase::Draw()
{
	for (auto& pos : poss_) { DrawRotaGraphF(pos.x, pos.y, 1, 0, backImg_, true); }
	for (auto& pos : backDecorationPoss_) { DrawRotaGraphF(pos.x, pos.y, 1, 0, backDecorationImg_, true); }

	for (auto& obj : objects_) {
		for (auto& info : obj.info) { DrawRotaGraphF(info.pos.x, info.pos.y, 1, 0, obj.objectImg, true); }
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

	for (auto& obj : objects_) {
		DeleteGraph(obj.objectImg);
		obj.info.clear();
	}
	objects_.clear();


	DeleteGraph(backImg_);
	DeleteGraph(backDecorationImg_);
}

void StageBase::BackScroll(Vector2 *poss, float scrollSpeed)
{
	for (int i = 0; i < ARRANGEMENT::MAX; i++) { poss[i] += (moveVec_ * scrollSpeed); }

	Vector2I screen = { Application::SCREEN_SIZE_X,Application::SCREEN_SIZE_Y };

	for (int i = 0; i < CENTER_NUM; i++) {
		if (poss[i].x + backSizeX / 2.0f < 0.0f || poss[i].y - backSizeY / 2.0f > screen.y) {
			int reverse = 1 - i;
			poss[i] = poss[reverse] + Vector2((float)backSizeX, (float)-backSizeY);
			break;
		}
	}
	if (poss[LEFT].x + backSizeX / 2.0f < 0.0f) {
		poss[LEFT] += Vector2((float)backSizeX, (float)-backSizeY);
	}
	if (poss[RIGHT].y - backSizeY / 2.0f > screen.y) {
		poss[RIGHT] += Vector2((float)backSizeX, (float)-backSizeY);
	}
}

void StageBase::NewObject(std::string path, int sizeX, int sizeY, int num, float maxSpeed)
{
	OBJECT st = {};
	st.objectImg = Utility::LoadImg(path);
	st.objectSizeX = sizeX;
	st.objectSizeY = sizeY;
	st.objectNum = num;
	st.objectMaxSpeed = maxSpeed;

	objects_.emplace_back(st);
}

void StageBase::ObjectScroll(void)
{
	Vector2I screen = { Application::SCREEN_SIZE_X,Application::SCREEN_SIZE_Y };

	for (auto& obj : objects_) {
		for (auto& info : obj.info) {
			info.pos += info.move;
			if (info.pos.x + obj.objectSizeX / 2.0f < 0.0f || info.pos.y - obj.objectSizeY / 2.0f > screen.y) {
				info.pos.x = (screen.x + obj.objectSizeX / 2.0f) + GetRand(backSizeX);
				info.pos.y = -(screen.y + obj.objectSizeY / 2.0f) + GetRand(backSizeY);
				info.move = moveVec_ * (GetRand((int)obj.objectMaxSpeed) + 1.0f);
			}
		}
	}
}
