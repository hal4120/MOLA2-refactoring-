#pragma once

#include"../../scene/StageSelect/SelectScene.h"

#include<vector>

class Score
{
private:
	Score();
	~Score();
public:
	static void CreateInstance(void) { if (ins_ == nullptr) { ins_ = new Score(); ins_->Load(); } }
	static Score& GetIns(void) { CreateInstance(); return *ins_; }
	static void DeleteIns(void) { if (ins_ != nullptr) { ins_->Save(); delete ins_; } }

	struct ScoreInfo
	{
		float score_;
		bool newRecord_;
		int rank_;
	};
	static constexpr int RANKING_NUM = 5;

	void Load(void);

	void SetScore(const float score);
	ScoreInfo GetNowScore(void) { return nowScore_; }
	std::vector<float>GetRanking(BOSS_KINDS k);

	void Save(void);

private:
	static Score* ins_;

	float ranking_[(int)BOSS_KINDS::MAX][RANKING_NUM];

	ScoreInfo nowScore_;

	bool err_;
};

