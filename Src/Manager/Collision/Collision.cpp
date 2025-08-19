#include "Collision.h"

#include <cmath>
#include <algorithm>

#include"../../Object/Player/Parry/Parry.h"

Collision::Collision():
	objects_()
{

}

Collision::~Collision()
{
}



void Collision::Check()
{
	for (size_t i = 0; i < objects_.size(); ++i) {
		for (size_t j = i + 1; j < objects_.size(); ++j) {
			UnitBase* a = objects_[i];
			UnitBase* b = objects_[j];

			const Base& ua = a->GetUnit();
			const Base& ub = b->GetUnit();

			if (ua.para_.colliType == ub.para_.colliType)continue;

			if ((ua.aliveCollision_ && !ua.isAlive_) || (ub.aliveCollision_ && !ub.isAlive_)) continue;

			if (ua.isInvici_ && ua.inviciCounter_ > 0)continue;
			if (ub.isInvici_ && ub.inviciCounter_ > 0)continue;

			if (IsHit(ua, ub)) {
				a->OnCollision(b);
				b->OnCollision(a);
			}
		}
	}
}

bool Collision::IsHit(const Base& a, const Base& b)
{
	Base workA = a;
	workA.pos_ += workA.para_.center;
	Base workB = b;
	workB.pos_ += workB.para_.center;

	const auto shapeA = a.para_.colliShape;
	const auto shapeB = b.para_.colliShape;

	// �����Ȍ`��Ȃ瓖���蔻�肵�Ȃ�
	if (shapeA == CollisionShape::NON || shapeB == CollisionShape::NON) return false;

	// �����`�󓯎m
	if (shapeA == CollisionShape::CIRCLE && shapeB == CollisionShape::CIRCLE)
		return Circle(workA, workB);

	if (shapeA == CollisionShape::RECTANGLE && shapeB == CollisionShape::RECTANGLE)
		return Rect(workA, workB);

	if (shapeA == CollisionShape::ELLIPSE && shapeB == CollisionShape::ELLIPSE)
		return Ellipse(workA, workB);

	// �����p�^�[��
	if (shapeA == CollisionShape::CIRCLE && shapeB == CollisionShape::RECTANGLE)
		return CircleAndRect(workA, workB);

	if (shapeA == CollisionShape::RECTANGLE && shapeB == CollisionShape::CIRCLE)
		return CircleAndRect(workB, workA);

	if (shapeA == CollisionShape::CIRCLE && shapeB == CollisionShape::ELLIPSE)
		return CircleAndEllipse(workA, workB);

	if (shapeA == CollisionShape::ELLIPSE && shapeB == CollisionShape::CIRCLE)
		return CircleAndEllipse(workB, workA);

	if (shapeA == CollisionShape::ELLIPSE && shapeB == CollisionShape::RECTANGLE)
		return EllipseAndRect(workA, workB);

	if (shapeA == CollisionShape::RECTANGLE && shapeB == CollisionShape::ELLIPSE)
		return EllipseAndRect(workB, workA);

	// ���̑��̖��Ή��p�^�[���� false
	return false;
}




const bool Collision::Circle(const Base& u1, const Base& u2) const
{
	//2�_�Ԃ̃x�N�g�����쐬
	Vector2 vec = { u1.pos_.x - u2.pos_.x,u1.pos_.y - u2.pos_.y };

	//�쐬�����x�N�g���̑傫�����v�Z
	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y);

	//�Փ˔���
	if (distance < u1.para_.radius + u2.para_.radius)return true;


	return false;
}

const bool Collision::Rect(const Base& u1, const Base& u2) const
{
	//�Փ˔���ɕK�v�ȏ����܂Ƃ߂�
	struct rec
	{
		float up;
		float down;
		float left;
		float right;
	};

	rec r1, r2;
	r1 = { u1.pos_.y - u1.para_.size.y / 2,	u1.pos_.y + u1.para_.size.y / 2, u1.pos_.x - u1.para_.size.x / 2, u1.pos_.x + u1.para_.size.x / 2 };
	r2 = { u2.pos_.y - u2.para_.size.y / 2,	u2.pos_.y + u2.para_.size.y / 2, u2.pos_.x - u2.para_.size.x / 2, u2.pos_.x + u2.para_.size.x / 2 };


	//�Փ˔���
	if (r1.up	 < r2.down &&
		r1.down  > r2.up &&
		r1.left	 < r2.right &&
		r1.right > r2.left) {
		return true;
	}

	return false;
}

const bool Collision::Ellipse(const Base& u1, const Base& u2) const
{
	//2�_�Ԃ̃x�N�g�����쐬
	Vector2 vec = { u1.pos_.x - u2.pos_.x,u1.pos_.y - u2.pos_.y };

	//�e�����̔��a�̘a���v�Z
	Vector2 radius = { (u1.para_.size.x + u2.para_.size.x) / 2,	(u1.para_.size.y + u2.para_.size.y) / 2 };


	// ���K�����ꂽ�����ł̑ȉ~�Փ˔���i�ȉ~��Ԃł̋�����1�ȉ��Ȃ�Փˁj
	float norm = ((vec.x * vec.x) / (radius.x * radius.x)) + ((vec.y * vec.y) / (radius.y * radius.y));

	return norm <= 1.0f;
}



const bool Collision::EllipseAndRect(const Base& ellipse, const Base& rect) const
{
	// �ȉ~�̒��S�Ɣ��a�iX��Y�ňႤ�j
	Vector2 ellipseCenter = ellipse.pos_;
	Vector2 ellipseRadius = ellipse.para_.size / 2.0f;

	// ��`�̒��S�Ɣ��T�C�Y
	Vector2 rectCenter = rect.pos_;
	Vector2 rectHalfSize = rect.para_.size / 2.0f;

	// �ȉ~�̋�ԂɃ}�b�s���O���ċ�`��]���i����`��ȉ~�̒P�ʋ�ԂɃX�P�[�����O�j
	Vector2 scale = { 1.0f / ellipseRadius.x, 1.0f / ellipseRadius.y };

	// �ȉ~���P�ʉ~��Ԃɕϊ����ꂽ��`���S
	Vector2 scaledRectCenter = {
		(rectCenter.x - ellipseCenter.x) * scale.x,
		(rectCenter.y - ellipseCenter.y) * scale.y
	};

	// �ȉ~���P�ʉ~��Ԃɕϊ����ꂽ��`�T�C�Y
	Vector2 scaledRectHalfSize = {
		rectHalfSize.x * scale.x,
		rectHalfSize.y * scale.y
	};

	// �P�ʉ~��AABB�̓����蔻��i���S���_�j
	float dx = ((std::abs(scaledRectCenter.x) - scaledRectHalfSize.x) > 0.0f)
		? (std::abs(scaledRectCenter.x) - scaledRectHalfSize.x)
		: 0.0f;

	float dy = ((std::abs(scaledRectCenter.y) - scaledRectHalfSize.y) > 0.0f)
		? (std::abs(scaledRectCenter.y) - scaledRectHalfSize.y)
		: 0.0f;

	return dx * dx + dy * dy <= 1.0f;
}

const bool Collision::CircleAndRect(const Base& circle, const Base& rect) const
{
	RectInfo work;

	work = { rect.pos_,{rect.para_.size.x,rect.para_.size.y + (circle.para_.radius * 2)} };
	if (RectAndPixel(work, circle.pos_))return true;

	work = { rect.pos_,{rect.para_.size.x + (circle.para_.radius * 2),rect.para_.size.y} };
	if (RectAndPixel(work, circle.pos_))return true;

	Vector2 top = { 0.0f,0.0f };
	Vector2 vec = { rect.pos_.x - circle.pos_.x,	rect.pos_.y - circle.pos_.y };
	if (vec.x > 0 && vec.y > 0) top = { rect.pos_.x - (rect.para_.size.x / 2),	rect.pos_.y - (rect.para_.size.y / 2) };

	if (vec.x < 0 && vec.y > 0) top = { rect.pos_.x + (rect.para_.size.x / 2),	rect.pos_.y - (rect.para_.size.y / 2) };

	if (vec.x > 0 && vec.y < 0) top = { rect.pos_.x - (rect.para_.size.x / 2),	rect.pos_.y + (rect.para_.size.y / 2) };

	if (vec.x < 0 && vec.y < 0) top = { rect.pos_.x + (rect.para_.size.x / 2),	rect.pos_.y + (rect.para_.size.y / 2) };

	CircleInfo topcircle = { top,circle.para_.radius };

	if (CircleAndPixel(topcircle, circle.pos_))return true;

	return false;
}

const bool Collision::CircleAndEllipse(const Base& circle, const Base& ellipse) const
{
	// �ȉ~�̒��S�Ɣ��a
	Vector2 ellipseCenter = ellipse.pos_;
	Vector2 ellipseRadius = ellipse.para_.size / 2.0f;

	// �~�̒��S�Ɣ��a
	Vector2 circleCenter = circle.pos_;
	float circleRadius = circle.para_.radius;

	// �~�̔��a�������ȉ~��c��܂���
	float a = ellipseRadius.x + circleRadius;
	float b = ellipseRadius.y + circleRadius;

	// ���S����̋���
	float dx = circleCenter.x - ellipseCenter.x;
	float dy = circleCenter.y - ellipseCenter.y;

	// �ȉ~�̎��Ŕ���
	float eq = (dx * dx) / (a * a) + (dy * dy) / (b * b);

	return eq <= 1.0f;
}

const bool Collision::CircleAndPixel(const CircleInfo& circle, const Vector2& pixel) const
{
	Vector2 vec = { circle.pos.x - pixel.x,	circle.pos.y - pixel.y };

	float distance = sqrtf(vec.x * vec.x + vec.y * vec.y);

	if (distance < circle.radius)return true;

	return false;
}

const bool Collision::RectAndPixel(const RectInfo& rect, const Vector2& pixel) const
{
	if (rect.pos.x - rect.size.x / 2 < pixel.x &&
		rect.pos.y - rect.size.y / 2 < pixel.y &&
		rect.pos.x + rect.size.x / 2 > pixel.x &&
		rect.pos.y + rect.size.y / 2 > pixel.y) {
		return true;
	}
	return false;
}