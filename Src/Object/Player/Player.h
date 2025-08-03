#pragma once
#include "../UnitBase.h"

#include"Parry/Parry.h"
#include"Special/PlayerLaser.h"

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

	enum STATE { DEFAULT, SPECIAL, DEATH, MAX };

	// �������W
	const Vector2 START_POS = { 50.0f,50.0f };

    Player();
    ~Player();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

	Parry& ParryIns(void) { return *parry_; }
	PlayerLaser& LaserIns(void) { return *laser_; }

private:
	// �摜�n���h��
	int img_[ANIM_NUM];

	// �A�j���[�V�����J�E���^�[
	int animCounter_;
	int animInterval_;

	// �A�j���[�V��������
	void Animation(void);

	// �X�e�[�g
	STATE state_;

	// �X�e�[�g�ʂ̊֐��̃|�C���^�Ŋi�[����ϐ�
	void (Player::* stateFuncPtr_[STATE::MAX])(void);

	// �X�e�[�g�ʂ̊֐�
	void Move(void);
	void Special(void);
	void Death(void);


	// ���͏��Ǘ�
	struct InputInfo
	{
		bool prev_ = false;
		bool now_ = false;
		bool upTrg_ = false;
		bool downTrg_ = false;
	};
	InputInfo up_, down_, left_, right_;
	InputInfo attackKey_;
	InputInfo specialKey_;

	void Input(void);

	Parry* parry_;
	PlayerLaser* laser_;

};