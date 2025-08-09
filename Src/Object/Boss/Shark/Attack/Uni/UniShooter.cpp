#include"UniShooter.h"

UniShooter::UniShooter():
	img_(),
	reticleImg_(-1),
	isReticle_(false),
	reticleFloat_(1.0f),
	target_(),
	arrowImg_(-1),
	unis_()
{
}

UniShooter::~UniShooter()
{
}

void UniShooter::Load(void)
{
	Utility::LoadImg(img_[(int)Uni::IMG_NUM::SUMMON], "Data/Image/Boss/Shark/Attack/Uni/shothole.png");
	Utility::LoadImg(img_[(int)Uni::IMG_NUM::UNI], "Data/Image/Boss/Shark/Attack/Uni/Uni.png");
	Utility::LoadImg(reticleImg_, "Data/Image/Boss/Shark/Attack/Uni/Reticle.png");
	Utility::LoadImg(arrowImg_, "Data/Image/Effect/Arrow.png");

	unis_.reserve(NUM);
	for (int i = 0; i < NUM; i++) {
		unis_.emplace_back(new Uni(img_,arrowImg_));
		unis_[unis_.size() - 1]->Load();
	}
}

void UniShooter::Init(void)
{

}

void UniShooter::Update(void)
{
	isReticle_ = false;
	for (auto& uni : unis_) {
		uni->Update();
		if (uni->GetState() == Uni::STATE::SUMMON ||
			uni->GetState() == Uni::STATE::THROWN) {
			isReticle_ = true;
		}
	}

	if (isReticle_) {
		reticleFloat_ += Utility::Deg2RadF(10.0f);
		if (reticleFloat_ >= Utility::Deg2RadF(360.0f)) {
			reticleFloat_ = Utility::Deg2RadF(0.0f);
		}
	}
}

void UniShooter::Draw(void)
{
	if (isReticle_) { DrawRotaGraph(target_.x, target_.y, ((sinf(reticleFloat_) + 1.0f) / 2.0f) + 0.5f, reticleFloat_, reticleImg_, true); }
	for (auto& uni : unis_) { uni->Draw(); }
}

void UniShooter::Release(void)
{
	for (auto& uni : unis_) {
		if (!uni) { continue; }
		delete uni;
		uni = nullptr;
	}

	for (auto& id : img_) { DeleteGraph(id); }
}

void UniShooter::Shot(Vector2 target)
{
	target_ = target;
	for (int i = 0; i < NUM; i++) {
		unis_[i]->On(POINT[i], target_);
	}
}