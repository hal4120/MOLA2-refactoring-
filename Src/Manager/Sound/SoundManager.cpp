#include "SoundManager.h"

#include<DxLib.h>

SoundManager* SoundManager::ins_ = nullptr;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::Load(SOUND s)
{
	// ���łɓǂݍ��܂�Ă�����ǂݍ��܂Ȃ�
	if (sounds_[s].id_ != -1) return;

	// �ǂݍ���
	sounds_[s].id_ = LoadSoundMem(("Data/Sound/" + sounds_[s].path_).c_str());
	sounds_[s].type_ = s;
}

void SoundManager::Play(SOUND s, bool over, int volume, bool loop, bool topPlay)
{
	// �ǂݍ��܂�Ă��Ȃ�������Đ����Ȃ�
	if (sounds_[s].id_ == -1) return;

	// �Đ�����������Đ����Ȃ�
	if ((CheckSoundMem(sounds_[s].id_) == 1) && !over)return;

	// �����L�^
	sounds_[s].loop_ = loop;
	sounds_[s].paused_ = false;

	// ���ʂ�ݒ�
	if (sounds_[s].volume_ != volume) {
		sounds_[s].volume_ = volume;
		ChangeVolumeSoundMem(sounds_[s].volume_, sounds_[s].id_);
	}

	// �Đ�
	PlaySoundMem(sounds_[s].id_, (sounds_[s].loop_) ? DX_PLAYTYPE_LOOP : DX_PLAYTYPE_BACK, topPlay);
}

void SoundManager::Stop(SOUND s)
{
	// �ǂݍ��܂�Ă��Ȃ�������Đ����Ȃ�
	if (sounds_[s].id_ == -1) return;

	// �Đ�������Ȃ������瑁�����^�[��
	if (CheckSoundMem(sounds_[s].id_) == 0)return;

	// ��~
	StopSoundMem(sounds_[s].id_);
}

void SoundManager::AllStop(void)
{
	for (auto& sound : sounds_) {
		if (sound.id_ == -1)continue;
		if (CheckSoundMem(sound.id_) == 0)continue;

		sound.paused_ = true;
		StopSoundMem(sound.id_);
	}
}

void SoundManager::PausePlay(void)
{
	for (auto& sound : sounds_) {
		if (!sound.paused_)continue;

		Play(sound.type_, false, sound.volume_, sound.loop_, false);
	}
}

void SoundManager::PauseInfoDelete(void)
{
	for (auto& sound : sounds_) { sound.paused_ = false; }
}

void SoundManager::Delete(SOUND s)
{
	// ���g���Ȃ������瑁�����^�[��
	if (sounds_[s].id_ == -1) return;

	// ���g����������-1�����Ƃ�
	DeleteSoundMem(sounds_[s].id_);
	sounds_[s].id_ = -1;
	sounds_[s].paused_ = false;
	sounds_[s].volume_ = 255;
}

void SoundManager::Init(void)
{
	// �n���h��ID�̕ϐ��������ׂ�-1�ŏ�����
	// �ꎞ��~�����������
	for (auto& sound : sounds_) {
		sound.id_ = -1;
		sound.paused_ = false;
		sound.volume_ = 255;
	}

	// �g�p����f�[�^�̃p�X�����Ă���("Data/Sound/�`�`"�����������̃p�X)
	sounds_[SOUND::BGM_RARARA].path_ = "BGM/Rarara.mp3";
	sounds_[SOUND::BGM_BOSS].path_ = "BGM/BossBgm.mp3";
	sounds_[SOUND::BGM_TITLE].path_ = "BGM/�J�[�g�D�[���E�L���B�Y�V���b�v.mp3";
	sounds_[SOUND::BGM_GAMEOVER].path_ = "BGM/GameOverBGM.mp3";


	sounds_[SOUND::PLAYER_ATTACK].path_ = "SE/Parry.mp3";
	sounds_[SOUND::PARRY].path_ = "SE/Ko.mp3";

	sounds_[SOUND::PLAYER_LASER].path_ = "SE/Laser.mp3";
	sounds_[SOUND::PLAYER_LASER_CHARGE].path_ = "SE/LaserCharge.mp3";

	sounds_[SOUND::CHAIN].path_ = "SE/Game/�A��.mp3";

	sounds_[SOUND::BLAST].path_ = "SE/Blast.mp3";

	sounds_[SOUND::WARNING].path_ = "SE/Warning.mp3";

	sounds_[SOUND::GAME_END].path_ = "SE/GameEnd.mp3";
	sounds_[SOUND::CLEAR].path_ = "SE/Clear.mp3";

	sounds_[SOUND::IKURA].path_ = "SE/�Ղ��Ղ�.mp3";
	sounds_[SOUND::BOSS_LASER].path_ = "SE/Laser.mp3";
	sounds_[SOUND::BOSS_LASER_CHARGE].path_ = "SE/LaserCharge.mp3";

	sounds_[SOUND::SPHERE_SHOT].path_ = "SE/Game/Boss/Kraken/Attack/Sphere/Shot.mp3";
	sounds_[SOUND::TENTACLE_SLAM].path_ = "SE/Game/Boss/Kraken/Attack/Tentacle/Slam.mp3";

	sounds_[SOUND::SELECT].path_ = "SE/Select.mp3";
	sounds_[SOUND::BUTTON].path_ = "SE/Button.mp3";

}

void SoundManager:: Release(void)
{
	// ��������Ă��Ȃ����̂����ׂĉ������
	for (auto& sound : sounds_) {
		if (sound.id_ != -1) { DeleteSoundMem(sound.id_); }
	}

	Smng::GetIns().Delete(SOUND::SPHERE_SHOT);
}