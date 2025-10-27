#pragma once

#include"../BossBase.h"

#include"Attack/Sumi/SumiShooter.h"
#include"Attack/Sphere/SphereShooter.h"

class Kraken : public BossBase
{
public:
#pragma region 画像関係

	// 読み込む画像のサイズ(縦・横、一緒)
	static constexpr int LOAD_SIZE = 96;

	// 画像の拡大率(元画像が小さいため拡大して使用する)
	static constexpr float SCALE = 4.0f;

	// 最終的に描画される際のサイズ(当たり判定などで使用するサイズ)
	static constexpr float SIZE_X = (LOAD_SIZE * SCALE) / 2.0f;
	static constexpr float SIZE_Y = (LOAD_SIZE * SCALE) / 1.5f;

	// モーションの列挙型定義
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

	// 各モーションのファイルパス(読み込みを簡略化するための定義)
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

	// 各モーションの画像の枚数(読み込みを簡略化するための定義)
	static constexpr int MOTION_NUM[(int)MOTION::MAX] = { 6,6,6,6,6,6,6,2,2 };

#pragma endregion

#pragma region パラメーター関係

	// 最大ヒットポイント
	static constexpr int HP_MAX = 100;

	// 移動速度
	static constexpr float MOVE_SPEED = 5.0f;

	// 攻撃のクールタイム
	static constexpr int ATTACK_INTERVAL = 300;

	// 死亡演出の長さ
	static constexpr int DEATH_PERFOR_TIME = 180;

#pragma endregion

	Kraken(const Vector2& playerPos);
	~Kraken();

	void Load(void)override;
	void Init(void)override;

	// 衝突時処理
	void OnCollision(UnitBase* other)override;

	// 攻撃のインスタンスを個別に分けて配列に格納したものを返す関数
	std::vector<UnitBase*>AttackIns(void)override;

	// タイムを進めるかどうか
	bool Timer(void)override;
private:

	// 状態の列挙型定義
	enum class STATE { IDLE, MOVE, ATTACK, DAMAGE, DEATH, MAX };

	// 状態別関数------------------------------------------
	void Idle(void);
	void Move(void);
	void Attack(void);
	void Damage(void);
	void Death(void);
	//-----------------------------------------------------

	// HP減少関数
	void HpDecrease(int damage);

	// イカ自体の動きのベクトル
	Vector2 moveVec_;

	// 死亡演出のカウンター
	int deathCou_;


	int idleTime_;

#pragma region 移動関係

	// 定数
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


	// 移動遷移後1回目を見分ける変数
	bool moveInit_;

	Vector2 destination_;

#pragma endregion

#pragma region 攻撃関係

	// 攻撃遷移後1回目を見分ける変数
	bool attackInit_;
	// 攻撃終了を見分ける変数
	bool attackEnd_;


	// 攻撃の種類
	enum class ATTACK_KINDS
	{
		NON = -1,
		SUMI,
		TENTACLE,
		SPHERE,
		TACKLE,

		MAX
	};

	// 現在の攻撃
	ATTACK_KINDS attackState_;
	// 攻撃の種類の抽選を行う関数
	ATTACK_KINDS AttackLottery(void) { return ATTACK_KINDS::SPHERE; }

	//各攻撃のインスタンス----
	SumiShooter* sumi_;
	SphereShooter* sphere_;
	//------------------------

	// 攻撃の各主要関数を呼び出す場所---
	void AttackUpdate(void)override;
	void AttackDraw(void)override;
	void AttackRelease(void)override;
	//---------------------------------

#pragma endregion
};