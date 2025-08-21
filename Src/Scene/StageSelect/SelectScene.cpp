#include "SelectScene.h"

#include<DxLib.h>

#include"../../Utility/Utility.h"
#include"../../Application/Application.h"

#include"../../Manager/Sound/SoundManager.h"

#include"../../Manager/Score/Score.h"

#include"../SceneManager/SceneManager.h"


#include"../../Object/Stage/Purple/PurpleStage.h"
#include"Object/SelectPlayer.h"

BOSS_KINDS SelectScene::nowBoss_ = BOSS_KINDS::NON;

SelectScene::SelectScene():
	player_(nullptr),
	stage_(nullptr),
	upKey_(),
	downKey_(),
	titleBackKey_(),
	numberKey_(),
	rankingFrameImg_(-1),
	selectObjImgs_(),
	selectAnimeCounter_(0),
	selectAnimeInterval_(0),
	selectObjPos_(),
	selectObjAngle_(0.0f),
	selectObjParry_(false),
	arrowImg_(-1),
	selectImg_(-1)
{
}

SelectScene::~SelectScene()
{
}

void SelectScene::Load(void)
{
	stage_ = new PurpleStage();
	stage_->Load();

	player_ = new SelectPlayer();
	player_->Load();

	Utility::LoadImg(selectImg_, "Data/Image/Select/Select.png");

	Utility::LoadImg(rankingFrameImg_, "Data/Image/Select/Ranking.png");

	Utility::LoadArrayImg("Data/Image/Select/NormalShark.png", 6, 6, 1, 480, 480, selectObjImgs_[(int)BOSS_KINDS::SHARK]);
	Utility::LoadArrayImg("Data/Image/Select/HardShark.png", 6, 6, 1, 480, 480, selectObjImgs_[(int)BOSS_KINDS::SHARK_HARD]);

	Utility::LoadImg(arrowImg_, "Data/Image/Effect/Arrow.png");

	Smng::GetIns().Load(SOUND::BGM_RARARA);
	Smng::GetIns().Load(SOUND::PARRY);
}

void SelectScene::Init(void)
{
	nowBoss_ = BOSS_KINDS::SHARK;

	stage_->Init();
	player_->Init();

	selectAnimeCounter_ = 0;
	selectAnimeInterval_ = 0;

	selectObjAngle_ = 0.0f;

	selectObjPos_ = SELECT_OBJ_POS_DEFAULT;

	selectObjParry_ = false;

	Smng::GetIns().Play(SOUND::BGM_RARARA, true, 150, true);
}

void SelectScene::Update(void)
{
	Input();

	if (titleBackKey_.down) {
		SceneManager::GetInstance().ChangeScene(SCENE_ID::TITLE);
		return;
	}

	stage_->Update();
	player_->Update();

	if (selectObjParry_) {

		selectObjPos_.x += 15;
		selectObjAngle_ += Utility::Deg2RadF(5.0f);

		if (selectObjPos_.x > Application::SCREEN_SIZE_X) { 
			SceneManager::GetInstance().ChangeScene(SCENE_ID::GAME);
			return;
		}

	} else {

		if (upKey_.down) {

			Smng::GetIns().Play(SOUND::SELECT, true);

			nowBoss_ = (BOSS_KINDS)( ((int)nowBoss_) - 1 );
			if (((int)nowBoss_) <= (int)BOSS_KINDS::NON) { nowBoss_ = (BOSS_KINDS)(((int)BOSS_KINDS::MAX) - 1); }

		}

		if (downKey_.down) {

			Smng::GetIns().Play(SOUND::SELECT, true);

			nowBoss_ = (BOSS_KINDS)(((int)nowBoss_) + 1);
			if (((int)nowBoss_) >= (int)BOSS_KINDS::MAX) { nowBoss_ = (BOSS_KINDS)(((int)BOSS_KINDS::NON) + 1); }

		}

		if (player_->Parry()) { selectObjParry_ = true; Smng::GetIns().Play(SOUND::PARRY, true); }

		RankingReset();
	}

	if (++selectAnimeInterval_ >= 10) {
		selectAnimeInterval_ = 0;
		if (++selectAnimeCounter_ >= selectObjImgs_[(int)nowBoss_].size()) {
			selectAnimeCounter_ = 0;
		}
	}

}

void SelectScene::Draw(void)
{
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	// îwåi
	stage_->Draw();

	// Ç‹Ç⁄
	player_->Draw();
	
	// ÉâÉìÉLÉìÉOÉtÉåÅ[ÉÄï\é¶
	DrawExtendGraph(x, 0, xx, yy, rankingFrameImg_, true);

	// ÉâÉìÉLÉìÉOï\é¶Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`
	auto ranking = Score::GetIns().GetRanking(nowBoss_);
	SetFontSize(55);
	for (int i = 0; i < ranking.size(); i++) {
		DrawFormatString(RANKING_POS.x, RANKING_POS.y + (i * RANKING_POS_Y_SPACE), 0x0000ff, (ranking[i] == -1.0f) ? "----" : "%.2fs", ranking[i]);
	}
	SetFontSize(16);
	//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

	// ëIëíÜÇÃÉ{ÉXÇÃÉvÉåÉrÉÖÅ[Çï\é¶
	DrawRotaGraph(selectObjPos_.x, selectObjPos_.y, 1, selectObjAngle_, selectObjImgs_[(int)nowBoss_][selectAnimeCounter_], true);

	// ñÓàÛÇï\é¶Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`
	for (int i = 0; i < 2; i++) {
		DrawRotaGraph(
			SELECT_OBJ_POS_DEFAULT.x,
			SELECT_OBJ_POS_DEFAULT.y + ((SELECT_OBJ_SIZE_Y / 4) * (i * 2 - 1)),
			3, Utility::Deg2RadF(90.0f) * (i * 2 - 1),
			arrowImg_, true);
	}
	// Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

	// ÅuSELECTÅvï\é¶
	DrawRotaGraph(x / 2, 150, 1, 0, selectImg_, true);
}

void SelectScene::Release(void)
{
	Smng::GetIns().Delete(SOUND::BGM_RARARA);
	Smng::GetIns().Delete(SOUND::PARRY);

	DeleteGraph(selectImg_);

	DeleteGraph(rankingFrameImg_);

	for (auto& imgs : selectObjImgs_) {
		for (auto& img : imgs) { DeleteGraph(img); }
		imgs.clear();
	}

	DeleteGraph(arrowImg_);

	if (stage_) {
		stage_->Release();
		delete stage_;
		stage_ = nullptr;
	}
	if (player_) {
		player_->Release();
		delete player_;
		player_ = nullptr;
	}
}


void SelectScene::Input(void)
{
	int input = GetJoypadInputState(DX_INPUT_PAD1);
	XINPUT_STATE state = {};
	if (GetJoypadXInputState(DX_INPUT_PAD1, &state) != 0) { state = {}; }

	upKey_.prev = upKey_.now;
	upKey_.now = (
		(CheckHitKey(KEY_INPUT_UP) == 0) &&
		(CheckHitKey(KEY_INPUT_W) == 0) &&
		((input & PAD_INPUT_UP) == 0)
		) ? false : true;
	upKey_.down = (!upKey_.prev && upKey_.now);
	upKey_.up = (upKey_.prev && !upKey_.now);


	downKey_.prev = downKey_.now;
	downKey_.now = (
		(CheckHitKey(KEY_INPUT_DOWN) == 0) &&
		(CheckHitKey(KEY_INPUT_S) == 0) &&
		((input & PAD_INPUT_DOWN) == 0)
		) ? false : true;
	downKey_.down = (!downKey_.prev && downKey_.now);
	downKey_.up = (downKey_.prev && !downKey_.now);


	titleBackKey_.prev = titleBackKey_.now;
	titleBackKey_.now = (
		(CheckHitKey(KEY_INPUT_ESCAPE) == 0) &&
		(state.Buttons[XINPUT_BUTTON_START] == 0)
		) ? false : true;
	titleBackKey_.down = (!titleBackKey_.prev && titleBackKey_.now);
	titleBackKey_.up = (titleBackKey_.prev && !titleBackKey_.now);


	for (int i = 0; i < NUMBER_NAME::MAX; i++) {
		numberKey_[i].prev = numberKey_[i].now;
		numberKey_[i].now = (CheckHitKey(NUMBERS_KEY[i]) == 0) ? false : true;
		numberKey_[i].down = (!numberKey_[i].prev && numberKey_[i].now);
		numberKey_[i].up = (numberKey_[i].prev && !numberKey_[i].now);
	}
}

void SelectScene::RankingReset(void)
{
	if (CheckHitKey(KEY_INPUT_0) == 0) { return; }

	if (CheckHitKey(KEY_INPUT_6) && CheckHitKey(KEY_INPUT_8)) { Score::GetIns().RankingReset(nowBoss_); }

	size_t input_num = 0;
	NUMBER_NAME num = {};
	for (int i = 0; i < NUMBER_NAME::MAX; i++) {
		if (numberKey_[i].down) { num = (NUMBER_NAME)i;	 input_num++; }
	}
	if (input_num == 1) {
		Score::GetIns().RankingReset(nowBoss_, num + 1);
	}
}
