//-------------------------------------------------------------------
// �Q�[������Fshooting
// �����@�@�@�F2416081�@�R�{ �I
//-------------------------------------------------------------------
#include <DxLib.h>
#include"TitleScene.h"
#include"../Manager/SceneManager.h"
#include"../Application.h"

TitleScene::TitleScene(void)
{
	image = -1;
}

TitleScene::~TitleScene(void)
{
}

bool TitleScene::SystemInit(void)
{
	image = LoadGraph("Data/image/Title.png");
	if (image == -1)return false;

	return true;
}

void TitleScene::GameInit(void)
{
	pos.x = 0;
	pos.y = Application::SCREEN_SIZE_HIG / 2 - HIG / 2;

	nextSceneID = E_SCENE_TITLE;		//���̃V�[���̏�����
	prevSpaceKey = nowSpaceKey = 0;
	prevPadKey = nowPadKey = 0;
}

void TitleScene::Update(void)
{
	prevSpaceKey = nowSpaceKey;
	nowSpaceKey = CheckHitKey(KEY_INPUT_SPACE);

	prevPadKey = nowPadKey;
	nowPadKey = GetJoypadInputState(DX_INPUT_PAD1) & PAD_INPUT_2;

	if ((prevSpaceKey == 1 && nowSpaceKey == 0) || (prevPadKey > 0 && nowPadKey == 0)) {
		nextSceneID = E_SCENE_SCORE;
	}
}

void TitleScene::Draw(void)
{
//	DrawGraph(pos.x, pos.y, image, true);
	DrawExtendGraph(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, image, true);

}

bool TitleScene::Release(void)
{
	if (DeleteGraph(image) == -1)return false;

	return true;
}

//�Q�b�^�[�֐�
E_SCENE_ID TitleScene::GetNextSceneID(void) { return nextSceneID; }
