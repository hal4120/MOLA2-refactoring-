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

	int rankingFrameImg_;


	struct KeyInfo { bool prev = false, now = false, down = false, up = false; };
	KeyInfo upKey_;
	KeyInfo downKey_;
	KeyInfo deciKey_;
	void Input(void);
};

using BOSS_KINDS = SelectScene::BOSS_KINDS;
