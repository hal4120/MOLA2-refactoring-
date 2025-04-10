#pragma once
#include"../StDefineData.h"
#include"../Vector2/Vector2.h"

class TitleScene
{
public:
	static constexpr int HIG = 562;
	 
	TitleScene(void);
	~TitleScene(void);

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);

	E_SCENE_ID GetNextSceneID(void);

private:
	Vector2 pos;
	int image;		//背景画像ハンドル番号

	E_SCENE_ID nextSceneID;		//次に遷移するシーンのID

	int prevSpaceKey, nowSpaceKey;
	int prevPadKey, nowPadKey;

};
