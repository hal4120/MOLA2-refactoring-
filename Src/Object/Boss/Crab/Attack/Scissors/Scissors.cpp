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
    lifeTime_(180),
    isReturn_(false)
{
}

Scissors::~Scissors()
{
}

void Scissors::Load(void)
{
    // 画像がある場合はこちらを使用
    Utility::LoadImg(img_, "Data/Image/Boss/Crab/Attack/Scissor.png");
}

void Scissors::Init(void)
{
    unit_.para_.colliShape = CollisionShape::CIRCLE;
    unit_.para_.colliType = CollisionType::ENEMY;

    unit_.isAlive_ = true;
    unit_.para_.radius = RADIUS;
    unit_.para_.speed = 10.0f;
    end_ = false;

    isReturn_ = false;

    // 発射位置（ボスの手など）
    unit_.pos_ = bossPos_;

    // プレイヤー方向の単位ベクトルを計算
    Vector2 vec = playerPos_ - bossPos_;
    float len = Utility::Magnitude(vec);
    if (len > 0.0f)
    {
        moveVec_ = Utility::Normalize(vec);
    }
    //moveVec_ = vec;
}

void Scissors::Update(void)
{
    // 移動
    unit_.pos_ += moveVec_ * unit_.para_.speed;

    if (!unit_.isAlive_ || unit_.para_.colliType == CollisionType::ALLY) { return; }

    // 現在の距離を計算
    float distOrigin = Utility::Distance(unit_.pos_, bossPos_);

    if (!isReturn_ && distOrigin > RETURN_DISTANCE) {
        isReturn_ = true;
    }

    if (isReturn_) {
        Vector2 toBoss = Utility::Normalize(bossPos_ - unit_.pos_);

        float angleNow = atan2f(moveVec_.y, moveVec_.x);
        float angleTarget = atan2f(toBoss.y, toBoss.x);
        float angleDiff = angleTarget - angleNow;

        if (angleDiff > DX_PI_F) angleDiff -= DX_PI_F * 2.0f;
        if (angleDiff < -DX_PI_F) angleDiff += DX_PI_F * 2.0f;

        float turnSpeed = 0.08f;
        angleNow += angleDiff * turnSpeed;

        moveVec_.x = cosf(angleNow);
        moveVec_.y = sinf(angleNow);

        if (distOrigin < 30.0f) {
            unit_.isAlive_ = false;
            end_ = true;
        }
    }

    // 画面外チェック
    if (unit_.para_.colliType == CollisionType::ALLY &&
        (unit_.pos_.x < 0 || unit_.pos_.x > Application::SCREEN_SIZE_X ||
        unit_.pos_.y < 0 || unit_.pos_.y > Application::SCREEN_SIZE_Y))
    {
        unit_.isAlive_ = false;
        end_ = true;
    }
}

void Scissors::Draw(void)
{
    if (!unit_.isAlive_) return;

    static float rota = 0;

    rota -= Utility::Deg2RadF(10.0f);
    if (rota > DX_PI_F * 2) {
        rota = 0;
    }

    //DrawCircle((int)unit_.pos_.x, (int)unit_.pos_.y, (int)unit_.para_.radius, GetColor(255, 0, 0), true);
    DrawRotaGraph(unit_.pos_.x, unit_.pos_.y, 4.0f, rota, img_, true, true);
}

void Scissors::Release(void)
{
    DeleteGraph(img_);
}

void Scissors::OnCollision(UnitBase* other)
{
    if (end_) { return; }
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
