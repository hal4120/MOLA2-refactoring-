#pragma once
#include "../SceneBase.h"

#include"../../Common/Vector2.h"

#include<vector>

class SelectPlayer;
class StageBase;

class SelectScene :
    public SceneBase
{
public:
	enum class BOSS_KINDS {
		NON = -1,
		SHARK,
		SHARK_HARD,
		KRAKEN,
		CRAB,

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

	SelectPlayer* player_;
	StageBase* stage_;

	std::vector<int>selectObjImgs_[(int)BOSS_KINDS::MAX];
	int selectAnimeCounter_;
	int selectAnimeInterval_;
	Vector2I selectObjPos_;
	float selectObjAngle_;
	bool selectObjParry_;

	const Vector2I SELECT_OBJ_POS_DEFAULT = { 550,600 };

	static constexpr int SELECT_OBJ_SIZE_Y = 480;

	int arrowImg_;

	int selectImg_;

	int rankingFrameImg_;

	const Vector2I RANKING_POS = { 1226,210 };
	static constexpr int RANKING_POS_Y_SPACE = 112;

	struct KeyInfo { bool prev = false, now = false, down = false, up = false; };
	KeyInfo upKey_;
	KeyInfo downKey_;
	KeyInfo titleBackKey_;

	enum NUMBER_NAME { ONE,TWO,THREE,FOUR,FIVE,MAX };
	KeyInfo numberKey_[NUMBER_NAME::MAX];
	static constexpr int NUMBERS_KEY[NUMBER_NAME::MAX] = { 2,3,4,5,6 };

	void Input(void);


	void RankingReset(void);

};

using BOSS_KINDS = SelectScene::BOSS_KINDS;
