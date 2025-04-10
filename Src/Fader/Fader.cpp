#include<DxLib.h>
#include"Fader.h"
#include"../Application.h"

Fader::Fader(void)
{

}

Fader::~Fader(void)
{

}

//初期化処理（最初の一回のみ実行）
bool Fader::SystemInit(void)
{
	GameInit();

	return true;
}

//ゲーム起動・再開時に必ず呼び出す処理
void Fader::GameInit(void)
{
	stat = E_STAT_FADE_NON;
	alpha = 0.0f;
	endFlg = true;
}

//更新処理
void Fader::Update(void)
{
	if (endFlg)return;

	switch (stat){
	case E_STAT_FADE_NON:
		return;
	case E_STAT_FADE_OUT:
		alpha += FADE_SPEED_ALPHA;				//アルファ値を加算して少しずつ見えなく（少しずつ不透明に）する
		if (alpha > 255.0f) {
			//フェードアウト終了
			alpha = 255.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	case E_STAT_FADE_IN:
		alpha -= FADE_SPEED_ALPHA;				//アルファ値を減産して少しずつ見る様に（少しずつ透明に）する
		if (alpha < 0) {
			//フェードイン終了
			alpha = 0.0f;
			endFlg = true;
			stat = E_STAT_FADE_NON;
		}
		break;
	default:
		return;
	}
}

//描画処理
void Fader::Draw(void)
{
	switch (stat)
	{
	case E_STAT_FADE_NON:
		return;
	case E_STAT_FADE_OUT:
	case E_STAT_FADE_IN:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)alpha);		//アルファ値をブレンドするモードに設定する
		DrawBox(0, 0, Application::SCREEN_SIZE_WID, Application::SCREEN_SIZE_HIG, GetColor(0,0,0),true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);				//ブレンド市内通常のモードに戻す
		break;
	default:
		return;
	}
}

//解放処理（最後の一回のみ実行）
bool Fader::Release(void)
{
	return true;
}

//フェードアウト・フェードインを開始するときに呼び出す
void Fader::SetFade(E_FADE_STAT_ID id)
{
	
	stat = id;
	if (stat != E_STAT_FADE_NON) {
		endFlg = false;
	}
}
