#pragma once

#include <dInput.h>
#include<DirectXMath.h>

#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

//Direct3D�Ƃ͕ʕ��Ƃ͊֌W�Ȃ��w�b�_�[�����炱���ł�#define���Ƃ�
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);

	DirectX::XMVECTOR GetMousePosition();
	void SetMousePosition(int x, int y);
	bool IsMouseButton(int buttonCode);
	bool IsMouseButtonDown(int buttonCode);
	bool IsMouseButtonUp(int buttonCode);
	void Release();
};