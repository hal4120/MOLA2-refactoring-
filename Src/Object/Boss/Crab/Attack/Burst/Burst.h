#pragma once
#include "../../../../UnitBase.h"

class Burst : public UnitBase
{
public:
    static constexpr int LIFE_TIME = 600;
    static constexpr int PREPARE_TIME = 90;   // DANGER 表示時間
    static constexpr float SPEED = 25.0f;
    static constexpr int MAX_BOUNCE = 2;      // 2往復（左右4回）

    enum class SIDE {
        LEFT,
        RIGHT,
        MAX
    };

    enum class STATE {
        WARNING,  // 警告中
        ATTACK,   // 移動中
        COOLDOWN  // 壁に到達した後の待機中
    };

    Burst(const Vector2& playerPos);
    ~Burst() override;

    void Load(void) override;
    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;
    void OnCollision(UnitBase* other) override;

    bool End(void) const { return end_; }

private:
    SIDE side_;
    STATE state_;
    const Vector2* playerPos_;
    int timer_;
    int warningTimer_;
    int cooldownTimer_;
    unsigned int color_;
    bool end_;
    float moveDir_;
    int bounceCount_;
    int dengerImg_;
    float fixedY_;
};
