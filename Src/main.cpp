//------------------------------------
// �Q�[������FAsoQuest
// ����		 �F2416081 �R�{�I
//------------------------------------
#include<DxLib.h>
#include"Application.h"

//----------------
// WinMain�֐�
//----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//�A�v���P�[�V�����N���X�̎��̉������C���X�^���X�̍쐬
	Application::CreateInstance();
	if (Application::GetInstance().IsError())return -1;

	//�Q�[���N��
	Application::GetInstance().Run();

	//�������
	Application::GetInstance().Release();
	if (Application::GetInstance().IsError())return -1;
	Application::DeleteInstance();

	return 0;		//�Q�[���I��
}
