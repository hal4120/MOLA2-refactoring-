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
	sounds_[SOUND::BGM1].path_ = "4m.rarara.mp3";
}

void SoundManager:: Release(void)
{
	// ��������Ă��Ȃ����̂����ׂĉ������
	for (auto& sound : sounds_) {
		if (sound.id_ != -1) { DeleteSoundMem(sound.id_); }
	}
}