#include "Player.h"

#include<DxLib.h>

#include"../../Manager/Input/InputManager.h"
#include"../../Manager/Input/KeyManager.h"
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
	dir_(DIR::RIGHT),

	parry_(nullptr),
	laser_(nullptr),

	gameEnd_(false),

	specialCharge_(0),
	specialChargeImg_(),
	specialChargeMaxImg_(-1),
	specialChargeMaxFlash_(0),

	specialChargeMaxButtonImg_(),
	specialChargeMaxKeyImg_(),

	uiImg_(-1),
	lifeImg_()
{
}

Player::~Player()
{
}

void Player::Load(void)
{
	// �v���C���[�摜�̓ǂݍ���
	Utility::LoadArrayImg("Data/Image/Player/�܂�.png",
		ANIM_NUM, ANIM_NUM_X, ANIM_NUM_Y,
		LOAD_SIZE_X, LOAD_SIZE_Y, img_);
	
	// UI
	Utility::LoadImg(uiImg_, "Data/Image/Player/UI/�܂�UI.png");
	for (int i = 0; i <= LIFE_MAX; i++) {
		Utility::LoadImg(lifeImg_[i], "Data/Image/Player/UI/Life/" + std::to_string(i) + ".png");
	}
	Utility::LoadArrayImg("Data/Image/Player/UI/Special/SpecialCharge.png", SPECIAL_CHARGE_MAX + 1, 1, SPECIAL_CHARGE_MAX + 1, 1600, 103, specialChargeImg_);
	Utility::LoadImg(specialChargeMaxImg_, "Data/Image/Player/UI/Special/SpecialChargeMax.png");

	for (int i = 0; i < 2; i++) {
		std::string sPath = "Data/Image/Player/UI/Special/Button/";
		std::string ePath = ".png";
		Utility::LoadImg(specialChargeMaxButtonImg_[i], (sPath + std::to_string(i + 1) + ePath).c_str());
	}
	for (int i = 0; i < 2; i++) {
		std::string sPath = "Data/Image/Player/UI/Special/Key/";
		std::string ePath = ".png";
		Utility::LoadImg(specialChargeMaxKeyImg_[i], (sPath + std::to_string(i + 1) + ePath).c_str());
	}

	// �֐��|�C���^�ɂ��ꂼ��̊֐��̃|�C���^���i�[
	stateFuncPtr_[STATE::DEFAULT] = &Player::Default;
	stateFuncPtr_[STATE::SPECIAL] = &Player::Special;
	stateFuncPtr_[STATE::DEATH] = &Player::Death;
	stateFuncPtr_[STATE::OVER] = &Player::Over;

	unit_.para_.speed = SPEED;

	unit_.para_.size = { LOAD_SIZE_X,LOAD_SIZE_Y };

	unit_.para_.colliShape = CollisionShape::ELLIPSE;
	unit_.para_.colliType = CollisionType::ALLY;

	parry_ = new Parry(unit_.pos_, dir_);
	parry_->Load();
	parry_->SetSpChargeFun([this](void) { this->SpecialCharge(); });

	laser_ = new PlayerLaser(unit_.pos_,dir_);
	laser_->Load();

}

void Player::Init(void)
{
	// �����t���O�̏�����
	unit_.isAlive_ = true;

	// ���W�̏�����
	unit_.pos_ = START_POS;

	// ���C�t
	unit_.hp_ = LIFE_MAX;

	// �A�j���[�V�����ϐ��̏�����
	animCounter_ = 0;
	animInterval_ = 0;

	angle_ = 0.0f;

	parry_->Init();
	laser_->Init();

	// �X�e�[�g�̏�����
	state_ = STATE::DEFAULT;

	gameEnd_ = false;

	specialCharge_ = 0;

	dir_ = DIR::RIGHT;
}

void Player::Update(void)
{
	Invi();

	// ���݂̃X�e�[�g�ɑΉ�����֐������s
	(this->*stateFuncPtr_[state_])();

	parry_->Update();
	laser_->Update();

	// �A�j���[�V�����̍X�V
	Animation();
	
	if (CheckHitKey(KEY_INPUT_P) == 1) { SpecialCharge(); }
}

void Player::Draw(void)
{
	// �����t���Ofalse�ő������^�[��
	if (!unit_.isAlive_)return;

	// �v���C���[�̕`��
	if (unit_.inviciCounter_ / 10 % 2 == 1) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100); }
	DrawRotaGraphF(unit_.pos_.x, unit_.pos_.y, 1, angle_, img_[animCounter_], true, (bool)dir_);
	if (unit_.inviciCounter_ / 10 % 2 == 1) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }

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
	if (specialCharge_ >= SPECIAL_CHARGE_MAX) {
		if (specialChargeMaxFlash_ / 10 % 2 == 0) { SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150); }
		DrawRotaGraph3(150, (yy - (150 / 2) - 30), 0, 51, 0.3, 0.3, 0, specialChargeMaxImg_, true);
		if (specialChargeMaxFlash_ / 10 % 2 == 0) { SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); }
		DrawRotaGraph3(
			680, (yy - (150 / 2) - 30), 200, 200,
			0.2, 0.2, 0,
			(KEY::GetIns().GetControllerConnect()) ?
			specialChargeMaxButtonImg_[specialChargeMaxFlash_ / 10 % 2] :
			specialChargeMaxKeyImg_[specialChargeMaxFlash_ / 10 % 2],
			true
		);
	}
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

	// �摜���
	for (auto& id : specialChargeMaxButtonImg_) { DeleteGraph(id); }
	for (auto& id : specialChargeMaxKeyImg_) { DeleteGraph(id); }

	for (auto& id : specialChargeImg_) { DeleteGraph(id); }
	DeleteGraph(specialChargeMaxImg_);

	for (auto& id : lifeImg_) { DeleteGraph(id); }
	DeleteGraph(uiImg_);

	for (auto& id : img_) { DeleteGraph(id); }
}

void Player::OnCollision(UnitBase* other)
{
	if (state_ == STATE::DEATH) { return; }
	GameScene::Shake(ShakeKinds::ROUND, ShakeSize::MEDIUM,10);
	GameScene::Slow(10);

	Smng::GetIns().Play(SOUND::BLAST, true);

	BlastEffectManager::On(unit_.pos_);

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
	if (specialCharge_ >= SPECIAL_CHARGE_MAX) {
		if (++specialChargeMaxFlash_ >= 600) { specialChargeMaxFlash_ = 0; }
	}
}

void Player::Default(void)
{
	auto& key = KEY::GetIns();

	Vector2 moveVec = key.GetLeftStickVec();

	if (moveVec == 0.0f) {
		if (key.GetInfo(KEY_TYPE::UP).now) { moveVec.y--; }
		if (key.GetInfo(KEY_TYPE::DOWN).now) { moveVec.y++; }
		if (key.GetInfo(KEY_TYPE::LEFT).now) { moveVec.x--; }
		if (key.GetInfo(KEY_TYPE::RIGHT).now) { moveVec.x++; }
	}

	if (moveVec != 0.0f) {
		moveVec = Utility::Normalize(moveVec);
		moveVec *= unit_.para_.speed;
		unit_.pos_ += moveVec;

		if (moveVec.x != 0.0f && laser_->GetUnit().isAlive_ == false) {
			dir_ = (moveVec.x > 0.0f) ? DIR::RIGHT : DIR::LEFT;
		}

		Vector2 min = { unit_.para_.size.x / 2,unit_.para_.size.y / 2 };
		Vector2 max = { Application::SCREEN_SIZE_X - min.x,Application::SCREEN_SIZE_Y - min.y };
		if (unit_.pos_.x < min.x) { unit_.pos_.x = min.x; }
		if (unit_.pos_.y < min.y) { unit_.pos_.y = min.y; }
		if (unit_.pos_.x > max.x) { unit_.pos_.x = max.x; }
		if (unit_.pos_.y > max.y) { unit_.pos_.y = max.y; }
	}

	if (key.GetInfo(KEY_TYPE::ATTACK).down) { parry_->On(); }

	if (key.GetInfo(KEY_TYPE::SPECIAL_ATTACK).down && specialCharge_ >= SPECIAL_CHARGE_MAX) {
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