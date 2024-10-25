#include "Input.h"

//キーボードもマウスも一つだけだからnamespaceにしてクラスは作らない
namespace Input
{
	//DirectInputオブジェクト
	LPDIRECTINPUT8   pDInput = nullptr;//DirectInput本体
	
	//キーボード
	LPDIRECTINPUTDEVICE8 pKeyDevice = nullptr;//キーボードデバイスオブジェクト
	BYTE keyState[256] = { 0 };//キーが押されてるかどうかの配列
	BYTE prevKeyState[256];    //前フレームでの各キーの状態

	//マウス
	LPDIRECTINPUTDEVICE8	pMouseDevice_;	//デバイスオブジェクト
	DIMOUSESTATE mouseState_;				//マウスの状態
	DIMOUSESTATE prevMouseState_;			//前フレームのマウスの状態
	DirectX::XMVECTOR mousePosition;

	void Initialize(HWND hWnd)
	{
		DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (VOID**)&pDInput, nullptr);
		
		pDInput->CreateDevice(GUID_SysKeyboard, &pKeyDevice, nullptr);
		pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
		//ほかの実行中のアプリに対する優先度（バックグラウンドにあるときは入力を受け付けないようにするなど）
		pKeyDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);

		pDInput->CreateDevice(GUID_SysMouse, &pMouseDevice_, nullptr);
		pMouseDevice_->SetDataFormat(&c_dfDIMouse);
		pMouseDevice_->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	}

	void Update()
	{
		memcpy(prevKeyState,keyState,sizeof(keyState));//keyStateの中身をprevKeyStateにコピーする

		pKeyDevice->Acquire();//これを書かないとキーを見失うらしい（マナーみたいなもの）
		pKeyDevice->GetDeviceState(sizeof(keyState), &keyState);//全キーの状態が配列に入る

		pMouseDevice_->Acquire();
		memcpy(&prevMouseState_, &mouseState_, sizeof(mouseState_));
		pMouseDevice_->GetDeviceState(sizeof(mouseState_), &mouseState_);
	}

	bool IsKey(int keyCode)
	{
		//ビットの計算というのが分かるように16進数で表現した方がよい
		//キーが押されているときはtrue
		if (keyState[keyCode] & 0x80) {//keyState[keyCode]の中身の最上位のビットが1ならtrue
			return true;
		}
		return false;
	}

	bool IsKeyDown(int keyCode)
	{
		//今は押してて、前回は押してない
		if (IsKey(keyCode) && !(prevKeyState[keyCode] & 0x80)) {
			return true;
		}
		return false;
	}

	bool IsKeyUp(int keyCode)
	{
		//今は押してなくて、前回は押してた
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
		//押してる
		if (mouseState_.rgbButtons[buttonCode] & 0x80)
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonDown(int buttonCode)
	{
		//今は押してて、前回は押してない
		if (IsMouseButton(buttonCode) && !(prevMouseState_.rgbButtons[buttonCode] & 0x80))
		{
			return true;
		}
		return false;
	}

	bool IsMouseButtonUp(int buttonCode)
	{
		//今押してなくて、前回は押してる
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
