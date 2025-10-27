#include"TentacleShooter.h"

#include"../../../../../Utility/Utility.h"

#include"../../../../../Manager/Collision/Collision.h"

TentacleShooter::TentacleShooter(const float& playerPosX) :
	playerPosX(playerPosX)
{
}

TentacleShooter::~TentacleShooter()
{
}

void TentacleShooter::Load(void)
{
	Utility::LoadImg(image_, "Data/Image/Boss/Kraken/Attack/Tentacle/Tentacle.png");

}

void TentacleShooter::Update(void)
{
	for (auto& t : tentacles_) { t->Update(); }
}

void TentacleShooter::Draw(void)
{
	for (auto& t : tentacles_) { t->Draw(); }
}

void TentacleShooter::Release(void)
{

}

void TentacleShooter::On(void)
{
	bool recycle = false;

	for (int i = 0; i < tentacles_.size(); i++) {
		if (tentacles_[i]->GetUnit().isAlive_) { continue; }

		recycle = true;
		tentacles_[i]->On();

		lastReference_ = i;

		break;
	}

	if (recycle) { return; }

	tentacles_.emplace_back(new Tentacle(image_, playerPosX));
	tentacles_.back()->Load();
	tentacles_.back()->Init();
	tentacles_.back()->On();
	Collision::Add(tentacles_.back());

	lastReference_ = (int)tentacles_.size() - 1;
}

bool TentacleShooter::End(void) 
{
	// 一番最後に起動したものの終了フラグを返す

	if (lastReference_ < tentacles_.size()) {
		return tentacles_[lastReference_]->End();
	} 
	return true;
}