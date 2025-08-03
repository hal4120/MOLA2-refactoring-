#include "EnemyManager.h"

#include"Monkfish/Monkfish.h"

EnemyManager::EnemyManager(BOSS_KINDS k):
	enemys_()
{
	switch (k)
	{
	case BOSS_KINDS::SHARK:
		for (int i = 0; i < ENEMY_MAX; i++) { enemys_[i] = new Monkfish((NUMBER)i); }
		break;
	}
}

EnemyManager::~EnemyManager()
{

}

void EnemyManager::Load(void)
{
	for (auto& enemy : enemys_) { enemy->Load(); }
}

void EnemyManager::Init(void)
{
	for (auto& enemy : enemys_) { enemy->Init(); }
}

void EnemyManager::Update(void)
{
	for (auto& enemy : enemys_) { enemy->Update(); }
}

void EnemyManager::Draw(void)
{
	for (auto& enemy : enemys_) { enemy->Draw(); }
}

void EnemyManager::Release(void)
{
	for (auto& enemy : enemys_) {
		enemy->Release();
		delete enemy;
		enemy = nullptr;
	}
}