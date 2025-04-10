#pragma once
#include"../StDefineData.h"
#include"../Vector2/Vector2.h"

class Score
{
public:
	static constexpr int RANKING_MAX = 5;

	Score();
	~Score();

	bool SystemInit(void);
	void GameInit(void);
	void Update(void);
	void Draw(void);
	bool Release(void);


	E_SCENE_ID GetNextSceneID(void) { return nextSceneID; }

	void RankingUpdate(MODE_ID id, float t);

private:
	int haikeiimage;

	float normaltimescore[RANKING_MAX];
	float hardtimescore[RANKING_MAX];

	Vector2 pos;

	E_SCENE_ID nextSceneID;		//éüÇ…ëJà⁄Ç∑ÇÈÉVÅ[ÉìÇÃID

	int prevSpaceKey, nowSpaceKey;

	int prevPadKey, nowPadKey;

};
