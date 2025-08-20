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

		MAX,
	};

	SelectScene();
	~SelectScene()override;

	// �ǂݍ���
	void Load(void)override;
	// ����������
	void Init(void)override;
	// �X�V�X�e�b�v
	void Update(void)override;
	// �`�揈��
	void Draw(void)override;
	// �������
	void Release(void)override;

	static const BOSS_KINDS GetNowBoss(void) { return nowBoss_; }

private:
	static BOSS_KINDS nowBoss_;

	SelectPlayer* player_;
	StageBase* stage_;

	std::vector<int>selectImgs_[(int)BOSS_KINDS::MAX];
	int selectAnimeCounter_;
	int selectAnimeInterval_;
	Vector2I selectObjPos_;
	float selectObjAngle_;
	bool selectObjParry_;

	const Vector2I SELECT_OBJ_POS_DEFAULT = { 550,600 };

	int rankingFrameImg_;

	const Vector2I RANKING_POS = { 1150,225 };
	static constexpr int RANKING_POS_Y_SPACE = 120;

	struct KeyInfo { bool prev = false, now = false, down = false, up = false; };
	KeyInfo upKey_;
	KeyInfo downKey_;
	void Input(void);
};

using BOSS_KINDS = SelectScene::BOSS_KINDS;
