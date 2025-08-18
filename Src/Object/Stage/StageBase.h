#pragma once

#include"../UnitBase.h"

#include<vector>
#include<string>

class StageBase
{
public:
	enum ARRANGEMENT { CENTER1, CENTER2, RIGHT, LEFT, MAX };
	static constexpr int CENTER_NUM = 2;

	StageBase();
	virtual ~StageBase();

	virtual void Load(void) = 0;
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	std::vector<UnitBase*>GetGimicIns(void) { return gimics_; }
protected:

	// 背景----------------
	// 定数
	int backSizeX; 
	int backSizeY;
	float backScrollSpeed;
	float backDecorationScrollSpeed;
	// 変数
	int backImg_;
	int backDecorationImg_;
	Vector2 poss_[ARRANGEMENT::MAX];
	Vector2 backDecorationPoss_[ARRANGEMENT::MAX];
	//---------------------

	/// <summary>
	/// 背景スクロール
	/// </summary>
	/// <param name="poss">座標配列</param>
	/// <param name="scrollSpeed">スクロールスピード</param>
	void BackScroll(Vector2 *poss,float scrollSpeed);

	// 装飾オブジェクト情報の構造体------
	struct OBJECT_INFO
	{
		Vector2 pos;
		Vector2 move;
	};

	struct OBJECT
	{
		// 定数(派生先で指定)
		int objectSizeX;
		int objectSizeY;
		int objectNum;
		float objectMaxSpeed;
		int objectImg;
		
		// 変数
		std::vector<OBJECT_INFO>info;
	};
	//------------------------------------

	std::vector<OBJECT> objects_;
	/// <summary>
	/// 装飾オブジェクトの新規作成(派生先で使用)
	/// </summary>
	/// <param name="path">画像パス</param>
	/// <param name="sizeX">横サイズ</param>
	/// <param name="sizeY">縦サイズ</param>
	/// <param name="num">同時出現個数</param>
	/// <param name="maxSpeed">最大速度</param>
	void NewObject(std::string path,int sizeX, int sizeY, int num, float maxSpeed);

	/// オブジェクトのスクロール
	void ObjectScroll(void);


	Vector2 moveVec_;

	// ステージギミッククラスのインスタンスを入れる配列
	std::vector<UnitBase*>gimics_;
};

