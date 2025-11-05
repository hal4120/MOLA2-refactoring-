#include "UFO.h"
#include "../../../../../Application/Application.h"

#include "../../../../Player/Parry/Parry.h"
#include "../../Crab.h"
#include <DxLib.h>
#include <cmath>

UFO::UFO(const Vector2& playerPos)
    : playerPos_(&playerPos),
    side_(SIDE::RIGHT),
    timer_(0),
    color_(GetColor(255, 0, 0)),
    moveDir_(-1.0f),
    bounceCount_(0),
    state_(STATE::WARNING),
    warningTimer_(0),
    cooldownTimer_(0),
    fixedY_(0.0f)
{
}

UFO::~UFO() {}

void UFO::Load(void)
{
    dengerImg_ = LoadGraph("Data/Image/Boss/Crab/Attack/Denger.png");
    burstImg_ = LoadGraph("Data/Image/Boss/Crab/Attack/UFO.png");
}

void UFO::Init(void)
{
    unit_.isAlive_ = true;
    end_ = false;
    timer_ = LIFE_TIME;
    bounceCount_ = 0;
    state_ = STATE::WARNING;
    warningTimer_ = 0;
    cooldownTimer_ = 0;

    unit_.para_.colliShape = CollisionShape::RECTANGLE;
    unit_.para_.colliType = CollisionType::ENEMY;
    unit_.para_.size = { 450.0f, 200.0f };

    side_ = (SIDE)GetRand((int)SIDE::MAX - 1);

    if (side_ == SIDE::RIGHT)
    {
        unit_.pos_.x = Application::SCREEN_SIZE_X; // 右端外
        moveDir_ = -1.0f;
    }
    else
    {
        unit_.pos_.x = -unit_.para_.size.x; // 左端外
        moveDir_ = 1.0f;
    }

    fixedY_ = playerPos_->y;
    unit_.pos_.y = fixedY_;
    unit_.para_.speed = SPEED;
}

void UFO::Update(void)
{
    if (!unit_.isAlive_) return;

    switch (state_)
    {
        // ===== DANGER フェーズ =====
    case STATE::WARNING:
        warningTimer_++;
        // 警告中はプレイヤーの高さを追従
        fixedY_ = playerPos_->y - unit_.para_.size.y / 2.0f;
        unit_.pos_.y = fixedY_;

        unit_.para_.colliType = CollisionType::ENEMY;

        if (warningTimer_ >= PREPARE_TIME)
        {
            warningTimer_ = 0;
            state_ = STATE::ATTACK;
        }
        break;

        // ===== 攻撃フェーズ =====
    case STATE::ATTACK:
        unit_.pos_.x += unit_.para_.speed * moveDir_;

        if (unit_.pos_.x <= -unit_.para_.size.x)
        {
            unit_.pos_.x = -unit_.para_.size.x;
            moveDir_ *= -1.0f;
            bounceCount_++;
            state_ = STATE::COOLDOWN;
            cooldownTimer_ = 0;
        }
        else if (unit_.pos_.x >= Application::SCREEN_SIZE_X + unit_.para_.size.x)
        {
            unit_.pos_.x = Application::SCREEN_SIZE_X + unit_.para_.size.x;
            moveDir_ *= -1.0f;
            bounceCount_++;
            state_ = STATE::COOLDOWN;
            cooldownTimer_ = 0;
        }

        // 寿命・往復回数チェック
        if (bounceCount_ >= MAX_BOUNCE || --timer_ <= 0)
        {
            unit_.isAlive_ = false;
            end_ = true;
        }
        break;

        // ===== クールダウンフェーズ =====
    case STATE::COOLDOWN:
        cooldownTimer_++;
        // 少しディレイを置いて再警告
        if (cooldownTimer_ > 30) // 0.5秒くらいの間
        {
            state_ = STATE::WARNING;
            warningTimer_ = 0;
        }
        break;
    }

}

template <typename T>
T Clamp(const T& value, const T& min, const T& max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

void UFO::Draw(void)
{
    if (!unit_.isAlive_) return;

    if (state_ == STATE::WARNING)
    {
        float alpha = (std::sin(warningTimer_ * 0.25f) * 0.5f + 0.5f) * 255.0f;
        SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alpha));

        int drawX = (moveDir_ > 0) ? 100 : Application::SCREEN_SIZE_X - 100; // 左向き = 右から出るので右に警告

        DrawRotaGraph(drawX,
            static_cast<int>(fixedY_),
            0.2f, 0.0f, dengerImg_, true);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
        return;
    }

#ifdef _DEBUG
    DrawOvalAA(unit_.pos_.x, unit_.pos_.y,
        unit_.para_.size.x / 2, unit_.para_.size.y / 2,
        30, color_, false);
#endif // _DEBUG

    for (int i = -10; i <= 10; i += 10)
    {
        DrawLine(0, unit_.pos_.y + i, Application::SCREEN_SIZE_X, unit_.pos_.y + i, 0xff0000, true);
    }

    DrawRotaGraph(
        unit_.pos_.x, unit_.pos_.y,
        2.0f, 0.0f, burstImg_,
        true
    );
}

void UFO::Release(void)
{
    DeleteGraph(dengerImg_);
}

void UFO::OnCollision(UnitBase* other)
{
    if (dynamic_cast<Parry*>(other)) {
        if (other->GetUnit().isAlive_) {
            moveDir_ = moveDir_ * -1;
            unit_.para_.colliType = CollisionType::ALLY;
        }
    }

    if (dynamic_cast<Crab*> (other)) {
        end_ = true;
    }
}
