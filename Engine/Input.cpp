#include "Input.h"

//�L�[�{�[�h���}�E�X�������������namespace�ɂ��ăN���X�͍��Ȃ�
namespace Input
{
	//DirectInput�I�u�W�F�N�g
	LPDIRECTINPUT8   pDInput = nullptr;//DirectInput�{��
	
	//�L�[�{�[�h
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;//�L�[�{�[�h�f�o�C�X�I�u�W�F�N�g
	BYTE keyState[256] = { 0 };//�L�[��������Ă邩�ǂ����̔z��
	BYTE prevKeyState[256];    //�O�t���[���ł̊e�L�[�̏��

	//�}�E�X
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//�f�o�C�X�I�u�W�F�N�g
	DIMOUSESTATE mouseState_;				//�}�E�X�̏��
	DIMOUSESTATE prevMouseState_;			//�O�t���[���̃}�E�X�̏��
	DirectX::XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		//�ق��̎��s���̃A�v���ɑ΂���D��x�i�o�b�N�O���E���h�ɂ���Ƃ��͓��͂��󂯕t���Ȃ��悤�ɂ���Ȃǁj
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState,keyState,sizeof(keyState));//keyState�̒��g��prevKeyState�ɃR�s�[����

		pKeyDevice->Acquire();//����������Ȃ��ƃL�[���������炵���i�}�i�[�݂����Ȃ��́j
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);//�S�L�[�̏�Ԃ��z��ɓ���

		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
	}

	bool IsKey(int keyCode)
	{
		//�r�b�g�̌v�Z�Ƃ����̂�������悤��16�i���ŕ\�����������悢
		//�L�[��������Ă���Ƃ���true
		if (keyState[keyCode] & 0x80) {//keyState[keyCode]�̒��g�̍ŏ�ʂ̃r�b�g��1�Ȃ�true
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//���͉����ĂȂ��āA�O��͉����Ă�
		if (!IsKey(keyCode) && (prevKeyState[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	DirectX::XMVECTOR GetMousePosition()
	{
		return mousePosition;
	}

	void SetMousePosition(int x, int y)
	{
		mousePosition = DirectX::XMVectorSet((float)x, (float)y, 0, 0);
	}

	bool IsMouseButton(int buttonCode)
	{
		//�����Ă�
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int buttonCode)
	{
		//���͉����ĂāA�O��͉����ĂȂ�
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int buttonCode)
	{
		//�������ĂȂ��āA�O��͉����Ă�
		if (!IsMouseButton(buttonCode) && prevMouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	void Release()
	{
		SAFE_RELEASE(pDInput);
		SAFE_RELEASE(pKeyDevice);
		SAFE_RELEASE(pMouseDevice_);
	}
}
