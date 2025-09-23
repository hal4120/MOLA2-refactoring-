#pragma once

#include"../../../../UnitBase.h"

#include <functional>

class SharkTackle : public UnitBase
{
public:
	// 読み込む画像のサイズ(縦・横、一緒)
	static constexpr int LOAD_SIZE = 96;

	// 画像の拡大率(元画像が小さいため拡大して使用する)
	static constexpr float DRAW_SCALE = 4.0f;

	// 最終的に描画される際のサイズ(当たり判定などで使用するサイズ)
	static constexpr float SIZE_X = LOAD_SIZE * DRAW_SCALE;
	static constexpr float SIZE_Y = (LOAD_SIZE * DRAW_SCALE) / 2.0f;


	static constexpr int ANIME_NUM = 6;
	static constexpr int ANIME_INTERVAL = 5;

	static constexpr float MOVE_SPEED = 20.0f;

	static constexpr int STAND_BY_TIME = 120;

	SharkTackle();
	~SharkTackle();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other)override;

	void On(void);

	void EndReset(void) { end_ = false; }
	const bool End(void)const { return end_; }

	void SetDamageFun(std::function<void(void)>ptr) { DamageFunPtr_ = std::move(ptr); }

private:
	int img_[LOAD_SIZE];
	int animeCounter_;
	int animeInterval_;


	bool end_;

	float angle_;

	Vector2 moveVec_;
	void Move(void);

	int standByCounter_;

	bool reverse_;

	enum class DIR_STATE { NON, LEFT, RIGHT, MAX };
	DIR_STATE state_;
	using STATEFUNC = void (SharkTackle::*)(void);
	STATEFUNC stateFuncPtr[(int)DIR_STATE::MAX];

	void Non(void) {};
	void LeftTackle(void);
	void RightTackle(void);

	bool parry_;
	void ParryFunc(void);

	void Animation(void);

	std::function<void(void)>DamageFunPtr_;
};