#pragma once

#include<string>

#include"FPS/FPS.h"

#include"Vector2/Vector2.h"
#include"Vector2/Vector2F.h"

class Application
{
private:
	Application();	//コンストラクタ
	~Application();	//デストラクタ

public:
	static constexpr int SCREEN_SIZE_WID = 1000;	//ゲーム画面の横サイズ
	static constexpr int SCREEN_SIZE_HIG = 640;		//ゲーム画面縦サイズ

	static constexpr int DEFAULT_FPS = 60.0f;

	//インスタンスの生成
	static void  CreateInstance(void) { if (instance == nullptr)instance = new Application(); instance->SystemInit(); }
	//インスタンスの取得
	static Application& GetInstance(void) { return *instance; }
	//インスタンスの削除
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }

	void SystemInit(void);						//初期化処理
	void Run(void);								//ゲーム起動
	void Update(void);							//更新処理
	void Draw(void);							//描画処理
	void Release(void);							//解放処理

	//エラー判定
	bool IsError(void);

	//四捨五入
	static int Round(float val) { return static_cast<int>(round(val)); }
	static Vector2 Round(Vector2F val);

private:
	//静的インスタンス
	static Application* instance;

	FPS* fps;

	//エラー情報
	bool errorInfo;

	//BGMに関する変数-----
	int bgm;
	bool bgmflg;
	int clearsound;
	//--------------------


	//画像・音声読み込み関数
	bool Load(void);


	//ポーズ画面に関する変数------------
	int pauseimage[5];
	int selectSound, button;

	bool pause, end;
	bool select;

	int nowEscape, prevEscaoe;
	int nowSpaceKey, prevSpaceKey;

	Vector2 pausegame, pausetitle;
	//----------------------------------
};

