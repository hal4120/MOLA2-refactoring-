#pragma once

#include "Bubble.h"
#include <vector>

class BubbleShooter
{
public:
    static constexpr int BUBBLE_NUM = 20;   // 弾の総数（プール）

    BubbleShooter(const Vector2& bossPos, const Vector2& playerPos);
    ~BubbleShooter();

    void Load(void);
    void Init(void);
    void Update(void);
    void Draw(void);
    void Release(void);

    void Shot(void); // 発射処理

    std::vector<Bubble*> Bubbles(void) { return bubbles_; }

    // 発射が終わったかどうか
    const bool End(void) const { return !shot_; }

private:
    int img_;
    std::vector<Bubble*> bubbles_;

    const Vector2& bossPos_;
    const Vector2& playerPos_;

    bool shot_;        // 発射中かどうか
    int shotCount_;    // 発射した数
    int interval_;     // 次の発射までの待ち時間
};