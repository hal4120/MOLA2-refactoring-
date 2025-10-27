#pragma once

#include "Bubble.h"
#include <vector>

class BubbleShooter
{
public:
    static constexpr int BUBBLE_NUM = 20;   // �e�̑����i�v�[���j

    BubbleShooter(const Vector2& bossPos, const Vector2& playerPos);
    ~BubbleShooter();

    void Load(void);
    void Init(void);
    void Update(void);
    void Draw(void);
    void Release(void);

    void Shot(void); // ���ˏ���

    std::vector<Bubble*> Bubbles(void) { return bubbles_; }

    // ���˂��I��������ǂ���
    const bool End(void) const { return !shot_; }

private:
    int img_;
    std::vector<Bubble*> bubbles_;

    const Vector2& bossPos_;
    const Vector2& playerPos_;

    bool shot_;        // ���˒����ǂ���
    int shotCount_;    // ���˂�����
    int interval_;     // ���̔��˂܂ł̑҂�����
};