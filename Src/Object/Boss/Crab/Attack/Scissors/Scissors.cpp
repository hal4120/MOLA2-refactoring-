#include "Scissors.h"
#include <DxLib.h>
#include <cmath>

#include "../../../../../Application/Application.h"

#include "../../../../Player/Player.h"
#include "../../../../Boss/BossBase.h"

#include "../../../../../Scene/Game/GameScene.h"

Scissors::Scissors(const Vector2& boss, const Vector2& player)
    : bossPos_(boss),
    playerPos_(player),
    img_(-1),
    end_(false),
    lifeTime_(180)
{
}

Scissors::~Scissors()
{
}

void Scissors::Load(void)
{
    // 画像がある場合はこちらを使用
    Utility::LoadImg(img_, "Data/Image/Boss/Clab/Attack/Scissor.png");
}

void Scissors::Init(void)
{
    unit_.para_.colliShape = CollisionShape::CIRCLE;
    unit_.para_.colliType = CollisionType::ENEMY;

    unit_.isAlive_ = true;
    unit_.para_.radius = RADIUS;
    unit_.para_.speed = 8.0f;
    end_ = false;

    // 発射位置（ボスの手など）
    unit_.pos_ = bossPos_;

    // プレイヤー方向の単位ベクトルを計算
    Vector2 dir = playerPos_ - bossPos_;
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len > 0.0f)
    {
        dir.x /= len;
        dir.y /= len;
    }
    moveDir_ = dir;
}

void Scissors::Update(void)
{
    if (!unit_.isAlive_) return;

    // 移動
    unit_.pos_.x += moveDir_.x * unit_.para_.speed;
    unit_.pos_.y += moveDir_.y * unit_.para_.speed;

    if (unit_.pos_.x < 0 ||
        unit_.pos_.x > Application::SCREEN_SIZE_X ||
        unit_.pos_.y < 0 ||
        unit_.pos_.y > Application::SCREEN_SIZE_Y)
    {
        unit_.isAlive_ = false;
        end_ = true;
    }


    // 寿命カウント
    //if (--lifeTime_ <= 0)
    //{
    //    unit_.isAlive_ = false;
    //    end_ = true;
    //}
}

void Scissors::Draw(void)
{
    if (!unit_.isAlive_) return;

    float angle = atan2f(moveDir_.y, moveDir_.x);

    DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 0.5f, angle, img_, true);
    DrawCircle((int)unit_.pos_.x, (int)unit_.pos_.y, (int)unit_.para_.radius, GetColor(255, 0, 0), true);
}

void Scissors::Release(void)
{
    DeleteGraph(img_);
}

void Scissors::OnCollision(UnitBase* other)
{
    if (dynamic_cast<Parry*>(other)) {
        Vector2 vec = unit_.pos_ - other->GetUnit().pos_;
        if (other->GetUnit().isAlive_) {
            unit_.para_.colliType = CollisionType::ALLY;
            moveDir_ = (vec / vec.length()) * (unit_.para_.speed * 2.0f);
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
