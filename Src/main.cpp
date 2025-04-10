//------------------------------------
// ゲーム制作：AsoQuest
// 氏名		 ：2416081 山本悠
//------------------------------------
#include<DxLib.h>
#include"Application.h"

//----------------
// WinMain関数
//----------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//アプリケーションクラスの実体化したインスタンスの作成
	Application::CreateInstance();
	if (Application::GetInstance().IsError())return -1;

	//ゲーム起動
	Application::GetInstance().Run();

	//解放処理
	Application::GetInstance().Release();
	if (Application::GetInstance().IsError())return -1;
	Application::DeleteInstance();

	return 0;		//ゲーム終了
}
