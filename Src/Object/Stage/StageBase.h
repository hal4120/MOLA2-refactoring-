#pragma once

#include"../UnitBase.h"

#include<vector>

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
	// 変数
	int backImg_;
	int backDecorationImg_;
	Vector2 poss_[ARRANGEMENT::MAX];
	//---------------------

	// 装飾オブジェクト情報の構造体
	struct OBJECT
	{
		Vector2 pos;
		Vector2 move;
	};

	// 装飾オブジェクト１つ目--
	// 定数
	int object1SizeX;
	int object1SizeY;
	int object1Num;
	float object1MaxSpeed;
	// 変数
	int object1Img_;
	std::vector<OBJECT> object1Info_;
	//--------------------------

	// 装飾オブジェクト２つ目--
	// 定数
	int object2SizeX;
	int object2SizeY;
	int object2Num;
	float object2MaxSpeed;
	// 変数
	int object2Img_;
	std::vector<OBJECT> object2Info_;
	//-------------------------

	Vector2 moveVec_;

	// ステージギミッククラスのインスタンスを入れる配列
	std::vector<UnitBase*>gimics_;
};

