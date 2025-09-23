#pragma once

// �N���X�̑O���錾
class FPS;

class Application
{
public:
	// �X�N���[���T�C�Y
	static constexpr int SCREEN_SIZE_X = 1600;	// �X�N���[������;
	static constexpr int SCREEN_SIZE_Y = 900;	// �X�N���[���c��;

public:
	// �V���O���g���i�����E�擾�E�폜�j
	static void CreateInstance(void) { if (instance_ == nullptr) { instance_ = new Application(); instance_->Init(); } }
	static Application& GetInstance(void) { return *instance_; }
	static void DeleteInstance(void) { if (instance_ != nullptr) delete instance_; instance_ = nullptr; }

public:

	void Init(void);	// ������
	void Run(void);		// �Q�[�����[�v�̊J�n
	void Release(void);	// ���

	// �Q�[���I��
	void GameEnd(void) { gameEnd_ = true; }

	// �����������^���s�̔���
	bool IsInitFail(void) const { return isInitFail_; };

	// ��������^���s�̔���
	bool IsReleaseFail(void) const { return isReleaseFail_; };

private:
	// �f�t�H���g�R���X�g���N�^��private�ɂ��āA
	// �O�����琶���ł��Ȃ��l�ɂ���
	Application(void);

	// �f�X�g���N�^�����l
	~Application(void);

	// �R�s�[�E���[�u������֎~
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	Application(Application&&) = delete;
	Application& operator=(Application&&) = delete;

	// ���L���R���p�C���G���[�����邽�� ��L��ǉ�
	// Application copy = *Application::GetInstance();
	// Application copied(*Application::GetInstance());
	// Application moved = std::move(*Application::GetInstance());
private:

	// �ÓI�C���X�^���X
	static Application* instance_;

	// �I���t���O
	bool gameEnd_;

	// ���������s
	bool isInitFail_;

	// ������s
	bool isReleaseFail_;

	// FPS
	FPS* fps_;
};
