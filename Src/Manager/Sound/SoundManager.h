#pragma once

#include<map>
#include<string>

class SoundManager
{
private:
	SoundManager();
	~SoundManager();
public:
	static void CreateIns(void) { if (ins_ == nullptr) { ins_ = new SoundManager(); ins_->Init(); } }
	static SoundManager& GetIns(void) { CreateIns(); return *ins_; }
	static void DeleteIns(void) { if (ins_ != nullptr) { ins_->Release(); delete ins_; } }

	enum SOUND
	{
		NON=-1,

		//BGM----------------
		BGM_RARARA,
		BGM_BOSS,
		BGM_TITLE,
		BGM_GAMEOVER,

		//-------------------

		//SE�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

		//GAME------------------

		// �v���C���[
		PLAYER_ATTACK,
		PARRY,
		PLAYER_LASER,
		PLAYER_LASER_CHARGE,

		// ����
		BLAST,

		// �{�X�o��
		WARNING,

		// �Q�[���I�[�o�[
		GAME_END,
		// �Q�[���N���A
		CLEAR,


		// �T��
		IKURA,
		BOSS_LASER,
		BOSS_LASER_CHARGE,

		// �C�J
		SPHERE_SHOT,

		

		//-----------------------

		//System----------------
		SELECT,	//�v�b���Ċ���
		BUTTON,	//�s�b���Ċ���

		//----------------------


		//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`


		MAX,
	};

	/// <summary>
	/// �w�肵���T�E���h�����[�h
	/// </summary>
	/// <param name="s">���</param>
	void Load(SOUND s);

	/// <summary>
	/// �w�肵���T�E���h���Đ�
	/// </summary>
	/// <param name="s">���</param>
	/// <param name="over">�Đ����̂�������Đ����邩�ǂ���</param>
	/// <param name="volume">����</param>
	/// <param name="loop">���[�v�Đ�</param>
	/// <param name="topPlay">�ŏ�����Đ����邩</param>
	void Play(SOUND s, bool over = false, int volume = 200, bool loop = false, bool topPlay = true);

	/// <summary>
	/// �w�肵���T�E���h���~
	/// </summary>
	/// <param name="s">���</param>
	void Stop(SOUND s);

	/// <summary>
	/// �Đ����̃T�E���h�����ׂĒ�~
	/// </summary>
	void AllStop(void);

	/// <summary>
	/// AllStop()�ňꎞ��~�����T�E���h�����ׂčĐ��ĊJ
	/// </summary>
	void PausePlay(void);

	/// <summary>
	/// AllStop()�ňꎞ��~�����T�E���h�̃|�[�Y����j������
	/// </summary>
	/// <param name=""></param>
	void PauseInfoDelete(void);

	/// <summary>
	/// �w�肵���T�E���h������
	/// </summary>
	/// <param name="s">���</param>
	void Delete(SOUND s);

private:
	static SoundManager* ins_;

	struct Sinfo
	{
		SOUND type_ = SOUND::NON;
		std::string path_;
		int id_ = -1;
		bool loop_ = false;
		bool paused_ = false;
		int volume_ = 255;
	};

	Sinfo sounds_[SOUND::MAX];


	void Init(void);
	void Release(void);
};

using Smng = SoundManager;

using SOUND = Smng::SOUND;