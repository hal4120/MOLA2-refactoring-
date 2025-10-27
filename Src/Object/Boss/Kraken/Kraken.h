#pragma once

#include"../BossBase.h"

#include"Attack/Sumi/SumiShooter.h"
#include"Attack/Sphere/SphereShooter.h"

class Kraken : public BossBase
{
public:
#pragma region �摜�֌W

	// �ǂݍ��މ摜�̃T�C�Y(�c�E���A�ꏏ)
	static constexpr int LOAD_SIZE = 96;

	// �摜�̊g�嗦(���摜�����������ߊg�債�Ďg�p����)
	static constexpr float SCALE = 4.0f;

	// �ŏI�I�ɕ`�悳���ۂ̃T�C�Y(�����蔻��ȂǂŎg�p����T�C�Y)
	static constexpr float SIZE_X = (LOAD_SIZE * SCALE) / 2.0f;
	static constexpr float SIZE_Y = (LOAD_SIZE * SCALE) / 1.5f;

	// ���[�V�����̗񋓌^��`
	enum class MOTION {
		IDLE,
		MOVE,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		ATTACK4,
		SPECIAL,
		DAMAGE,
		DEATH,

		MAX
	};

	// �e���[�V�����̃t�@�C���p�X(�ǂݍ��݂��ȗ������邽�߂̒�`)
	static constexpr const char* MOTION_PATH[(int)MOTION::MAX] =
	{
		"Data/Image/Boss/Kraken/Idle.png",
		"Data/Image/Boss/Kraken/Walk.png",
		"Data/Image/Boss/Kraken/Attack1.png",
		"Data/Image/Boss/Kraken/Attack2.png",
		"Data/Image/Boss/Kraken/Attack3.png",
		"Data/Image/Boss/Kraken/Attack4.png",
		"Data/Image/Boss/Kraken/Special.png",
		"Data/Image/Boss/Kraken/Hurt.png",
		"Data/Image/Boss/Kraken/Hurt.png"
	};

	// �e���[�V�����̉摜�̖���(�ǂݍ��݂��ȗ������邽�߂̒�`)
	static constexpr int MOTION_NUM[(int)MOTION::MAX] = { 6,6,6,6,6,6,6,2,2 };

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

	Kraken(const Vector2& playerPos);
	~Kraken();

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
	enum class STATE { IDLE, MOVE, ATTACK, DAMAGE, DEATH, MAX };

	// ��ԕʊ֐�------------------------------------------
	void Idle(void);
	void Move(void);
	void Attack(void);
	void Damage(void);
	void Death(void);
	//-----------------------------------------------------

	// HP�����֐�
	void HpDecrease(int damage);

	// �C�J���̂̓����̃x�N�g��
	Vector2 moveVec_;

	// ���S���o�̃J�E���^�[
	int deathCou_;


	int idleTime_;

#pragma region �ړ��֌W

	// �萔
	static constexpr int DESTINATION_POS_NUM = 9;
	const Vector2 DESTINATION_TABLE[DESTINATION_POS_NUM] =
	{
		{1600 / 6 * 1.0f,900 / 6 * 1.0f},
		{1600 / 6 * 3.0f,900 / 6 * 1.0f},
		{1600 / 6 * 5.0f,900 / 6 * 1.0f},
		{1600 / 6 * 1.0f,900 / 6 * 3.0f},
		{1600 / 6 * 3.0f,900 / 6 * 3.0f},
		{1600 / 6 * 5.0f,900 / 6 * 3.0f},
		{1600 / 6 * 1.0f,900 / 6 * 5.0f},
		{1600 / 6 * 3.0f,900 / 6 * 5.0f},
		{1600 / 6 * 5.0f,900 / 6 * 5.0f}
	};


	// �ړ��J�ڌ�1��ڂ���������ϐ�
	bool moveInit_;

	Vector2 destination_;

#pragma endregion

#pragma region �U���֌W

	// �U���J�ڌ�1��ڂ���������ϐ�
	bool attackInit_;
	// �U���I������������ϐ�
	bool attackEnd_;


	// �U���̎��
	enum class ATTACK_KINDS
	{
		NON = -1,
		SUMI,
		TENTACLE,
		SPHERE,
		TACKLE,

		MAX
	};

	// ���݂̍U��
	ATTACK_KINDS attackState_;
	// �U���̎�ނ̒��I���s���֐�
	ATTACK_KINDS AttackLottery(void) { return ATTACK_KINDS::SPHERE; }

	//�e�U���̃C���X�^���X----
	SumiShooter* sumi_;
	SphereShooter* sphere_;
	//------------------------

	// �U���̊e��v�֐����Ăяo���ꏊ---
	void AttackUpdate(void)override;
	void AttackDraw(void)override;
	void AttackRelease(void)override;
	//---------------------------------

#pragma endregion
};