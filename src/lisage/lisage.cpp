// lisage.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//

#include "stdafx.h"
#include "lisage.h"
#include <math.h>

#define MAX_LOADSTRING 100
#define WM_TRAYICON		WM_APP

// �O���[�o���ϐ�:
HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK MoveWindow(HWND hWnd, LPARAM lParam);

int count = 0; // �J�E���^
double sinn[80], coss[40]; // �͋Z

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �����ɃR�[�h��}�����Ă��������B
	MSG msg;
	HACCEL hAccelTable;

	if (MessageBox(NULL, L"�{�\�t�g�E�F�A�����s����ƁA��ʏ�̂��ׂẴE�B���h�E�������o���A\n"
						 L"�\�����Ȃ�����������N��������A����Ɏx������������ꂪ����܂��B\n"
						 L"�E���̃^�X�N�g���C���E�N���b�N���ƂŏI���ł��܂����A\n�O�̂��ߎ��O�Ƀ^�X�N�}�l�[�W���[���N�����Ă������Ƃ������������߂��܂��B\n\n"
						 L"���s���܂����H", L"!! WARNING !!", MB_YESNO | MB_ICONWARNING) == IDNO)
		return 0;

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_LISAGE, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LISAGE));

	// �e�[�u���ݒ�
	int i;
		for (i = 0; i < 80; i++)
		{
			sinn[i] = sin((double)i * 3.1415926535897932 / 40) * 16;
			if (i < 40)
				coss[i] = cos((double)i * 3.1415926535897932 / 20) * 4;
		}

	// ���C�� ���b�Z�[�W ���[�v:
	while (1)
	{
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if (msg.message == WM_QUIT) break;
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		EnumWindows(MoveWindow, NULL);
			count++;
		Sleep(16);	//�@�l�^�������̂ŁA�����͂��̂ւ�ŏI���ɂ��悤���Ǝv���܂��B
					//�@������Ȃ����e�Ő\����Ȃ��ł����A�������ǂ������肪�Ƃ��������܂����B
					//�@�e���b�v�̏���������ʂ��߂��Ă��Ȃ��E�E�E
	}

	return (int) msg.wParam;
}



//
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
//  �R�����g:
//
//    ���̊֐�����юg�����́A'RegisterClassEx' �֐����ǉ����ꂽ
//    Windows 95 ���O�� Win32 �V�X�e���ƌ݊�������ꍇ�ɂ̂ݕK�v�ł��B
//    �A�v���P�[�V�������A�֘A�t����ꂽ
//    �������`���̏������A�C�R�����擾�ł���悤�ɂ���ɂ́A
//    ���̊֐����Ăяo���Ă��������B
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LISAGE));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_LISAGE);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   return TRUE;
}

BOOL CALLBACK MoveWindow(HWND hWnd, LPARAM lParam)
{
	if (IsWindowVisible(hWnd))
	{
		RECT point;
		int scrambled_count = count + (int)hWnd;

		GetWindowRect(hWnd, &point);
		SetWindowPos(hWnd, HWND_TOP, point.left + sinn[scrambled_count % 80] * (scrambled_count / 80 % 2 ? -1 : 1), point.top + coss[scrambled_count % 40],
			0, 0, SWP_NOSIZE);
	}
	return TRUE;
}

//
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:  ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
//
//
NOTIFYICONDATA task;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		task.cbSize = sizeof(NOTIFYICONDATA);
		task.hWnd = hWnd;
		task.uID = 101;
		task.hIcon = LoadIcon(hInst, (LPCTSTR)IDI_LISAGE);
		task.uCallbackMessage = WM_TRAYICON;
		lstrcpy(task.szTip, szTitle);
		task.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		Shell_NotifyIcon(NIM_ADD, &task);

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �`��R�[�h�������ɒǉ����Ă�������...
		EndPaint(hWnd, &ps);
		break;
	case WM_TRAYICON:
		if (lParam == WM_RBUTTONUP && wParam == 101)
		{
			// �|�b�v�A�b�v���j���[���o��
			POINT cursor;
			HMENU hMenu = LoadMenu(hInst, (LPCTSTR)IDC_LISAGE);

			GetCursorPos(&cursor);
			SetForegroundWindow(hWnd);
			TrackPopupMenu(GetSubMenu(hMenu, 0),		// �|�b�v����
							TPM_BOTTOMALIGN, cursor.x, cursor.y,
							0, hWnd, NULL);
			DestroyMenu(hMenu);
		}
		break;
	case WM_DESTROY:
		Shell_NotifyIcon(NIM_DELETE, &task);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
