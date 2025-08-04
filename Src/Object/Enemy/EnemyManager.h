#pragma once

#include<vector>

#include"EnemyBase.h"

#include"../../Scene/StageSelect/SelectScene.h"

class EnemyManager
{
public:
	static constexpr int ENEMY_MAX = 5;

	EnemyManager(BOSS_KINDS k);
	~EnemyManager();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	std::vector<UnitBase*>GetEnemys(void) {
		std::vector<UnitBase*>ret;
		for (auto& enemy : enemys_) { ret.emplace_back(enemy); }
		return ret;
	}

private:
	EnemyBase* enemys_[ENEMY_MAX];

};

