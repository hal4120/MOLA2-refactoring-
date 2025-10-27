#pragma once

#include<vector>
#include"Tentacle.h"

class TentacleShooter
{
public:
	TentacleShooter(const float& playerPos);
	~TentacleShooter();

	void Load(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void On(void);

	bool End(void);

private:
	int image_;
	std::vector<Tentacle*>tentacles_;

	int lastReference_;
	
	const float& playerPosX;
};