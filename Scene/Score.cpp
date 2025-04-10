#include<DxLib.h>
#include "Score.h"
#include"../Manager/SceneManager.h"
#include"../Application.h"

Score::Score()
{
}

Score::~Score()
{
}

bool Score::SystemInit(void)
{
	haikeiimage = LoadGraph("image/Ranking.png");
	if (haikeiimage == -1)return false;

	for (int ii = 0; ii < RANKING_MAX; ii++) {
		normaltimescore[ii] = 0.0f;
		hardtimescore[ii] = 0.0f;
	}

	return true;
}

void Score::GameInit(void)
{
	pos.x = Application::SCREEN_SIZE_WID / 10;
	pos.y = Application::SCREEN_SIZE_HIG / 4;

	prevSpaceKey = nowSpaceKey = 0;
	prevPadKey = nowPadKey = 0;


	nextSceneID = E_SCENE_SCORE;
}

void Score::Update(void)
{
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	prevPadKey = nowPadKey;
	nowPadKey = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2;



	if ((prevSpaceKey == 1 && nowSpaceKey == 0) || (prevPadKey > 0 && nowPadKey == 0)) {
		nextSceneID = E_SCENE_MODESELECT;
	}
}

void Score::Draw(void)
{
	DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, RGB(255, 255, 255), true);
	DrawGraph(0, 39, haikeiimage, true);
	SetFontSize(64);
	for (int ii = 0; ii < RANKING_MAX; ii++) {
		DrawFormatString(pos.x, pos.y + (64 * ii), RGB(255, 0, 0), "%dst", ii + 1);
		DrawFormatString(pos.x + 100, pos.y + (64 * ii), RGB(255, 0, 0), "[%.2fs]", normaltimescore[ii]);
		DrawFormatString(pos.x + ((Application::SCREEN_SIZE_WID / 10) * 5), pos.y + (64 * ii), RGB(0, 0, 255), "%dst", ii + 1);
		DrawFormatString(pos.x + ((Application::SCREEN_SIZE_WID / 10) * 5) + 100, pos.y + (64 * ii), RGB(0, 0, 255), "[%.2fs]", hardtimescore[ii]);
	}
	SetFontSize(16);
}

bool Score::Release(void)
{
	if (DeleteGraph(haikeiimage) == -1)return false;
	return true;
}

void Score::RankingUpdate(MODE_ID id, float t)
{
	float time = t;
	float work;

	switch (id)
	{
	case MODE_NORMAL:
		for (int ii = 0; ii < RANKING_MAX; ii++) {
			if (normaltimescore[ii] == 0) {
				normaltimescore[ii] = time;
				break;
			}

			if (time < normaltimescore[ii]) {
				work = normaltimescore[ii];
				normaltimescore[ii] = time;

				for (int jj = RANKING_MAX - 1; jj > ii + 1; jj--) {
					normaltimescore[jj] = normaltimescore[jj - 1];
				}
				
				if (ii < RANKING_MAX - 1)normaltimescore[ii + 1] = work;

				break;
			}
		}

		break;

	case MODE_HARD:
		for (int ii = 0; ii < RANKING_MAX; ii++) {
			if (hardtimescore[ii] == 0) {
				hardtimescore[ii] = time;
				break;
			}

			if (time < hardtimescore[ii]) {
				work = hardtimescore[ii];
				hardtimescore[ii] = time;

				for (int jj = RANKING_MAX - 1; jj > ii + 1; jj--) {
					hardtimescore[jj] = hardtimescore[jj - 1];
				}

				if (ii < RANKING_MAX - 1)hardtimescore[ii + 1] = work;

				break;
			}
		}

		break;
	}

}
