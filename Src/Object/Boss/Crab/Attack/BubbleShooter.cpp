#include "BubbleShooter.h"
#include <DxLib.h>

BubbleShooter::BubbleShooter(const Vector2& bossPos, const Vector2& playerPos)
    : bossPos_(bossPos)
    , playerPos_(playerPos)
    , img_(-1)
    , shot_(false)
    , shotCount_(0)
    , interval_(0)
{
}

BubbleShooter::~BubbleShooter()
{
    Release();
}

void BubbleShooter::Load(void)
{
    // バブル画像をロードする（仮：白円なので不要なら消してOK）
    img_ = LoadGraph("Data/Image/Bubble.png");

    bubbles_.reserve(BUBBLE_NUM);
    for (int i = 0; i < BUBBLE_NUM; i++) {
        bubbles_.emplace_back(new Bubble(img_));
        bubbles_.back()->Load();
    }
}

void BubbleShooter::Init(void)
{
    for (auto& b : bubbles_) {
        b->Init();
    }
    shot_ = true;
    shotCount_ = 0;
    interval_ = 0;
}

void BubbleShooter::Update(void)
{
    for (auto& b : bubbles_) {
        b->Update();
    }
}

void BubbleShooter::Draw(void)
{
    for (auto& b : bubbles_) {
        b->Draw();
    }
}

void BubbleShooter::Release(void)
{
    for (auto& b : bubbles_) {
        b->Release();
    }
    bubbles_.clear();
}

void BubbleShooter::Shot(void)
{
    if (!shot_) return;
    if (interval_ > 0) { interval_--; return; }

    // 発射方向（プレイヤー方向）
    Vector2 dir = playerPos_ - bossPos_;
    float len = sqrtf(dir.x * dir.x + dir.y * dir.y);
    if (len != 0.0f) {
        dir.x /= len;
        dir.y /= len;
    }

    const int SHOT_NUM = 5;   // 1回に撃つ弾数
    const float ANGLE_RANGE = DX_PI_F / 12.0f; // ±15度

    int fired = 0; // 実際に撃てた数

    for (int i = 0; i < SHOT_NUM; i++) {
        float offset = (GetRand(300) / 100.0f - 1.5f) * ANGLE_RANGE;
        float cosA = cosf(offset);
        float sinA = sinf(offset);

        Vector2 shotDir;
        shotDir.x = dir.x * cosA - dir.y * sinA;
        shotDir.y = dir.x * sinA + dir.y * cosA;

        // 空いてるバブルを探して撃つ
        for (auto& b : bubbles_) {
            if (!b->GetUnit().isAlive_) {
                b->Shot(bossPos_, shotDir);
                shotCount_++;
                fired++;
                break; // 1個確保できたら次の弾へ
            }
        }
    }

    // 全弾撃てなかった場合 → 発射終了
    if (fired < SHOT_NUM) {
        shot_ = false;
        return;
    }

    interval_ = 30; // 次の発射までの間隔

    if (shotCount_ >= BUBBLE_NUM) {
        shot_ = false; // 全弾撃ち終えたら終了
    }
}
