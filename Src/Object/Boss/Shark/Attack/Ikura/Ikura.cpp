#include"Ikura.h"

#include<DxLib.h>

#include"../../../../../Application/Application.h"
#include"../../../../../Scene/Game/GameScene.h"
#include"../../../../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../../../../Manager/Sound/SoundManager.h"

#include"../../../../Player/Player.h"

Ikura::Ikura(int img):
	img_(img),
	moveVec_()
{
}

Ikura::~Ikura()
{
}

void Ikura::Load(void)
{
	unit_.para_.radius = SIZE / 2.0f;
	unit_.para_.colliShape = CollisionShape::CIRCLE;
	unit_.para_.colliType = CollisionType::ENEMY;

	unit_.para_.speed = SPEED;
}

void Ikura::Update(void)
{
	if (!unit_.isAlive_) { return; }
	unit_.pos_ += moveVec_ * unit_.para_.speed;
	if (unit_.pos_.x + unit_.para_.radius < 0.0f ||
		unit_.pos_.x - unit_.para_.radius > Application::SCREEN_SIZE_X ||
		unit_.pos_.y + unit_.para_.radius < 0.0f ||
		unit_.pos_.y - unit_.para_.radius > Application::SCREEN_SIZE_Y)
	{
		unit_.isAlive_ = false;
	}
}

void Ikura::Draw(void)
{
	if (!unit_.isAlive_) { return; }
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, 0, img_, true);
}

void Ikura::OnCollision(UnitBase* other)
{
	if (!other->GetUnit().isAlive_) { return; }

	if (dynamic_cast<Player*>(other)) {
		GameScene::Slow();
		BlastEffectManager::On(unit_.pos_);
	}

	Smng::GetIns().Play(SOUND::IKURA, true);

	unit_.isAlive_ = false;
}