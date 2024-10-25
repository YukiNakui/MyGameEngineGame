#pragma once
#define SAFE_DELETE(p) if(p != nullptr){ delete p; p = nullptr; }        //Delete�����̃}�N��
#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr; }   //Relese�����̃}�N��

//�C���N���[�h
#include<d3d11.h>
#include<assert.h>

enum SHADER_TYPE {
	SHADER_2D,
	SHADER_3D,
	SHADER_MAX
};

//�����J
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace Direct3D
{
	//������ ���s�������i�iWinMain�j
	HRESULT Initialize(int winW, int winH, HWND hWnd);

	//�V�F�[�_�[���� ���s�������i�iInitialize�j�ɕ�
	HRESULT InitShader();//�G���[���o���Ƃ��ɃG���[���o���ƒm�点����悤�ɖ߂�l��HRESULT(HRESULT�̓G���[�̓��e������)
	HRESULT InitShader3D();//simple3D.hlsl�̂��߂̏�����
	HRESULT InitShader2D();//simple2D.hlsl�̂��߂̏�����

	void SetShader(SHADER_TYPE type);

	//�`��J�n
	void BeginDraw();

	//�`��I��
	void EndDraw();

	//���
	void Release();

	extern ID3D11Device* pDevice;
	extern ID3D11DeviceContext* pContext;
	extern const int WINDOW_WIDTH;
	extern const int WINDOW_HEIGHT;
};
