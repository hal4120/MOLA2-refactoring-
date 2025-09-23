#pragma once
#include "../UnitBase.h"

#include"../../Application/Application.h"

#include"Parry/Parry.h"
#include"Special/PlayerLaser.h"

enum class DIR { RIGHT, LEFT };

class Player : public UnitBase
{
public:
	// �ǂݍ��މ摜�̖���
	static constexpr int ANIM_NUM_X = 7;
	static constexpr int ANIM_NUM_Y = 1;
	static constexpr int ANIM_NUM = ANIM_NUM_X * ANIM_NUM_Y;

	// �ǂݍ��މ摜�̑傫��
	static constexpr int LOAD_SIZE_X = 42;
	static constexpr int LOAD_SIZE_Y = 66;

	// �A�j���[�V�����̃X�s�[�h(���t���[���ɂP��A�j���𓮂�����)
	static constexpr int ANIM_SPEED = 5;

	// ���
	enum STATE { DEFAULT, SPECIAL, DEATH, OVER, MAX };

	// �������W
	const Vector2 START_POS = { 50.0f,Application::SCREEN_SIZE_Y / 2 };

	// �ړ����x
	static constexpr float SPEED = 8.0f;

	// ���C�t
	static constexpr int LIFE_MAX = 5;

	// �X�y�V�����U���̃`���[�W�K�v��
	static constexpr int SPECIAL_CHARGE_MAX = 20;

    Player();
    ~Player();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void UIDraw(void);
	void Release(void)override;

	void OnCollision(UnitBase* other);

	Parry* ParryIns(void) { return parry_; }
	PlayerLaser* LaserIns(void) { return laser_; }

	void SpecialCharge(void) { if (++specialCharge_ > SPECIAL_CHARGE_MAX) { specialCharge_ = SPECIAL_CHARGE_MAX; } }

	const bool CollisionValid(void)const { return state_ != STATE::DEATH; }

	const bool GameOver(void)const { return gameEnd_; }
private:
	// �摜�n���h��
	int img_[ANIM_NUM];

	// �A�j���[�V�����J�E���^�[
	int animCounter_;
	int animInterval_;

	// ��]��
	float angle_;

	// ����
	DIR dir_;

	// �A�j���[�V��������
	void Animation(void);

	// �X�e�[�g
	STATE state_;

	// �X�e�[�g�ʂ̊֐��̃|�C���^�Ŋi�[����ϐ�
	void (Player::* stateFuncPtr_[STATE::MAX])(void);

	// �X�e�[�g�ʂ̊֐�
	void Default(void);
	void Special(void);
	void Death(void);
	void Over(void);

	// �m�b�N�o�b�N�֌W
	Vector2 knockBackVec_;

	Parry* parry_;
	PlayerLaser* laser_;

	int specialCharge_;
	int specialChargeImg_[SPECIAL_CHARGE_MAX + 1];
	int specialChargeMaxImg_;
	int specialChargeMaxFlash_;
	int specialChargeMaxButtonImg_[2];
	int specialChargeMaxKeyImg_[2];

	bool gameEnd_;

	int uiImg_;
	int	lifeImg_[LIFE_MAX + 1];
};