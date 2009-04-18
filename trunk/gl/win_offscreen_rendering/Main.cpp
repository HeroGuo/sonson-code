// 
// win_offscreen_rendering
// Main.cpp
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
/////////////////////////////////////////////////////////////////////////////////
//�I�t�X�N���[���E�����_�����O�@�T���v��
//
//		sonson(c)2001 17/9
//

#include "main.h"
#include "CglDIB.h"

//�\������E�B���h�E�̏����T�C�Y
#define WIDTH	640
#define HEIGHT	480

//�쐬����r�b�g�}�b�v�������̃T�C�Y
#define MEM_WIDTH	1200
#define MEM_HEIGHT	900

//�A�v���P�[�V������
char * szAppName = "sonson OpenGL offscreen rendering";

GLfloat LookAt[][4] = {
	{0.0, 0.0, 0.0},
	{3.0, 3.0, 4.5}
};						//���_�̏����ʒu

GLfloat Look_deg =0;	//���_�̊p�x
float tt=0;

////////////////////////////////////////////////////////////////////
//�E�B���h�E�֐�
LONG   WINAPI MainWndProc (HWND, UINT, WPARAM, LPARAM);

void Draw(void){
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//���_�̕ϊ��s��̏�����
	glLoadIdentity();
	//���_�̌���
	gluLookAt(LookAt[1][0],LookAt[1][1],LookAt[1][2],
		LookAt[0][0],LookAt[0][1],LookAt[0][2],
		0.0, 1.0, 0.0);
	//���_�̈ړ�
	drawAxis();
	glFlush();
}
////////////////////////////////////////////////////////////////////
// �G���g���|�C���g
int APIENTRY WinMain(HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        int nCmdShow )
{
	WNDCLASSEX wcex;	// �E�C���h�E�N���X�\����
	HWND hWnd;			// �E�C���h�E�n���h��
	MSG msg;			// ���b�Z�[�W�\����

	// �E�B���h�E�N���X�\���̂�ݒ肵�܂��B
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc = (WNDPROC)MainWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = NULL;//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;//MAKEINTRESOURCE(NULL);
	wcex.lpszClassName = szAppName;
	wcex.hIconSm = NULL;//LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	
	// �E�C���h�E�N���X��o�^���܂��B
	RegisterClassEx(&wcex);

	// �E�C���h�E���쐬���܂��B
   	hWnd = CreateWindow(wcex.lpszClassName,				// �E�C���h�E�N���X��
		szAppName, 		// �L���v�V����������
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,	// �E�C���h�E�̃X�^�C��
		CW_USEDEFAULT,			// �����ʒu
		CW_USEDEFAULT,			// �����ʒu
		WIDTH,
		HEIGHT,					// ����
		NULL,					// �e�E�C���h�E
		NULL,					// �E�C���h�E���j���[
		hInstance,				// �C���X�^���X�n���h��
		NULL);					// WM_CREATE���
	
	// �E�C���h�E��\�����܂��B
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// ���b�Z�[�W���[�v
	while(GetMessage(&msg, NULL, 0, 0)) 
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// �߂�l��Ԃ��܂��B
	return msg.wParam;
}

////////////////////////////////////////////////////////////////////
//�E�B���h�E�v���V�[�W��
LONG WINAPI MainWndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	static CglDIB render;			//OpenGL�r�b�g�}�b�v�������N���X
    static HDC hDC;					//�f�o�C�X�R���e�L�X�g
	static int width;				//��ʃT�C�Y
	static int height;

	LONG    lRet = 1;

    switch (uMsg)
    {
    	case WM_CREATE:
			//�`���N���C�A���g�̈�̃f�o�C�X�R���e�L�X�g
			hDC = GetDC(hWnd);
			//�r�b�g�}�b�v�������쐬
			render.CreateGLDIB(MEM_WIDTH,MEM_HEIGHT,24,24);
			//OpenGL�R�}���h�̏�����
			Init_GLWindow(MEM_WIDTH,MEM_HEIGHT);
			//���T�C�Y����
			Resize(MEM_WIDTH,MEM_HEIGHT);
			StartFunction();
			break;
    	case WM_PAINT:
			//OpenGL�`��
			Draw();
			//�r�b�g�}�b�v���������N���C�A���g�̈�փR�s�[
			render.Draw(hDC,width,height);
			//�A�b�v�f�[�g
			ValidateRect(hWnd,NULL);
			break;
		case WM_SIZE:
			//�`��̈�͈͂̍X�V
			width = LOWORD(lParam);
			height = HIWORD(lParam);
			break;
		case WM_DESTROY:
			PostQuitMessage (0);
			break;
	   	default:
            lRet = DefWindowProc (hWnd, uMsg, wParam, lParam);
			break;
    }
    return lRet;
}