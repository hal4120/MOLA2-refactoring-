#pragma once
#include "../../../../UnitBase.h"

class FireBall : public UnitBase
{
public:
    static constexpr float RADIUS = 40.0f;
    static constexpr float SPEED = 12.0f;
    static constexpr int LIFE_TIME = 180;

    FireBall(const Vector2& boss, const Vector2& player);
    ~FireBall() override;

    void Load(void) override;
    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

    void OnCollision(UnitBase* other) override;
    bool End(void) const { return !unit_.isAlive_; }

private:
    int img_;
    int timer_;
    Vector2 moveVec_;
    const Vector2& bossPos_;
    const Vector2& playerPos_;
};
