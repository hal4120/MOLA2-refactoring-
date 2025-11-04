#include "BounceBall.h"
#include <DxLib.h>
#include "../../../../../Application/Application.h"
#include "../../../../Player/Player.h"
#include "../../../../Boss/BossBase.h"
#include "../../../../../Scene/Game/GameScene.h"

BounceBall::BounceBall(const Vector2& boss, const Vector2& player)
    : bossPos_(boss), playerPos_(player), img_(), bounceCount_(0)
{
}

BounceBall::~BounceBall() {}

void BounceBall::Load(void)
{
    //Utility::LoadImg(img_, "Data/Image/Boss/Crab/Attack/Bound.png");
    Utility::LoadArrayImg(
        "Data/Image/Boss/Crab/Attack/Bound.png",
        IMG_NUM_MAX, 
        IMG_NUM_X, IMG_NUM_Y,
        IMG_SIZE_X, IMG_SIZE_Y, 
        img_);
}

void BounceBall::Init(void)
{
    unit_.para_.colliShape = CollisionShape::CIRCLE;
    unit_.para_.colliType = CollisionType::ENEMY;
    unit_.para_.radius = RADIUS;
    unit_.para_.speed = SPEED;
    unit_.isAlive_ = true;
    bounceCount_ = 0;

    // 発射方向（プレイヤー方向）
    Vector2 dir = playerPos_ - bossPos_;
    moveVec_ = Utility::Normalize(dir);
    unit_.pos_ = bossPos_;
}

void BounceBall::Update(void)
{
    if (!unit_.isAlive_) return;

    // 移動
    unit_.pos_ += moveVec_ * unit_.para_.speed;

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

    // 跳ね返った瞬間の処理
    if (bounced)
    {
        bounceCount_++;               // 跳ね返り回数カウント
        unit_.para_.speed *= 0.95f;   // 減衰（お好みで）
        // Smng::GetIns().Play(SOUND::BOUNCE);
    }

    // 一定回数跳ね返ったら消滅
    if (bounceCount_ >= MAX_BOUNCE_COUNT)
        unit_.isAlive_ = false;
}


void BounceBall::Draw(void)
{
    if (!unit_.isAlive_) return;
    static int i = 0;
    if (i < IMG_NUM_MAX) {
        i++;
    }
    else {
        i = 0;
    }

    if (unit_.para_.colliType == CollisionType::ENEMY) {
        SetDrawBright(255, 0, 0);
        DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 1.5f, 0.0f, img_[i], true);
        SetDrawBright(255, 255, 255);
    }
    else {
        DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 1.5f, 0.0f, img_[i], true);
    }

#ifdef _DEBUG
    DrawCircle(unit_.pos_.x, unit_.pos_.y, unit_.para_.radius, 0xffffff, false);
#endif // _DEBUG
}

void BounceBall::Release(void)
{
    for (int i = 0; i < IMG_NUM_MAX; i++) {
        DeleteGraph(img_[i]);
    }
}

void BounceBall::OnCollision(UnitBase* other)
{
    if (dynamic_cast<Parry*>(other)) {
        Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
        if (other->GetUnit().isAlive_) {
            unit_.para_.colliType = CollisionType::ALLY;
            moveVec_ = (vec / vec.length()) * unit_.para_.speed / 3;
            bounceCount_ = 0;
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
