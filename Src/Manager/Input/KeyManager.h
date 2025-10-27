#pragma once

#include<vector>
#include"../../Common/Vector2.h"

class KeyManager
{
private:
	static KeyManager* ins;

	KeyManager();
	~KeyManager() {};
public:
	static void CreateIns(void) { if (ins == nullptr) { ins = new KeyManager(); ins->Init(); } }
	static KeyManager& GetIns(void) { return *ins; }
	static void DeleteIns(void) { if (ins != nullptr) { ins->Release(); delete ins; ins = nullptr; } }

	void Update(void);

	enum class KEY_TYPE
	{
		NON = -1,

		// �ėp����
		UP,
		DOWN,
		RIGHT,
		LEFT,
		// �v���C���[����
		ATTACK,
		SPECIAL_ATTACK,

		// �V�X�e������
		PAUSE,

		GAME_END,

		DEBUG,

		MAX,
	};

	struct KEY_INFO { bool prev = false, now = false, up = false, down = false; };

	const KEY_INFO GetInfo(KEY_TYPE k) { return keyInfo[(int)k]; }

	bool GetControllerConnect(void) const;

	Vector2 GetRightStickVec(void) const;
	Vector2 GetLeftStickVec(void) const;

	struct MOUCE_INFO
	{
		Vector2I now = {};
		Vector2I prev = {};
		Vector2 move = {};
	};

	const MOUCE_INFO GetMouceInfo(void)const { return mouceInfo; }
	const Vector2 GetMouceMove(void)const { return mouceInfo.move; }

	const Vector2I GetMoucePoint(void)const { return mouceInfo.now; }

	/// <summary>
	/// �}�E�X�J�[�\���𒆐S�ɌŒ肷��ݒ�
	/// (�Œ肵���ꍇGetMouceMove()�ɂă}�E�X�̒P�ʃx�N�g�����󂯎���)
	/// </summary>
	/// <param name="fixed">true=�Œ肷��Afalse=�Œ肵�Ȃ�</param>
	void SetMouceFixed(bool fixed) { mouceFixed_ = fixed; }

private:
	void Init(void);
	void Release(void);

	void KeyUpdate(void);

	KEY_INFO keyInfo[(int)KEY_TYPE::MAX];

	std::vector<int>keyboardFormat[(int)KEY_TYPE::MAX];
	std::vector<int>controllerButtonFormat[(int)KEY_TYPE::MAX];
	std::vector<int>mouceButtonFormat[(int)KEY_TYPE::MAX];
	enum class CONTROLLER_OTHERS
	{
		LEFTSTICK_UP,
		LEFTSTICK_DOWN,
		LEFTSTICK_RIGHT,
		LEFTSTICK_LEFT,

		RIGHTSTICK_UP,
		RIGHTSTICK_DOWN,
		RIGHTSTICK_RIGHT,
		RIGHTSTICK_LEFT,

		LEFT_TRIGGER,
		RIGHT_TRIGGER,
	};
	std::vector<CONTROLLER_OTHERS>controllerOthersFormat[(int)KEY_TYPE::MAX];
	bool ControllerOthersInput(const CONTROLLER_OTHERS& input);


	void MouceUpdate(void);
	MOUCE_INFO mouceInfo;
	bool mouceFixed_;
	const float MOUCE_THRESHOLD = 1.0f;
};

using KEY = KeyManager;
using KEY_TYPE = KEY::KEY_TYPE;