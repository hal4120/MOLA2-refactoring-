#pragma once

#include"../Common/Vector2.h"

#include"../Utility/Utility.h"

struct Base
{
	//�p�����[�^�[
	struct {
		enum CollisionPara { NON = -1, CIRCLE, RECT, ELLIPSE, CAPSULE, MAX };
		CollisionPara colliType_ = CollisionPara::NON;	//�����蔻��̑���
		Vector2 size = { -1.0f,-1.0f };					//�T�C�Y
		float radius_ = -1.0f;							//���a
		Vector2 center = { 0.0f,0.0f };					//���S
		float speed_ = -1;								//�X�s�[�h
	}para_;

	// �����t���O
	bool isAlive_ = false;

	// ���W
	Vector2 pos_ = { -1.0f,-1.0f };

	// �q�b�g�|�C���g
	int hp_ = -1;

	// ���G����
	bool isInvici_ = false;
	int inviciCounter_ = 0;
};

class UnitBase
{
public:
	UnitBase();
	virtual ~UnitBase();

	virtual void Load(void) = 0;
	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;

	const Base GetUnit(void)const { return unit_; }

protected:
	Base unit_;
};

