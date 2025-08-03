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

	// �w�i----------------
	// �萔
	int backSizeX; 
	int backSizeY;
	float backScrollSpeed;
	// �ϐ�
	int backImg_;
	int backDecorationImg_;
	Vector2 poss_[ARRANGEMENT::MAX];
	//---------------------

	// �����I�u�W�F�N�g���̍\����
	struct OBJECT
	{
		Vector2 pos;
		Vector2 move;
	};

	// �����I�u�W�F�N�g�P��--
	// �萔
	int object1SizeX;
	int object1SizeY;
	int object1Num;
	float object1MaxSpeed;
	// �ϐ�
	int object1Img_;
	std::vector<OBJECT> object1Info_;
	//--------------------------

	// �����I�u�W�F�N�g�Q��--
	// �萔
	int object2SizeX;
	int object2SizeY;
	int object2Num;
	float object2MaxSpeed;
	// �ϐ�
	int object2Img_;
	std::vector<OBJECT> object2Info_;
	//-------------------------

	Vector2 moveVec_;

	// �X�e�[�W�M�~�b�N�N���X�̃C���X�^���X������z��
	std::vector<UnitBase*>gimics_;
};

