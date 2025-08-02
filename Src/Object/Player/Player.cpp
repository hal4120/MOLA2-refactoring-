#include "Player.h"

#include<DxLib.h>

#include"../../Application/Application.h"
#include"../../Manager/Input/InputManager.h"

#include"Parry/Parry.h"


Player::Player():
	img_(),
	animCounter_(0),
	animInterval_(0),
	state_(STATE::MOVE),
	parry_(nullptr)
{
}

Player::~Player()
{
}

void Player::Load(void)
{
	// プレイヤー画像の読み込み
	int err = 0;
	err = LoadDivGraph("Data/Image/Player/まぼ.png",
		ANIM_NUM, LOAD_NUM_X, LOAD_NUM_Y,
		LOAD_SIZE_X, LOAD_SIZE_Y, img_);
	if (err == -1) { printfDx("プレイヤーの画像の読み込みに失敗しました"); }

	// 関数ポインタにそれぞれの関数のポインタを格納
	stateFuncPtr_[STATE::MOVE] = &Player::Move;
	stateFuncPtr_[STATE::ATTACK] = &Player::Attack;
	stateFuncPtr_[STATE::SPECIAL] = &Player::Special;
	stateFuncPtr_[STATE::DEATH] = &Player::Death;

	unit_.para_.speed_ = 5.0f;

	unit_.para_.size = { LOAD_SIZE_X,LOAD_SIZE_Y };

	parry_ = new Parry();
	parry_->Load();
	parry_->takePlayerPosPtr(unit_.pos_);
}

void Player::Init(void)
{
	// 生存フラグの初期化
	unit_.isAlive_ = true;

	// 座標の初期化
	unit_.pos_ = START_POS;

	// アニメーション変数の初期化
	animCounter_ = 0;
	animInterval_ = 0;

	parry_->Init();

	// ステートの初期化
	state_ = STATE::MOVE;
}

void Player::Update(void)
{
	// 入力情報の更新
	Input();

	// 現在のステートに対応する関数を実行
	(this->*stateFuncPtr_[state_])();

	parry_->Update();

	// アニメーションの更新
	Animation();
}

void Player::Draw(void)
{
	// 生存フラグfalseで早期リターン
	if (!unit_.isAlive_)return;

	// プレイヤーの描画
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, 0, img_[animCounter_], true);

	parry_->Draw();

}

void Player::Release(void)
{
	parry_->Release();
	// 画像解放
	for (auto& id : img_) { DeleteGraph(id); }
}


void Player::Animation(void)
{
	if (++animInterval_ >= ANIM_SPEED) {
		animInterval_ = 0;
		if (++animCounter_ >= ANIM_NUM) {
			animCounter_ = 0;
		}
	}
}

void Player::Move(void)
{
	Vector2 moveVec = {};

	if (up_.now_) { moveVec.y--; }
	if (down_.now_) { moveVec.y++; }
	if (left_.now_) { moveVec.x--; }
	if (right_.now_) { moveVec.x++; }

	moveVec *= unit_.para_.speed_;

	unit_.pos_ += moveVec;

	Vector2 min = { unit_.para_.size.x / 2,unit_.para_.size.y / 2 };
	Vector2 max = { Application::SCREEN_SIZE_X - min.x,Application::SCREEN_SIZE_Y - min.y };
	if (unit_.pos_.x < min.x) { unit_.pos_.x = min.x; }
	if (unit_.pos_.y < min.y) { unit_.pos_.y = min.y; }
	if (unit_.pos_.x > max.x) { unit_.pos_.x = max.x; }
	if (unit_.pos_.y > max.y) { unit_.pos_.y = max.y; }

	if (attackKey_.downTrg_) { state_ = STATE::ATTACK; }
	if (specialKey_.downTrg_) { state_ = STATE::SPECIAL; }
}

void Player::Attack(void)
{
	parry_->On();

	state_ = STATE::MOVE;
}

void Player::Special(void)
{
	state_ = STATE::MOVE;
}

void Player::Death(void)
{
}

void Player::Input(void)
{
	up_.prev_ = up_.now_;
	up_.now_ = ((CheckHitKey(KEY_INPUT_UP) == 0) &&
		(CheckHitKey(KEY_INPUT_W) == 0)) ? false : true;
	up_.downTrg_ = (!up_.prev_ && up_.now_);
	up_.upTrg_ = (up_.prev_ && !up_.now_);

	down_.prev_ = down_.now_;
	down_.now_ = ((CheckHitKey(KEY_INPUT_DOWN) == 0) &&
		(CheckHitKey(KEY_INPUT_S) == 0)) ? false : true;
	down_.downTrg_ = (!down_.prev_ && down_.now_);
	down_.upTrg_ = (down_.prev_ && !down_.now_);

	left_.prev_ = left_.now_;
	left_.now_ = ((CheckHitKey(KEY_INPUT_LEFT) == 0) &&
		(CheckHitKey(KEY_INPUT_A) == 0)) ? false : true;
	left_.downTrg_ = (!left_.prev_ && left_.now_);
	left_.upTrg_ = (left_.prev_ && !left_.now_);

	right_.prev_ = right_.now_;
	right_.now_ = ((CheckHitKey(KEY_INPUT_RIGHT) == 0) &&
		(CheckHitKey(KEY_INPUT_D) == 0)) ? false : true;
	right_.downTrg_ = (!right_.prev_ && right_.now_);
	right_.upTrg_ = (right_.prev_ && !right_.now_);

	attackKey_.prev_ = attackKey_.now_;
	attackKey_.now_ = ((CheckHitKey(KEY_INPUT_SPACE) == 0) &&
		(CheckHitKey(KEY_INPUT_J) == 0)) ? false : true;
	attackKey_.downTrg_ = (!attackKey_.prev_ && attackKey_.now_);
	attackKey_.upTrg_ = (attackKey_.prev_ && !attackKey_.now_);

	specialKey_.prev_ = specialKey_.now_;
	specialKey_.now_ = ((CheckHitKey(KEY_INPUT_V) == 0) &&
		(CheckHitKey(KEY_INPUT_B) == 0)) ? false : true;
	specialKey_.downTrg_ = (!specialKey_.prev_ && specialKey_.now_);
	specialKey_.upTrg_ = (specialKey_.prev_ && !specialKey_.now_);
}
