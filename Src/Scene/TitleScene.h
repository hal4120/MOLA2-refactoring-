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
	int image;		//�w�i�摜�n���h���ԍ�

	E_SCENE_ID nextSceneID;		//���ɑJ�ڂ���V�[����ID

	int prevSpaceKey, nowSpaceKey;
	int prevPadKey, nowPadKey;

};
