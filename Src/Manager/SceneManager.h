#pragma once

#include"../StDefineData.h"

class Fader;
class TitleScene;
class Score;
class ModeSelect;
class GameScene;
class GameOverScene;

class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	//�C���X�^���X�̐���
	static void CreateInstance(void) { if (instance == nullptr)instance = new SceneManager(); instance->SystemInit(); }
	//�C���X�^���X�̎擾
	static SceneManager& GetInstance(void) { return *instance; }
	//�C���X�^���X�̏���
	static void DeleteInstance(void) { if (instance != nullptr)delete instance; instance = nullptr; }



	bool SystemInit(void);						//����������
	void Update(void);							//�X�V����
	void Draw(void);							//�`�揈��
	bool Release(void);							//�������



private:
	//�ÓI�C���X�^���X
	static SceneManager* instance;

	TitleScene* titleInst;						//�^�C�g���N���X�̃C���X�^���X
	Score* scoreInst;							//�X�R�A��ʃN���X�̃C���X�^���X
	ModeSelect* modeselectInst;
	GameScene* gameInst;						//�Q�[���V�[���N���X�̃C���X�^���X
	GameOverScene* gameover;
	Fader* fader;								//�t�F�[�h�N���X�̃C���X�^���X

	E_SCENE_ID scene_ID;						//���݂̃V�[��

	E_SCENE_ID waitScene;
	bool sceneChangeFlg;

	bool ChangeScene(E_SCENE_ID id);
	void ReleaseScene(E_SCENE_ID id);

};

