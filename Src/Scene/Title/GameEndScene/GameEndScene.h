#pragma once

#include"../../SceneBase.h"

class GameEndScene : public SceneBase
{
public:
	enum class SELECT { YES, NO, MAX };

	GameEndScene();
	~GameEndScene()override;
	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

private:
	int windowImg_[(int)SELECT::MAX];
	SELECT nowSelect_;

	struct KeyInfo { bool prev = false, now = false, down = false, up = false; };
	KeyInfo upKey_;
	KeyInfo downKey_;
	KeyInfo deciKey_;
	void Input(void);
};