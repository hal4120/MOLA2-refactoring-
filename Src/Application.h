#pragma once

#include<string>

#include"FPS/FPS.h"

#include"Vector2/Vector2.h"
#include"Vector2/Vector2F.h"

class Application
{
private:
	Application();	//�R���X�g���N�^
	~Application();	//�f�X�g���N�^

public:
	static constexpr int SCREEN_SIZE_WID = 1000;	//�Q�[����ʂ̉��T�C�Y
	static constexpr int SCREEN_SIZE_HIG = 640;		//�Q�[����ʏc�T�C�Y

	static constexpr int DEFAULT_FPS = 60.0f;

	//�C���X�^���X�̐���
	static void  CreateInstance(void) { if (instance == nullptr)instance = new Application(); instance->SystemInit(); }
	//�C���X�^���X�̎擾
	static Application& GetInstance(void) { return *instance; }
	//�C���X�^���X�̍폜
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }

	void SystemInit(void);						//����������
	void Run(void);								//�Q�[���N��
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��
	void Release(void);							//�������

	//�G���[����
	bool IsError(void);

	//�l�̌ܓ�
	static int Round(float val) { return static_cast<int>(round(val)); }
	static Vector2 Round(Vector2F val);

private:
	//�ÓI�C���X�^���X
	static Application* instance;

	FPS* fps;

	//�G���[���
	bool errorInfo;

	//BGM�Ɋւ���ϐ�-----
	int bgm;
	bool bgmflg;
	int clearsound;
	//--------------------


	//�摜�E�����ǂݍ��݊֐�
	bool Load(void);


	//�|�[�Y��ʂɊւ���ϐ�------------
	int pauseimage[5];
	int selectSound, button;

	bool pause, end;
	bool select;

	int nowEscape, prevEscaoe;
	int nowSpaceKey, prevSpaceKey;

	Vector2 pausegame, pausetitle;
	//----------------------------------
};

