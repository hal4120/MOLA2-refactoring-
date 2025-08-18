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