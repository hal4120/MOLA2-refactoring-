#pragma once

class Vector2I
{
public:

	int x;
	int y;

	// �R���X�g���N�^
	Vector2I(void);

	// �R���X�g���N�^
	Vector2I(int vX, int vY);

	// �f�X�g���N�^
	~Vector2I(void);

	// ���---------------------------------------
	void operator=(const int value);
	//--------------------------------------------

	// ���Z---------------------------------------
	Vector2I operator+(const Vector2I value)const;
	void operator+=(const Vector2I value);

	Vector2I operator+(const int value)const;
	void operator+=(const int value);
	//--------------------------------------------
	
	// ���Z---------------------------------------
	Vector2I operator-(const Vector2I value)const;
	void operator-=(const Vector2I value);

	Vector2I operator-(const int value)const;
	void operator-=(const int value);
	//--------------------------------------------

	// ��Z---------------------------------------
	Vector2I operator*(const Vector2I value)const;
	void operator*=(const Vector2I value);

	Vector2I operator*(const int value)const;
	void operator*=(const int value);
	//--------------------------------------------

	// ���Z---------------------------------------
	Vector2I operator/(const Vector2I value)const;
	void operator/=(const Vector2I value);

	Vector2I operator/(const int value)const;
	void operator/=(const int value);
	//--------------------------------------------

	bool operator==(const int value) const;
	bool operator!=(const int value) const;
};

class Vector2
{
public:

	float x;
	float y;

	//�R���X�g���N�^
	Vector2(void);

	//�R���X�g���N�^
	Vector2(float vX, float vY);

	//�f�X�g���N�^
	~Vector2(void);

	//���Z

	// ���---------------------------------------
	void operator=(const float value);
	//--------------------------------------------

	// ���Z---------------------------------------
	Vector2 operator+(const Vector2 value)const;
	void operator+=(const Vector2 value);

	Vector2 operator+(const float value)const;
	void operator+=(const float value);
	//--------------------------------------------

	// ���Z---------------------------------------
	Vector2 operator-(const Vector2 value)const;
	void operator-=(const Vector2 value);

	Vector2 operator-(const float value)const;
	void operator-=(const float value);
	//--------------------------------------------

	// ��Z---------------------------------------
	Vector2 operator*(const Vector2 value)const;
	void operator*=(const Vector2 value);

	Vector2 operator*(const float value)const;
	void operator*=(const float value);
	//--------------------------------------------

	// ���Z---------------------------------------
	Vector2 operator/(const Vector2 value)const;
	void operator/=(const Vector2 value);

	Vector2 operator/(const float value)const;
	void operator/=(const float value);
	//--------------------------------------------


	bool operator==(const float value) const;
	bool operator!=(const float value) const;

	bool operator==(const Vector2 value) const;
	bool operator!=(const Vector2 value) const;

	bool operator<=(const float value)const;
	bool operator<=(const Vector2 value)const;
	bool operator<(const float value)const;
	bool operator<(const Vector2 value)const;
	bool operator>=(const float value)const;
	bool operator>=(const Vector2 value)const;
	bool operator>(const float value)const;
	bool operator>(const Vector2 value)const;

	Vector2 Abs(void)const;

	float length(void)const;

};