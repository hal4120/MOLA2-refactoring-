#include "FireBall.h"
#include <DxLib.h>
#include "../../../../../Application/Application.h"
#include "../../../../Player/Player.h"
#include "../../../../Boss/BossBase.h"
#include "../../../../../Scene/Game/GameScene.h"

FireBall::FireBall(const Vector2& boss, const Vector2& player)
    : bossPos_(boss), playerPos_(player), img_(-1), timer_(LIFE_TIME)
{
}

FireBall::~FireBall() {}

void FireBall::Load(void)
{
    Utility::LoadImg(img_, "Data/Image/Boss/Crab/Attack/FireBall.png");
}

void FireBall::Init(void)
{
    unit_.para_.colliShape = CollisionShape::CIRCLE;
    unit_.para_.colliType = CollisionType::ENEMY;
    unit_.para_.radius = RADIUS;
    unit_.para_.speed = SPEED;
    unit_.isAlive_ = true;
    timer_ = LIFE_TIME;

    // 発射方向（プレイヤー方向）
    Vector2 dir = playerPos_ - bossPos_;
    moveVec_ = Utility::Normalize(dir);
    unit_.pos_ = bossPos_;
}

void FireBall::Update(void)
{
    if (!unit_.isAlive_) return;

    // 移動
    unit_.pos_ += moveVec_ * unit_.para_.speed;
    timer_--;

    // === 壁反射処理 ===
    const float left = 0.0f;
    const float right = Application::SCREEN_SIZE_X;
    const float top = 0.0f;
    const float bottom = Application::SCREEN_SIZE_Y;

    bool bounced = false;

    // 左右の壁
    if (unit_.pos_.x - unit_.para_.radius < left)
    {
        unit_.pos_.x = left + unit_.para_.radius;
        moveVec_.x *= -1.0f;
        bounced = true;
    }
    else if (unit_.pos_.x + unit_.para_.radius > right)
    {
        unit_.pos_.x = right - unit_.para_.radius;
        moveVec_.x *= -1.0f;
        bounced = true;
    }

    // 上下の壁
    if (unit_.pos_.y - unit_.para_.radius < top)
    {
        unit_.pos_.y = top + unit_.para_.radius;
        moveVec_.y *= -1.0f;
        bounced = true;
    }
    else if (unit_.pos_.y + unit_.para_.radius > bottom)
    {
        unit_.pos_.y = bottom - unit_.para_.radius;
        moveVec_.y *= -1.0f;
        bounced = true;
    }

    // 跳ね返った瞬間に少し効果をつけたい場合（任意）
    if (bounced)
    {
        // ちょっとスピード減衰 or 音再生など
        unit_.para_.speed *= 0.95f; // ←減衰効果（不要なら消してOK）
        // Smng::GetIns().Play(SOUND::BOUNCE); // 反射音を鳴らすなど
    }

    // 寿命が尽きたら消滅
    if (timer_ <= 0)
        unit_.isAlive_ = false;
}

void FireBall::Draw(void)
{
    if (!unit_.isAlive_) return;
    DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 3.0f, 0.0f, img_, true);
    DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.para_.radius, 0xffffff, true);
}

void FireBall::Release(void)
{
    DeleteGraph(img_);
}

void FireBall::OnCollision(UnitBase* other)
{
    if (dynamic_cast<Parry*>(other)) {
        Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
        if (other->GetUnit().isAlive_) {
            unit_.para_.colliType = CollisionType::ALLY;
            moveVec_ = (vec / vec.length()) * unit_.para_.speed / 2;
            GameScene::HitStop(10);
        }
        return;
    }

    if (dynamic_cast<Player*>(other)) {
        unit_.isAlive_ = false;
        GameScene::HitStop(10);
        return;
    }

    if (dynamic_cast<BossBase*>(other)) {
        unit_.isAlive_ = false;
        GameScene::HitStop(10);
    }
}
