#include"BlastEffectManager.h"

#include<DxLib.h>

#include"BlastEffect.h"

#include"../../Utility/Utility.h"

std::vector<int>BlastEffectManager::image_ = {};
std::vector<BlastEffect*> BlastEffectManager::blast_ = {};

BlastEffectManager::BlastEffectManager()
{
}

BlastEffectManager::~BlastEffectManager()
{
}

void BlastEffectManager::Load(void)
{
	this->Release();

	Utility::LoadArrayImg("Data/Image/Effect/Blast.png", BLAST_NUM_MAX, BLAST_NUM_X, BLAST_NUM_Y, BLAST_SIZE, BLAST_SIZE, image_);

	blast_.reserve(10);
}

void BlastEffectManager::Update(void)
{
	for (auto& b : blast_) {
		if (!b->GetAlive())continue;
		b->Update();
	}
}

void BlastEffectManager::Draw(void)
{
	for (auto& b : blast_) {
		if (!b->GetAlive())continue;
		b->Draw();
	}
}

void BlastEffectManager::Release(void)
{
	for (auto& b : blast_) {
		if (!b)continue;
		b->Release();
		delete b;
	}
	blast_.clear();

	for (auto& i : image_) {
		DeleteGraph(i);
	}
	image_.clear();
}

void BlastEffectManager::On(Vector2 pos)
{
	bool r = false;
	for (auto& b : blast_) {
		if (!b->GetAlive()) {
			b->On(pos);
			r = true;
			break;
		}
	}

	if (!r) {
		blast_.emplace_back(new BlastEffect());
		blast_[blast_.size() - 1]->Load(image_);
		blast_[blast_.size() - 1]->On(pos);
	}
}
