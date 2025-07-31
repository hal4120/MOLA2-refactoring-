#include"Score.h"

#include<sstream>
#include<fstream>
#include<iostream>
#include<vector>
#include<string>

#include"../../Utility/Utility.h"

Score* Score::ins_ = nullptr;

Score::Score():
	err_(false)
{
}

Score::~Score()
{
}

void Score::Load(void)
{
	std::ifstream ifs = std::ifstream("Data/ranking/ranking.csv");
	if (!ifs) {
		// 読み込みに失敗したので、ロード失敗を記録してすべてスコアなしで初期化して終了
		err_ = true;
		for (auto& kinds : ranking_) { for (auto& rank : kinds) { rank = -1; } }
		return;
	}

	std::string line;
	std::vector<std::string> strrSplit;
	float num = 0;
	int kinds = 0;

	while (getline(ifs, line))
	{
		strrSplit = Utility::Split(line, ',');
		for (int i = 0; i < RANKING_NUM; i++) {
			num = stof(strrSplit[i]);

			ranking_[kinds][i] = num;
		}
		kinds++;
	}
}

void Score::SetScore(const float score)
{
	nowScore_.score_ = score;
	nowScore_.rank_ = -1;
	nowScore_.newRecord_ = false;

	int i = -1;
	for (auto& r : ranking_[(int)SelectScene::GetNowBoss()]) {
		i++;

		if (r == -1) {
			r = nowScore_.score_;
			nowScore_.rank_ = i;
			nowScore_.newRecord_ = true;
			break;
		}

		if (nowScore_.score_ < r ) {
			float work = r;
			r = nowScore_.score_;

			for (int j = RANKING_NUM - 1; j > i; j--) {
				ranking_[(int)SelectScene::GetNowBoss()][j] = ranking_[(int)SelectScene::GetNowBoss()][j - 1];
			}
			if (i < RANKING_NUM - 1) { ranking_[(int)SelectScene::GetNowBoss()][i + 1] = work; }

			nowScore_.rank_ = i;
			nowScore_.newRecord_ = true;
			break;
		}
	}
}

std::vector<float> Score::GetRanking(BOSS_KINDS k)
{
	std::vector<float>ret = {};

	for (auto& s : ranking_[(int)k]) {
		ret.emplace_back(s);
	}

	return ret;
}

void Score::Save(void)
{
	// ロードに失敗していたらすでにあるデータを破壊してしまうのでセーブを行わない
	if (err_) { return; }

	std::ofstream ofs("Data/ranking/ranking.csv");
	if (!ofs) {
		printfDx("ランキングの保存に失敗しました\n");
		return;
	}

	for (int kind = 0; kind < (int)BOSS_KINDS::MAX; kind++) {
		for (int i = 0; i < RANKING_NUM; i++) {
			ofs << ranking_[kind][i];
			if (i != RANKING_NUM - 1) { ofs << ","; } //カンマで区切る
		}
		ofs << '\n'; //改行
	}

}