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

	// �w�i----------------
	// �萔
	int backSizeX; 
	int backSizeY;
	float backScrollSpeed;
	float backDecorationScrollSpeed;
	// �ϐ�
	int backImg_;
	int backDecorationImg_;
	Vector2 poss_[ARRANGEMENT::MAX];
	Vector2 backDecorationPoss_[ARRANGEMENT::MAX];
	//---------------------

	/// <summary>
	/// �w�i�X�N���[��
	/// </summary>
	/// <param name="poss">���W�z��</param>
	/// <param name="scrollSpeed">�X�N���[���X�s�[�h</param>
	void BackScroll(Vector2 *poss,float scrollSpeed);

	// �����I�u�W�F�N�g���̍\����------
	struct OBJECT_INFO
	{
		Vector2 pos;
		Vector2 move;
	};

	struct OBJECT
	{
		// �萔(�h����Ŏw��)
		int objectSizeX;
		int objectSizeY;
		int objectNum;
		float objectMaxSpeed;
		int objectImg;
		
		// �ϐ�
		std::vector<OBJECT_INFO>info;
	};
	//------------------------------------

	std::vector<OBJECT> objects_;
	/// <summary>
	/// �����I�u�W�F�N�g�̐V�K�쐬(�h����Ŏg�p)
	/// </summary>
	/// <param name="path">�摜�p�X</param>
	/// <param name="sizeX">���T�C�Y</param>
	/// <param name="sizeY">�c�T�C�Y</param>
	/// <param name="num">�����o����</param>
	/// <param name="maxSpeed">�ő呬�x</param>
	void NewObject(std::string path,int sizeX, int sizeY, int num, float maxSpeed);

	/// �I�u�W�F�N�g�̃X�N���[��
	void ObjectScroll(void);


	Vector2 moveVec_;

	// �X�e�[�W�M�~�b�N�N���X�̃C���X�^���X������z��
	std::vector<UnitBase*>gimics_;
};

