#pragma once
#include"../SceneBase.h"

class StageBase;

class TitleShark;
class TitleMonkfish;
class TitlePlayer;

class TitleScene : public SceneBase
{
public:
	enum class SELECT { START, END, MAX };


	TitleScene();
	~TitleScene()override;

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

private:
	StageBase* stage_;
	TitleShark* shark_;
	TitleMonkfish* fish_;
	TitlePlayer* player_;

	int rogoImg_;
	
	SELECT nowSelect_;
	int selectImg_[(int)SELECT::MAX];
	int arrowImg_;

	bool prevSelectKey_, nowSelectKey_, downSelectKey_, upSelectKey_;
	bool prevDeciKey_, nowDeciKey_, downDeciKey_, upDeciKey_;
	void Input(void);
};