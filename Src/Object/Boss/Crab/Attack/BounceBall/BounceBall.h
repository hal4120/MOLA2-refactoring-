#pragma once
#include "../../../../UnitBase.h"

class BounceBall : public UnitBase
{
public:
    static constexpr float RADIUS = 40.0f;
    static constexpr float SPEED = 12.0f;

    static constexpr int IMG_NUM_MAX = 22;
    static constexpr int IMG_NUM_X = 5;
    static constexpr int IMG_NUM_Y = 5;
    static constexpr int IMG_SIZE_X = 960 / 5;
    static constexpr int IMG_SIZE_Y = 960 / 5;

    BounceBall(const Vector2& boss, const Vector2& player);
    ~BounceBall() override;

    void Load(void) override;
    void Init(void) override;
    void Update(void) override;
    void Draw(void) override;
    void Release(void) override;

    void OnCollision(UnitBase* other) override;
    bool End(void) const { return !unit_.isAlive_; }

private:
    int img_[22];
    Vector2 moveVec_;
    const Vector2& bossPos_;
    const Vector2& playerPos_;

    int bounceCount_;              // íµÇÀï‘ÇËâÒêî
    static const int MAX_BOUNCE_COUNT = 3; // è¡ñ≈Ç‹Ç≈ÇÃç≈ëÂâÒêî

};
