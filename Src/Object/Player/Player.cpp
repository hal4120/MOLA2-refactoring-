#include "Player.h"

#include<DxLib.h>

#include"../../Manager/Input/InputManager.h"
#include"../../Scene/Game/GameScene.h"
#include"../../Manager/BlastEffect/BlastEffectManager.h"
#include"../../Manager/Sound/SoundManager.h"

Player::Player():
	img_(),
	animCounter_(0),
	animInterval_(0),
	state_(STATE::DEFAULT),
	stateFuncPtr_(),
	knockBackVec_(),
	angle_(0.0f),
	parry_(nullptr),
	laser_(nullptr),
	gameEnd_(false),
	specialCharge_(0),
	specialChargeImg_(),
	uiImg_(-1),
	lifeImg_()
{
}

Player::~Player()
{
}

void Player::Load(void)
{
	// プレイヤー画像の読み込み
	Utility::LoadArrayImg("Data/Image/Player/まぼ.png",
		ANIM_NUM, ANIM_NUM_X, ANIM_NUM_Y,
		LOAD_SIZE_X, LOAD_SIZE_Y, img_);
	
	// UI
	Utility::LoadImg(uiImg_, "Data/Image/Player/UI/まぼUI.png");
	for (int i = 0; i <= LIFE_MAX; i++) {
		Utility::LoadImg(lifeImg_[i], "Data/Image/Player/UI/Life/" + std::to_string(i) + ".png");
	}
	Utility::LoadArrayImg("Data/Image/Player/UI/SpecialCharge.png", SPECIAL_CHARGE_MAX + 1, 1, SPECIAL_CHARGE_MAX + 1, 1600, 103, specialChargeImg_);

	// 関数ポインタにそれぞれの関数のポインタを格納
	stateFuncPtr_[STATE::DEFAULT] = &Player::Default;
	stateFuncPtr_[STATE::SPECIAL] = &Player::Special;
	stateFuncPtr_[STATE::DEATH] = &Player::Death;
	stateFuncPtr_[STATE::OVER] = &Player::Over;

	unit_.para_.speed = SPEED;

	unit_.para_.size = { LOAD_SIZE_X,LOAD_SIZE_Y };

	unit_.para_.colliShape = CollisionShape::ELLIPSE;
	unit_.para_.colliType = CollisionType::ALLY;

	parry_ = new Parry(unit_.pos_);
	parry_->Load();
	parry_->SetSpChargeFun([this](void) { this->SpecialCharge(); });

	laser_ = new PlayerLaser(unit_.pos_);
	laser_->Load();

}

void Player::Init(void)
{
	// 生存フラグの初期化
	unit_.isAlive_ = true;

	// 座標の初期化
	unit_.pos_ = START_POS;

	// ライフ
	unit_.hp_ = LIFE_MAX;

	// アニメーション変数の初期化
	animCounter_ = 0;
	animInterval_ = 0;

	angle_ = 0.0f;

	parry_->Init();
	laser_->Init();

	// ステートの初期化
	state_ = STATE::DEFAULT;

	gameEnd_ = false;

	specialCharge_ = 0;
}

void Player::Update(void)
{
	// 入力情報の更新
	Input();

	Invi();

	// 現在のステートに対応する関数を実行
	(this->*stateFuncPtr_[state_])();

	parry_->Update();
	laser_->Update();

	// アニメーションの更新
	Animation();
	
	if (CheckHitKey(KEY_INPUT_P) == 1) { SpecialCharge(); }
}

void Player::Draw(void)
{
	// 生存フラグfalseで早期リターン
	if (!unit_.isAlive_)return;

	// プレイヤーの描画
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, angle_, img_[animCounter_], true);

	parry_->Draw();
	laser_->Draw();
}

void Player::UIDraw(void)
{
	using app = Application;
	int xx = app::SCREEN_SIZE_X;
	int yy = app::SCREEN_SIZE_Y;
	int x = xx / 2;
	int y = yy / 2;

	DrawRotaGraph3(0, yy, 0, 500, 0.3, 0.3, 0, uiImg_, true);
	DrawRotaGraph3(160, (yy - (150 / 2))+30, 0, 150, 0.3, 0.3, 0, lifeImg_[unit_.hp_], true);
	DrawRotaGraph3(150, (yy - (150 / 2) - 30), 0, 51, 0.3, 0.3, 0, specialChargeImg_[specialCharge_], true);
}

void Player::Release(void)
{
	if (parry_) {
		parry_->Release();
		delete parry_;
		parry_ = nullptr;
	}
	if (laser_) {
		laser_->Release();
		delete laser_;
		laser_ = nullptr;
	}

	for (auto& id : lifeImg_) { DeleteGraph(id); }
	DeleteGraph(uiImg_);

	// 画像解放
	for (auto& id : img_) { DeleteGraph(id); }
}

void Player::OnCollision(UnitBase* other)
{
	if (state_ == STATE::DEATH) { return; }
	GameScene::Shake(ShakeKinds::ROUND, ShakeSize::MEDIUM);
	GameScene::Slow(20);

	Smng::GetIns().Play(SOUND::BLAST, true);

	knockBackVec_ = unit_.pos_ - other->GetUnit().pos_;
	knockBackVec_ /= sqrtf(knockBackVec_.x * knockBackVec_.x + knockBackVec_.y * knockBackVec_.y);

	state_ = STATE::DEATH;

	unit_.hp_--;
	if (unit_.hp_ <= 0) {
		unit_.hp_ = 0;
		state_ = STATE::OVER;
	}

	parry_->MagReset();
	laser_->Off();
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

void Player::Default(void)
{
	Vector2 moveVec = {};

	if (up_.now_) { moveVec.y--; }
	if (down_.now_) { moveVec.y++; }
	if (left_.now_) { moveVec.x--; }
	if (right_.now_) { moveVec.x++; }

	moveVec *= unit_.para_.speed;

	unit_.pos_ += moveVec;

	Vector2 min = { unit_.para_.size.x / 2,unit_.para_.size.y / 2 };
	Vector2 max = { Application::SCREEN_SIZE_X - min.x,Application::SCREEN_SIZE_Y - min.y };
	if (unit_.pos_.x < min.x) { unit_.pos_.x = min.x; }
	if (unit_.pos_.y < min.y) { unit_.pos_.y = min.y; }
	if (unit_.pos_.x > max.x) { unit_.pos_.x = max.x; }
	if (unit_.pos_.y > max.y) { unit_.pos_.y = max.y; }


	if (attackKey_.downTrg_) { parry_->On(); }

	if (specialKey_.downTrg_ && specialCharge_ >= SPECIAL_CHARGE_MAX) {
		specialCharge_ = 0;
		laser_->On();
		state_ = STATE::SPECIAL;
	}
}

void Player::Special(void)
{
	if (laser_->GetState() != PlayerLaser::STATE::CHARGE) { state_ = STATE::DEFAULT; }
}

void Player::Death(void)
{
	unit_.pos_ += knockBackVec_;
	angle_ -= Utility::Deg2RadF(3.0f);
	if (angle_ < -Utility::Deg2RadF(60.0f)) {
		unit_.inviciCounter_ = 100;
		unit_.pos_ = START_POS;
		angle_ = 0.0f;
		unit_.isAlive_ = true;
		state_ = STATE::DEFAULT;
	}
}

void Player::Over(void)
{
	GameScene::Slow();
	GameScene::Shake(ShakeKinds::ROUND, ShakeSize::BIG, 20);
	BlastEffectManager::On(unit_.pos_);
	Smng::GetIns().Play(SOUND::GAME_END);

	unit_.pos_ += knockBackVec_;

	angle_ -= Utility::Deg2RadF(3.0f);
	if (angle_ < -Utility::Deg2RadF(120.0f)) { gameEnd_ = true; }
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