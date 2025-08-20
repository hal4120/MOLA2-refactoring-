#pragma once
#include "../SceneBase.h"

class SelectScene :
    public SceneBase
{
public:
	enum class BOSS_KINDS {
		NON = -1,
		SHARK,

		MAX,
	};

	SelectScene();
	~SelectScene()override;

	// 読み込み
	void Load(void)override;
	// 初期化処理
	void Init(void)override;
	// 更新ステップ
	void Update(void)override;
	// 描画処理
	void Draw(void)override;
	// 解放処理
	void Release(void)override;

	static const BOSS_KINDS GetNowBoss(void) { return nowBoss_; }

private:
	static BOSS_KINDS nowBoss_;

	int rankingFrameImg_;


	struct KeyInfo { bool prev = false, now = false, down = false, up = false; };
	KeyInfo upKey_;
	KeyInfo downKey_;
	KeyInfo deciKey_;
	void Input(void);
};

using BOSS_KINDS = SelectScene::BOSS_KINDS;
