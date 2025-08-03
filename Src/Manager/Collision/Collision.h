#pragma once

#include"../../Object/UnitBase.h"

class Collision
{
public:
	Collision();
	~Collision();

	void Add(UnitBase* obj) { if (obj) objects_.emplace_back(obj); }
	void Clear(){ objects_.clear(); }
	void Check();


private:
	std::vector<UnitBase*> objects_;

	// �����蔻��̌`�̐U�蕪��
	bool IsHit(const Base& a, const Base& b);

	/// <summary>
	/// �~�`���m�̓����蔻��
	/// </summary>
	/// <param name="u1"></param>
	/// <param name="u2"></param>
	/// <returns></returns>
	const bool Circle(const Base& u1, const Base& u2)const;

	/// <summary>
	/// ��`���m�̓����蔻��
	/// </summary>
	/// <param name="u1"></param>
	/// <param name="u2"></param>
	/// <returns></returns>
	const bool Rect(const Base& u1, const Base& u2)const;

	/// <summary>
	/// �ȉ~���m�̓����蔻��
	/// </summary>
	/// <param name="u1"></param>
	/// <param name="u2"></param>
	/// <returns></returns>
	const bool Ellipse(const Base& u1, const Base& u2) const;

	/// <summary>
	/// �ȉ~�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="ellipse">�ȉ~</param>
	/// <param name="rect">��`</param>
	/// <param name="invici">���G�l��</param>
	/// <returns></returns>
	const bool EllipseAndRect(const Base& ellipse, const Base& rect) const;

	/// <summary>
	/// �~�`�Ƌ�`�̓����蔻��
	/// </summary>
	/// <param name="circle">�~�`</param>
	/// <param name="rect">��`</param>
	/// <returns></returns>
	const bool CircleAndRect(const Base& circle, const Base& rect)const;

	/// <summary>
	/// �~�`�Ƒȉ~�̓����蔻��
	/// </summary>
	/// <param name="circle">�~�`</param>
	/// <param name="ellipse">�ȉ~</param>
	/// <param name="invici">���G������l�����邩</param>
	/// <returns></returns>
	const bool CircleAndEllipse(const Base& circle, const Base& ellipse) const;

	//�~�`�̏����܂Ƃ߂�\����(�����Ŏg��)
	struct CircleInfo
	{
		Vector2 pos;
		float radius;
	};

	/// <summary>
	/// �~�`�Ɠ_�̓����蔻��
	/// </summary>
	/// <param name="circle"></param>
	/// <param name="pixel"></param>
	/// <returns></returns>
	const bool CircleAndPixel(const CircleInfo& circle, const Vector2& pixel)const;

	//��`�̏����܂Ƃ߂�\����(�����Ŏg��)
	struct RectInfo
	{
		Vector2 pos;
		Vector2 size;
	};

	/// <summary>
	/// ��`�Ɠ_�̓����蔻��
	/// </summary>
	/// <param name="rect">��`</param>
	/// <param name="pixel">�_</param>
	/// <returns></returns>
	const bool RectAndPixel(const RectInfo& rect, const Vector2& pixel)const;
};