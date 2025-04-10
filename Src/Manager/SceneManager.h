#pragma once

#include"../StDefineData.h"

class Fader;
class TitleScene;
class Score;
class ModeSelect;
class GameScene;
class GameOverScene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	//インスタンスの生成
	static void CreateInstance(void) { if (instance == nullptr)instance = new SceneManager(); instance->SystemInit(); }
	//インスタンスの取得
	static SceneManager& GetInstance(void) { return *instance; }
	//インスタンスの消去
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }



	bool SystemInit(void);						//初期化処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理
	bool Release(void);							//解放処理



private:
	//静的インスタンス
	static SceneManager* instance;

	TitleScene* titleInst;						//タイトルクラスのインスタンス
	Score* scoreInst;							//スコア画面クラスのインスタンス
	ModeSelect* modeselectInst;
	GameScene* gameInst;						//ゲームシーンクラスのインスタンス
	GameOverScene* gameover;
	Fader* fader;								//フェードクラスのインスタンス

	E_SCENE_ID scene_ID;						//現在のシーン

	E_SCENE_ID waitScene;
	bool sceneChangeFlg;

	bool ChangeScene(E_SCENE_ID id);
	void ReleaseScene(E_SCENE_ID id);

};

