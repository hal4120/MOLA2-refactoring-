#pragma once
#include "../UnitBase.h"

class Parry;

class Player :
    public UnitBase
{
public:
	// �ǂݍ��މ摜�̑傫��
	static constexpr int LOAD_SIZE_X = 42;
	static constexpr int LOAD_SIZE_Y = 66;

	// �ǂݍ��މ摜�̖���
	static constexpr int LOAD_NUM_X = 7;
	static constexpr int LOAD_NUM_Y = 1;

	// �A�j���[�V�����̐�
	static constexpr int ANIM_NUM = LOAD_NUM_X * LOAD_NUM_Y;

	// �A�j���[�V�����̃X�s�[�h(���t���[���ɂP��A�j���𓮂�����)
	static constexpr int ANIM_SPEED = 5;

	enum STATE { MOVE, ATTACK, SPECIAL, DEATH, MAX };

	// �������W
	const Vector2 START_POS = { 50.0f,50.0f };

    Player();
    ~Player();

	void Load(void)override;
	void Init(void)override;
	void Update(void)override;
	void Draw(void)override;
	void Release(void)override;

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
	void Attack(void);
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
};