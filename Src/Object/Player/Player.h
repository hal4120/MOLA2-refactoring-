#pragma once
#include "../UnitBase.h"

class Parry;

class Player :
    public UnitBase
{
public:
	// 読み込む画像の大きさ
	static constexpr int LOAD_SIZE_X = 42;
	static constexpr int LOAD_SIZE_Y = 66;

	// 読み込む画像の枚数
	static constexpr int LOAD_NUM_X = 7;
	static constexpr int LOAD_NUM_Y = 1;

	// アニメーションの数
	static constexpr int ANIM_NUM = LOAD_NUM_X * LOAD_NUM_Y;

	// アニメーションのスピード(何フレームに１回アニメを動かすか)
	static constexpr int ANIM_SPEED = 5;

	enum STATE { MOVE, ATTACK, SPECIAL, DEATH, MAX };

	// 初期座標
	const Vector2 START_POS = { 50.0f,50.0f };

    Player();
    ~Player();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	// 画像ハンドル
	int img_[ANIM_NUM];

	// アニメーションカウンター
	int animCounter_;
	int animInterval_;

	// アニメーション処理
	void Animation(void);

	// ステート
	STATE state_;

	// ステート別の関数のポインタで格納する変数
	void (Player::* stateFuncPtr_[STATE::MAX])(void);

	// ステート別の関数
	void Move(void);
	void Attack(void);
	void Special(void);
	void Death(void);


	// 入力情報管理
	struct InputInfo
	{
		bool prev_ = false;
		bool now_ = false;
		bool upTrg_ = false;
		bool downTrg_ = false;
	};
	InputInfo up_, down_, left_, right_;
	InputInfo attackKey_;
	InputInfo specialKey_;

	void Input(void);

	Parry* parry_;
};