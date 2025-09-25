#pragma once

#include "Bubble.h"
#include <vector>

class BubbleShooter
{
public:

	static constexpr int BUBBLE_NUM = 20;      // 1âÒÇÃîgÇÃíeêî


	BubbleShooter(const Vector2& bossPos, const Vector2& playerPos);
	~BubbleShooter();

	void Load(void);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	int img_;

	std::vector<Bubble*> bubbles_;

	const Vector2& bossPos_;
	const Vector2& playerPos_;

	bool shot_;

};