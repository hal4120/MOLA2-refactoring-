#pragma once

//---------------
// �񋓌^��`
//---------------
//�V�[����`
enum E_SCENE_ID {
	E_SCENE_NON = -1,
	E_SCENE_TITLE,
	E_SCENE_SCORE,
	E_SCENE_MODESELECT,
	E_SCENE_GAME,
	E_SCENE_GAMEOVER,
	E_SCENE_GAMECLEAR,

	E_SCENE_ID_MAX,
};

//�t�F�[�h�̏��
enum E_FADE_STAT_ID {
	E_STAT_FADE_NON = -1,
	E_STAT_FADE_OUT,			//�t�F�[�h�A�E�g�i���X�ɈÓ]����j
	E_STAT_FADE_IN,			//�t�F�[�h�C���@�i���X�ɖ��]����j

	E_STAT_FADE_MAX,
};

enum MODE_ID {
	MODE_NON=-1,
	MODE_NORMAL,
	MODE_HARD,

	MODE_MAX,
};