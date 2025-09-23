#pragma once
#include "../UnitBase.h"

#include"../../Application/Application.h"

#include"Parry/Parry.h"
#include"Special/PlayerLaser.h"

enum class DIR { RIGHT, LEFT };

class Player : public UnitBase
{
public:
	// 読み込む画像の枚数
	static constexpr int ANIM_NUM_X = 7;
	static constexpr int ANIM_NUM_Y = 1;
	static constexpr int ANIM_NUM = ANIM_NUM_X * ANIM_NUM_Y;

	// 読み込む画像の大きさ
	static constexpr int LOAD_SIZE_X = 42;
	static constexpr int LOAD_SIZE_Y = 66;

	// アニメーションのスピード(何フレームに１回アニメを動かすか)
	static constexpr int ANIM_SPEED = 5;

	// 状態
	enum STATE { DEFAULT, SPECIAL, DEATH, OVER, MAX };

	// 初期座標
	const Vector2 START_POS = { 50.0f,Application::SCREEN_SIZE_Y / 2 };

	// 移動速度
	static constexpr float SPEED = 8.0f;

	// ライフ
	static constexpr int LIFE_MAX = 5;

	// スペシャル攻撃のチャージ必要量
	static constexpr int SPECIAL_CHARGE_MAX = 20;

    Player();
    ~Player();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void UIDraw(void);
	void Release(void)override;

	void OnCollision(UnitBase* other);

	Parry* ParryIns(void) { return parry_; }
	PlayerLaser* LaserIns(void) { return laser_; }

	void SpecialCharge(void) { if (++specialCharge_ > SPECIAL_CHARGE_MAX) { specialCharge_ = SPECIAL_CHARGE_MAX; } }

	const bool CollisionValid(void)const { return state_ != STATE::DEATH; }

	const bool GameOver(void)const { return gameEnd_; }
private:
	// 画像ハンドル
	int img_[ANIM_NUM];

	// アニメーションカウンター
	int animCounter_;
	int animInterval_;

	// 回転量
	float angle_;

	// 向き
	DIR dir_;

	// アニメーション処理
	void Animation(void);

	// ステート
	STATE state_;

	// ステート別の関数のポインタで格納する変数
	void (Player::* stateFuncPtr_[STATE::MAX])(void);

	// ステート別の関数
	void Default(void);
	void Special(void);
	void Death(void);
	void Over(void);

	// ノックバック関係
	Vector2 knockBackVec_;

	Parry* parry_;
	PlayerLaser* laser_;

	int specialCharge_;
	int specialChargeImg_[SPECIAL_CHARGE_MAX + 1];
	int specialChargeMaxImg_;
	int specialChargeMaxFlash_;
	int specialChargeMaxButtonImg_[2];
	int specialChargeMaxKeyImg_[2];

	bool gameEnd_;

	int uiImg_;
	int	lifeImg_[LIFE_MAX + 1];
};