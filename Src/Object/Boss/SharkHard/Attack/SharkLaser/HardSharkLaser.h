#pragma once
#include"../../../../UnitBase.h"
class HardSharkLaser : public UnitBase
{
public:
	static constexpr int SIZE_X = 1500;
	static constexpr int SIZE_Y = 66;

	enum STATE { NON = -1, CHARGE, ACTIVE, END, MAX };

	const std::string FILE_PATH[STATE::MAX] =
	{
		"Data/Image/Boss/Shark/Attack/Laser/Charge/",
		"Data/Image/Boss/Shark/Attack/Laser/Active/",
		"Data/Image/Boss/Shark/Attack/Laser/End/"
	};

	static constexpr int IMG_NUM[STATE::MAX] = { 7,8,7 };

	// �A�j���[�V�����X�s�[�h(���t���[���ɂP��A�j���[�V������i�߂邩)
	static constexpr int ANIM_SPEED = 5;

	// �r�[�����ˎ���
	static constexpr int ACTIVE_TIME = 60; //�t���[��

	HardSharkLaser(const Vector2& bossPos);
	~HardSharkLaser();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	void OnCollision(UnitBase* other);

	const STATE GetState(void)const { return state_; }

	void On(void) { if (state_ != STATE::NON) { return; }state_ = STATE::CHARGE; counter_ = 0; countInterval_ = 0; }
	void Off(void) { state_ = STATE::NON; }

	const bool End(void)const { return state_ == STATE::NON; }

private:
	// �摜
	std::vector<int>img_[STATE::MAX];

	// �A�j���[�V�����J�E���^�[
	int counter_;
	int countInterval_;

	// ���
	STATE state_;

	const Vector2& boss_;
};