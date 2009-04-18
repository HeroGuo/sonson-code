// 
// SkeltonSDK
// DirectShowSkeltonSDK.cpp
// 
// The MIT License
// 
// Copyright (c) 2009 sonson, sonson@Picture&Software
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//// DirectShowSkeltonSDK.cpp : �A�v���P�[�V�����p�̃G���g�� �|�C���g�̒�`
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100

#pragma comment( lib, "strmBasd.lib" )		// DirectShow
#pragma comment( lib, "Quartz.lib" )		// AMGetErrorText()�̂��߂ɕK�v

#include <dShow.h>							// DirectShow�K�{
#include "DirectShowSkeltonSDK.h"

/////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�:
HINSTANCE hInst;					// ���݂̃C���X�^���X
TCHAR szTitle[MAX_LOADSTRING];				// �^�C�g�� �o�[ �e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];			// �^�C�g�� �o�[ �e�L�X�g

/////////////////////////////////////////////////////////////////////////////////////////
// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̑O�錾:
ATOM				MyRegisterClass( HINSTANCE hInstance );
BOOL				InitInstance( HINSTANCE, int );
LRESULT CALLBACK	WndProc( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK	About( HWND, UINT, WPARAM, LPARAM );

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�֌W
IGraphBuilder			*g_pGraph    = NULL;				// �O���t �r���_
IMediaControl			*g_pMediaCtrl = NULL;				// ���f�B�A �R���g���[��
IVideoWindow			*g_pVideoWindow;					// �`��p�̃E�B���h�E
ICaptureGraphBuilder2	*g_pBuilder = NULL;					// �L���v�`���r���_�[
IMediaEventEx			*g_pMediaEvent = NULL;				// ���f�B�A�C�x���g

IBaseFilter				*g_pSrc		= NULL;					// �\�[�X
IBaseFilter				*g_pVideoRenderer = NULL;			// �����_��

IBaseFilter				*g_pThrough = NULL;					// ���̃v���O�����ł����t�B���^

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�t�B���^�̍쐬
/////////////////////////////////////////////////////////////////////////////////////////
BOOL CreateFilters(void){
	HRESULT hResult;
	// Through�t�B���^�̃C���X�^���X���쐬

	hResult = CoCreateInstance(CLSID_Through, NULL,
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&g_pThrough);
	if (hResult != S_OK)return FALSE;
	// �O���t�r���_�ɒǉ�����
	hResult = g_pGraph->AddFilter(g_pThrough, L"Through");
	if (hResult != S_OK)return FALSE;

	// VideoRenderer�̃C���X�^���X���쐬
	hResult = CoCreateInstance(CLSID_VideoRenderer, NULL, 
		CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&g_pVideoRenderer);
	if (hResult != S_OK)return FALSE;
	// �O���t�r���_�ɒǉ�����
	hResult = g_pGraph->AddFilter(g_pVideoRenderer, L"Video Renderer");
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�t�B���^�̐ڑ�
/////////////////////////////////////////////////////////////////////////////////////////
BOOL ConectFilters(void){
	HRESULT hResult;
	// �\�[�X�̃t�B���^��Through�t�B���^�ɐڑ�
	hResult = g_pBuilder->RenderStream(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,g_pSrc,0,g_pThrough);
	if (hResult != S_OK)return FALSE;

	// Through�t�B���^��VideoRenderer�ɐڑ�
	hResult = g_pBuilder->RenderStream( 0, &MEDIATYPE_Video, g_pThrough, NULL, g_pVideoRenderer );
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�̕`��E�B���h�E�����T�C�Y
/////////////////////////////////////////////////////////////////////////////////////////
BOOL ResizeWindow(HWND hWnd){
	HRESULT hResult;

	// �E�B���h�E���L�������`�F�b�N
	if( !g_pVideoWindow )return FALSE;

	// �E�B���h�E��s����Ԃɂ���
	hResult = g_pVideoWindow->put_Visible(OAFALSE);
	// �E�B���h�E�̗̈�T�C�Y���擾���C�������ޔ͈͂�ݒ肷��
	RECT rect;
	GetWindowRect(hWnd,&rect);
	hResult = g_pVideoWindow->SetWindowPosition(0, 0, rect.right-rect.left,rect.bottom-rect.top);
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E������Ԃɂ���
	hResult = g_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return FALSE;
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�`��̈�̐ݒ�
/////////////////////////////////////////////////////////////////////////////////////////
BOOL SetWindow(HWND hWnd){
	HRESULT hResult;
	// �O���t�r���_����E�B���h�E���擾����
    hResult = g_pGraph->QueryInterface(IID_IVideoWindow, (void **) &g_pVideoWindow);
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E�̃I�[�i�[�ƂȂ�E�B���h�E�̃n���h�����w�肷��
	hResult = g_pVideoWindow->put_Owner( (OAHWND)hWnd );
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E�̃X�^�C�����w�肷��
	hResult = g_pVideoWindow->put_WindowStyle(WS_CHILD| WS_CLIPSIBLINGS);
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E�̗̈�T�C�Y���擾���C�������ޔ͈͂�ݒ肷��
	RECT rect;
	GetWindowRect(hWnd,&rect);
	hResult = g_pVideoWindow->SetWindowPosition(0, 0, rect.right-rect.left,rect.bottom-rect.top);
	if (hResult != S_OK)return FALSE;

	// �E�B���h�E������Ԃɂ���
	hResult = g_pVideoWindow->put_Visible(OATRUE);
	if (hResult != S_OK)return FALSE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�t�B���^�̉��
/////////////////////////////////////////////////////////////////////////////////////////
BOOL ReleaseAll(void){
	if(g_pMediaCtrl)g_pMediaCtrl->Stop();
	if(g_pGraph)g_pGraph->Release();
	if(g_pMediaCtrl)g_pMediaCtrl->Release();
	if(g_pSrc)g_pSrc->Release();
	if(g_pThrough)g_pThrough->Release();
	if(g_pVideoRenderer)g_pVideoRenderer->Release();
	if(g_pBuilder)g_pBuilder->Release();
	if(g_pVideoWindow)g_pVideoWindow->Release();
	if(g_pMediaEvent)g_pMediaEvent->Release();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�L���v�`���f�o�C�X�̎擾�Ɨ�
/////////////////////////////////////////////////////////////////////////////////////////
BOOL GetCaptureDevice(IBaseFilter **ppSrcFilter)
{
	HRESULT hResult;

	// �f�o�C�X��񋓂���
	ICreateDevEnum *pDevEnum = NULL;
	hResult = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC, IID_ICreateDevEnum, (void **)&pDevEnum);
	if (hResult != S_OK)return FALSE;

	// �񋓂����f�o�C�X�̈�Ԗڂ��f�o�C�X�Ƃ��Ď擾����
	IEnumMoniker *pClassEnum = NULL;
	hResult = pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pClassEnum, 0);
	if (hResult != S_OK)return FALSE;

	// �f�o�C�X���t�B���^�ɐڑ�����
	ULONG cFetched;
	IMoniker *pMoniker = NULL;
	if (pClassEnum->Next(1, &pMoniker, &cFetched) == S_OK){
		// �ŏ��̃��j�J���t�B���^�I�u�W�F�N�g�Ƀo�C���h����
		pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void **)ppSrcFilter);
		pMoniker->Release();
	}else
		return FALSE;

	// �O���t�r���_�ɒǉ�����
	hResult = g_pGraph->AddFilter(g_pSrc, L"Video Capture");
	if (hResult != S_OK)return FALSE;

	// �I�u�W�F�N�g�̕ЂÂ�
	pClassEnum->Release();
	pDevEnum->Release();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
// DirectShow�t�B���^�̏���������
/////////////////////////////////////////////////////////////////////////////////////////
BOOL InitializeDirectDraw(HWND hWnd){
	
	HRESULT		hResult;

	// �t�B���^�O���t�쐬
	hResult = CoCreateInstance(CLSID_FilterGraph, NULL, 
		CLSCTX_INPROC, IID_IGraphBuilder, (void **)&g_pGraph);
	if (hResult != S_OK)return FALSE;

	// �L���v�`���f�o�C�X�擾
	hResult = GetCaptureDevice(&g_pSrc);
	if (hResult != TRUE)return FALSE;

	// �L���v�`���r���_�̍쐬
	hResult = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, 
		CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&g_pBuilder);
	if (hResult != S_OK)return FALSE;

	// �O���t�ɃL���v�`���r���_���Z�b�g
	hResult = g_pBuilder->SetFiltergraph(g_pGraph);
	if (hResult != S_OK)return FALSE;

	// ���f�B�A�R���g���[�����擾
	g_pGraph->QueryInterface(IID_IMediaControl, (void **)&g_pMediaCtrl);

	// �t�B���^�̍쐬
	if( !CreateFilters() )return FALSE;
	// �t�B���^�̐ڑ�
	if( !ConectFilters() )return FALSE;
	// �E�B���h�E�̃Z�b�g
	if( !SetWindow(hWnd) )return FALSE;
	
	// �����J�n
	hResult = g_pMediaCtrl->Run();

	return TRUE;
}
/////////////////////////////////////////////////////////////////////////////////////////
// main
/////////////////////////////////////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
 	// TODO: ���̈ʒu�ɃR�[�h���L�q���Ă��������B
	HRESULT		hResult;				// COM�n API�̖߂�l�ۑ��p

	// COM���C�u�����̏�����
	hResult = CoInitialize( NULL );

	MSG msg;
	HACCEL hAccelTable;

	// �O���[�o�� �X�g�����O�����������܂�
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DIRECTSHOWSKELTONSDK, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass( hInstance );

	// �A�v���P�[�V�����̏��������s���܂�:
	if( !InitInstance( hInstance, nCmdShow ) ) 
	{
		ReleaseAll();
		CoUninitialize();		// COM�̏I��
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_DIRECTSHOWSKELTONSDK);

	// ���C�� ���b�Z�[�W ���[�v:
	while( GetMessage(&msg, NULL, 0, 0) ) 
	{
		if( !TranslateAccelerator (msg.hwnd, hAccelTable, &msg) ) 
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	ReleaseAll();
	CoUninitialize();		// COM�̏I��

	return msg.wParam;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  �֐�: MyRegisterClass()
//
//  �p�r: �E�B���h�E �N���X�̓o�^
//
//  �R�����g:
//
//    ���̊֐�����т��̎g�p�͂��̃R�[�h�� Windows 95 �Ő�ɒǉ����ꂽ
//    'RegisterClassEx' �֐��� Win32 �V�X�e���̌݊�����ێ��������ꍇ��
//    �̂ݕK�v�ƂȂ�܂��B�A�v���P�[�V�������A�A�v���P�[�V�����Ɋ֘A�t��
//    ��ꂽ�X���[�� �A�C�R�����擾�ł���悤�A���̊֐����Ăяo�����Ƃ�
//    �d�v�ł��B
//
/////////////////////////////////////////////////////////////////////////////////////////
ATOM MyRegisterClass( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style		= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon		= LoadIcon(hInstance, (LPCTSTR)IDI_DIRECTSHOWSKELTONSDK);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCSTR)IDC_DIRECTSHOWSKELTONSDK;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx( &wcex );
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//   �֐�: InitInstance(HANDLE, int)
//
//   �p�r: �C���X�^���X �n���h���̕ۑ��ƃ��C�� �E�B���h�E�̍쐬
//
//   �R�����g:
//
//        ���̊֐��ł́A�C���X�^���X �n���h�����O���[�o���ϐ��ɕۑ����A�v���O������
//        ���C�� �E�B���h�E���쐬���\�����܂��B
//
/////////////////////////////////////////////////////////////////////////////////////////
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
   HWND hWnd;

   hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X �n���h����ۑ����܂�

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if( !hWnd ) 
   {
      return FALSE;
   }

   ShowWindow( hWnd, nCmdShow );
   UpdateWindow( hWnd );

   if( !InitializeDirectDraw(hWnd) )
	   return FALSE;

   return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//  �֐�: WndProc(HWND, unsigned, WORD, LONG)
//
//  �p�r: ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- �I�����b�Z�[�W�̒ʒm�ƃ��^�[��
//
//
/////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch( message ) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// ���j���[�I���̉��:
			switch( wmId ) 
			{
				case IDM_ABOUT:
				   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
				   break;
				case IDM_EXIT:
				   DestroyWindow( hWnd );
				   break;
				default:
				   return DefWindowProc( hWnd, message, wParam, lParam );
			}
			break;
		case WM_SIZE:
			ResizeWindow(hWnd);
			break;
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;
		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
   }
   return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
// �o�[�W�������{�b�N�X�p���b�Z�[�W �n���h��
LRESULT CALLBACK About( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch( message )
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if( LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL ) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}
