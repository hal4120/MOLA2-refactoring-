#pragma once
#include "../SceneBase.h"

class SelectScene :
    public SceneBase
{
public:
	enum class BOSS_KINDS {
		NON,

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

};

using BOSS_KINDS = SelectScene::BOSS_KINDS;
