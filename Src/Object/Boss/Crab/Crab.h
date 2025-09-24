#pragma once
#include "../BossBase.h"

class Crab : public BossBase
{
public:
#pragma region �摜�֌W

	// �ǂݍ��މ摜�̃T�C�Y(�c�E���A�ꏏ)
	static constexpr int LOAD_SIZE = 96;

	// �摜�̊g�嗦(���摜�����������ߊg�債�Ďg�p����)
	static constexpr float SCALE = 4.0f;

	// �ŏI�I�ɕ`�悳���ۂ̃T�C�Y(�����蔻��ȂǂŎg�p����T�C�Y)
	static constexpr float SIZE_X = LOAD_SIZE * SCALE;
	static constexpr float SIZE_Y = (LOAD_SIZE * SCALE) / 2.0f;

	// ���[�V�����̗񋓌^��`
	enum class MOTION {
		MOVE,
		IDLE,
		ATTACK1, 
		ATTACK2,
		ATTACK3,
		ATTACK4,
		SPECIAL,
		DAMAGE, 
		DEATH,
		MAX };

	// �e���[�V�����̃t�@�C���p�X(�ǂݍ��݂��ȗ������邽�߂̒�`)
	static constexpr const char* MOTION_PATH[(int)MOTION::MAX] =
	{
		"Data/Image/Boss/Crab/Walk.png",
		"Data/Image/Boss/Crab/Idle.png",
		"Data/Image/Boss/Crab/Attack1.png",
		"Data/Image/Boss/Crab/Attack2.png",
		"Data/Image/Boss/Crab/Attack3.png",
		"Data/Image/Boss/Crab/Attack4.png",
		"Data/Image/Boss/Crab/Special.png",
		"Data/Image/Boss/Crab/Hurt.png",
		"Data/Image/Boss/Crab/Hurt.png"
	};

	// �e���[�V�����̉摜�̖���(�ǂݍ��݂��ȗ������邽�߂̒�`)
	static constexpr int MOTION_NUM[(int)MOTION::MAX] = { 6,4,6,6,6,6,6,2,2 };

#pragma endregion

#pragma region �p�����[�^�[�֌W

	// �ő�q�b�g�|�C���g
	static constexpr int HP_MAX = 100;

	// �ړ����x
	static constexpr float MOVE_SPEED = 5.0f;

	// �U���̃N�[���^�C��
	static constexpr int ATTACK_INTERVAL = 300;

	// ���S���o�̒���
	static constexpr int DEATH_PERFOR_TIME = 180;

#pragma endregion

	Crab(const Vector2& playerPos);
	~Crab();

	void Load(void)override;
	void Init(void)override;

	// �Փˎ�����
	void OnCollision(UnitBase* other)override;

	// �U���̃C���X�^���X���ʂɕ����Ĕz��Ɋi�[�������̂�Ԃ��֐�
	std::vector<UnitBase*>AttackIns(void)override;

	// �^�C����i�߂邩�ǂ���
	bool Timer(void)override;

private:

	// ��Ԃ̗񋓌^��`
	enum class STATE { MOVE, ATTACK, DAMAGE, DEATH, MAX };

	// ��ԕʊ֐�------------------------------------------
	void Move(void);
	void Attack(void);
	void Damage(void);
	void Death(void);
	//-----------------------------------------------------

	// HP�����֐�
	void HpDecrease(int damage);

	// �{�X���̂̓����̃x�N�g��
	Vector2 moveVec_;

	// ���S���o�̃J�E���^�[
	int deathCou_;

#pragma region �U���֌W

	// �U���̊Ԋu���Ǘ�����J�E���^�[
	int attackInterval_;

	// �U���J�ڌ�1��ڂ���������ϐ�
	bool attackInit_;
	// �U���I������������ϐ�
	bool attackEnd_;

	// �U���̎��
	enum class ATTACK_KINDS
	{
		NON = -1,

		MAX
	};

	// ���݂̍U��
	ATTACK_KINDS attackState_;
	// �U���̎�ނ̒��I���s���֐�
	ATTACK_KINDS AttackLottery(void) { return ATTACK_KINDS::NON; }

	//�e�U���̃C���X�^���X----
	
	//------------------------

	// �U���̊e��v�֐����Ăяo���ꏊ---
	void AttackUpdate(void)override;
	void AttackDraw(void)override;
	void AttackRelease(void)override;
	//---------------------------------

	static constexpr int SP_ATTACK_MEASU = 1800;
	int spAttackMeasu_;
	// �ːi����
	bool TacklePreparation(void);
	// �ːi�I��
	bool TackleEnd(void);

#pragma endregion
};