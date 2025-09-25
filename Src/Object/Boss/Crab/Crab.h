#pragma once
#include "../BossBase.h"

class Crab : public BossBase
{
public:
#pragma region 画像関係

	// 読み込む画像のサイズ(縦・横、一緒)
	static constexpr int LOAD_SIZE = 96;

	// 画像の拡大率(元画像が小さいため拡大して使用する)
	static constexpr float SCALE = 4.0f;

	// 最終的に描画される際のサイズ(当たり判定などで使用するサイズ)
	static constexpr float SIZE_X = LOAD_SIZE * SCALE;
	static constexpr float SIZE_Y = (LOAD_SIZE * SCALE) / 2.0f;

	// モーションの列挙型定義
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

	// 各モーションのファイルパス(読み込みを簡略化するための定義)
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

	// 各モーションの画像の枚数(読み込みを簡略化するための定義)
	static constexpr int MOTION_NUM[(int)MOTION::MAX] = { 6,4,6,6,6,6,6,2,2 };

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

	Crab(const Vector2& playerPos);
	~Crab();

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
	enum class STATE { MOVE, ATTACK, DAMAGE, DEATH, MAX };

	// 状態別関数------------------------------------------
	void Move(void);
	void Attack(void);
	void Damage(void);
	void Death(void);
	//-----------------------------------------------------

	// HP減少関数
	void HpDecrease(int damage);

	// ボス自体の動きのベクトル
	Vector2 moveVec_;

	// 死亡演出のカウンター
	int deathCou_;

#pragma region 攻撃関係

	// 攻撃の間隔を管理するカウンター
	int attackInterval_;

	// 攻撃遷移後1回目を見分ける変数
	bool attackInit_;
	// 攻撃終了を見分ける変数
	bool attackEnd_;

	// 攻撃の種類
	enum class ATTACK_KINDS
	{
		NON = -1,

		MAX
	};

	// 現在の攻撃
	ATTACK_KINDS attackState_;
	// 攻撃の種類の抽選を行う関数
	ATTACK_KINDS AttackLottery(void) { return ATTACK_KINDS::NON; }

	//各攻撃のインスタンス----
	
	//------------------------

	// 攻撃の各主要関数を呼び出す場所---
	void AttackUpdate(void)override;
	void AttackDraw(void)override;
	void AttackRelease(void)override;
	//---------------------------------

	static constexpr int SP_ATTACK_MEASU = 1800;
	int spAttackMeasu_;
	// 突進準備
	bool TacklePreparation(void);
	// 突進終了
	bool TackleEnd(void);

#pragma endregion
};