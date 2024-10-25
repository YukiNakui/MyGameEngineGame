#pragma once
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr; }        //Delete処理のマクロ
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr; }   //Relese処理のマクロ

//インクルード
#include<d3d11.h>
#include<assert.h>

enum SHADER_TYPE {
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX
};

//リンカ
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Direct3D
{
	//初期化 失敗したら上司（WinMain）
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//シェーダー準備 失敗したら上司（Initialize）に報告
	HRESULT InitShader();//エラーが出たときにエラーが出たと知らせられるように戻り値はHRESULT(HRESULTはエラーの内容が入る)
	HRESULT InitShader3D();//simple3D.hlslのための初期化
	HRESULT InitShader2D();//simple2D.hlslのための初期化

	void SetShader(SHADER_TYPE type);

	//描画開始
	void BeginDraw();

	//描画終了
	void EndDraw();

	//解放
	void Release();

	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;
	extern const int WINDOW_WIDTH;
	extern const int WINDOW_HEIGHT;
};
