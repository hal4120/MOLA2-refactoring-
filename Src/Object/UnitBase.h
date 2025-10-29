#pragma once

#include"../Common/Vector2.h"
#include"../Utility/Utility.h"

enum class CollisionShape { NON = -1, CIRCLE, RECTANGLE, ELLIPSE, MAX };
enum class CollisionType { NON = -2, ALLY/*����*/, ENEMY/*�G*/ };	//�������������瓖���蔻�肵�Ȃ�

struct Base
{
	//�p�����[�^�[
	struct {
		CollisionShape colliShape = CollisionShape::NON;	//�����蔻��̌`
		CollisionType colliType = CollisionType::NON;

		Vector2 size = { -1.0f,-1.0f };						//�T�C�Y
		float radius = -1.0f;								//���a
		Vector2 center = { 0.0f,0.0f };						//���S
		float speed = -1;									//�X�s�[�h
	}para_;

	// �����t���O
	bool isAlive_ = false;

	// �����t���O�ɂ�铖���蔻��̑������^�[�����s�����ǂ���
	bool aliveCollision_ = true;

	// ���W
	Vector2 pos_ = { -1.0f,-1.0f };


	// �q�b�g�|�C���g
	int hp_ = -1;


	// ���G����
	bool isInvici_ = true;
	int inviciCounter_ = 0;
};

class UnitBase
{
public:
	UnitBase();
	virtual ~UnitBase() = 0;

	virtual void Load(void) = 0;
	virtual void Init(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void Release(void) = 0;

	const Base& GetUnit(void)const { return unit_; }

	virtual void OnCollision(UnitBase* other) = 0;

protected:
	Base unit_;
	void Invi(void);

	// �����蔻��̕`��̃����_�֐�
	void DrawDebug(void);
};

