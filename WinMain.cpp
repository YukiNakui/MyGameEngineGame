//�C���N���[�h
#include <Windows.h>
#include<cstdlib>
#include"Engine/Direct3D.h"
#include"Engine/Camera.h"
#include"Engine/RootJob.h"
#include"Engine/Input.h"
#include"Engine/Model.h"

//�����J
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "winmm.lib")

//�萔�錾
const wchar_t* WIN_CLASS_NAME = L"SampleGame";//�E�B���h�E�N���X��
const wchar_t* APP_NAME = L"�T���v���Q�[��";//�A�v���P�[�V������

RootJob* pRootJob = nullptr;//���[�g�W���u�i���ׂĂ̐e�j

//API�i�A�v���P�[�V�����v���O���~���O�C���^�[�t�F�[�X�j ���炩�̃A�v������肽���Ƃ��֗̕��@�\���܂Ƃ߂����́i�v���O�����p�j
//SDK�i�\�t�g�E�F�A�f�x���b�v�����g�L�b�g�j�\�t�g�E�F�A�J���L�b�g�i�v���O�����ȊO���܂ށj

//�v���g�^�C�v�錾
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//�G���g���[�|�C���g
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;                   //�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;            //�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;                   //�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;         //�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //�A�C�R��
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //�������A�C�R��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //�}�E�X�J�[�\��
	wc.lpszMenuName = NULL;                     //���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //�w�i�i���j
	RegisterClassEx(&wc); //�N���X��o�^

	//�E�B���h�E�T�C�Y�̌v�Z(�\���̈��WINDOW_WIDTH�~WINDOW_HEIGHT�Ɏw�肷�邽�߂̌v�Z)
	RECT winRect = { 0, 0, Direct3D::WINDOW_WIDTH, Direct3D::WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;     //�E�B���h�E��
	int winH = winRect.bottom - winRect.top;     //�E�B���h�E����


	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,         //�E�B���h�E�N���X��
		APP_NAME,     //�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW, //�X�^�C���i���ʂ̃E�B���h�E�j
		CW_USEDEFAULT,       //�\���ʒu���i���܂����j
		CW_USEDEFAULT,       //�\���ʒu��i���܂����j
		winW,                 //�E�B���h�E��
		winH,                 //�E�B���h�E����
		NULL,                //�e�E�C���h�E�i�Ȃ��j
		NULL,                //���j���[�i�Ȃ��j
		hInstance,           //�C���X�^���X
		NULL                 //�p�����[�^�i�Ȃ��j
	);

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	HRESULT hr;

	//Direct3D������
	hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))//E_�` ���A���Ă���������
	{
		//���s�������̏���
		MessageBox(NULL, L"Direct3D�̏������Ɏ��s���܂���", L"�G���[", MB_OK);
		return 0;
	}
	Input::Initialize(hWnd);

	Camera::Initialize();

	pRootJob = new RootJob(nullptr);
	pRootJob->Initialize();

	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		//���b�Z�[�W�Ȃ�
		else
		{//���̃J�b�R����1�t���[��
			//static�ŋN�������Ƃ��ɏ���������ďI���܂ŕێ����ꑱ����
			//����������ƁA�I���܂ŏ����Ȃ��̂Ń������������
			timeBeginPeriod(1);
			static DWORD startTime = timeGetTime();
			DWORD nowTime = timeGetTime();
			timeEndPeriod(1);

			static DWORD lastUpdateTime = nowTime;
			static DWORD countFps = 0;
			//timeGetTime() Windows���N�����Ă���̎��Ԃ��~���b
			//char str[16];
			if (nowTime - startTime >= 1000) {
				std::wstring str;
				wsprintf(str.data(), L"%u", countFps);
				SetWindowTextW(hWnd, str.c_str());

				countFps = 0;
				startTime = nowTime;
			}
			if (nowTime-lastUpdateTime<=1000.0f/60.0f) {
				continue;//1/60�b�����Ă��Ȃ��̂ŃX���[
			}
			lastUpdateTime = nowTime;//1/60�b�����Ă����̂ō��̎��ԂɍX�V
			//wsprintf(str.data(), L"%u", nowTime-startTime);
			countFps++;

			Input::Update();
			
			//�J�����̍X�V
			Camera::Update();

			//���[�g�W���u����Ȃ��邷�ׂẴI�u�W�F�N�g��Update����
			pRootJob->UpdateSub();

			//�Q�[���̏���
			Direct3D::BeginDraw();

			//���[�g�W���u����Ȃ��邷�ׂẴI�u�W�F�N�g��Draw����
			pRootJob->DrawSub();
			
			//�����ɃQ�[���̓��e������

			//�`�揈��
			Direct3D::EndDraw();
			
		}
	}

	Model::Release();
	pRootJob->ReleaseSub();
	Direct3D::Release();

	return 0;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j CALLBACK�����Ă�Ə���ɌĂ΂�� typedef��int�Ȃǂ̌^�ɖ��O��t����� define�Ő��l�ɕʖ�������
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY://�~�}�[�N�������ꂽ�Ƃ� �E�B���h�E������ꂽ�Ƃ����C�x���g
		PostQuitMessage(0);  //�v���O�����I��
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

//�E�B���h�E�̊e�p�[�c����
//�^�C�g���o�[(��̖��O�\������Ă�Ƃ�)
//�N���C�A���g�̈�(��Ԃł����̈�)
//�t���[��(�g)